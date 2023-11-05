#include "CollegeClass.h"
#include <list>
#include "Student.h"
#include "Request.h"
#include "Dataset.h"
#include "Parser.h"
#include <algorithm>

#define CLASS_CAP 25



/**
 * For making a change in the Student Schedule needs to maintain class balance (the difference between the number of
 * students in all classes is less than 4).
 * Time complexity: O(n)
 * @param sizeStudentCompare
 * @return if change maintains class balance
 */
bool Request::maintainsClassBalance(int sizeStudentCompare) {
    string currentUc = this->collegeClass.get_ucCode();
    list<string> classes = Parser::getUcsByClasses()[currentUc];
    for(string currentClass : classes){
        int ucClassStudents =  dataset.getNumStudentsInClassAndUc(CollegeClass(currentClass,currentUc, {}, Schedule()));
        if(abs(ucClassStudents - (sizeStudentCompare + 1) > 4) && this->option == ADD) return false;
        if(abs(ucClassStudents - (sizeStudentCompare - 1) > 4) && this->option == REMOVE) return false;
    }
    return true;
}
/**
 * For making a change in the Student Schedule any given Uc needs not to conflict with the Student current Schedule.
 * Time complexity: O(n²)
 * @param sizeStudentCompare
 * @return if the current Schedule conflicts with the new Schedule
 */
bool Request::isConflictingSchedule(Schedule studentSchedule, list<Lesson> lessonsToCompare) {
    list<Lesson> studentLessons = studentSchedule.get_scheduleLessons();
    for(Lesson lessonToCompare : lessonsToCompare) {
        for(Lesson studentLesson : studentLessons){
            double studentStartTime = studentLesson.get_LessonStartHour();
            double studentFinishTime = studentStartTime + studentLesson.get_LessonDuration();
            double lessonToCompareStartTime = lessonToCompare.get_LessonStartHour(); 
            double lessonToCompareFinishTime = lessonToCompareStartTime + lessonToCompare.get_LessonDuration();

            bool hasSameWeekDay = lessonToCompare.get_LessonWeekday() == studentLesson.get_LessonWeekday();
            bool hasConflictTime =  (lessonToCompareStartTime > studentStartTime && lessonToCompareStartTime < studentFinishTime) 
                                || (lessonToCompareFinishTime > studentStartTime && lessonToCompareFinishTime < studentFinishTime)
                                || (lessonToCompareStartTime < studentStartTime && lessonToCompareFinishTime > studentFinishTime);

            if (lessonToCompare.get_ucCode() == studentLesson.get_ucCode())
                return true;
            if (hasConflictTime && hasSameWeekDay) return true;
        }
    }
    return false;
}
/**
 * Request for adding a given class to the Student Schedule by adding each Uc at a time, then calling the dataset object
 * to set the current state of the program. If request fails the Student Schedule goes back to what it was before.
 * Time Complexity: O(n³)
 * @param dataset DataSet object to be changed
 * @param classToAdd class to be added
 * @return if request was successful
 */
bool Request::addClass(DataSet &dataset, string classToAdd,list<string> newClassUcs) {
    bool failed = false;
    list<string> classUcs = Parser::getUcsByClasses()[classToAdd]; // get all ucs from class
    set<CollegeClass> oldClasses = this->student.get_studentClasses();
    if(!newClassUcs.empty()) classUcs = newClassUcs;
    for(string uc : classUcs) {
        CollegeClass currentCC = CollegeClass(classToAdd, uc, Parser::studentsFromCollegeClass()[CollegeClass(classToAdd, uc, {}, Schedule())], Schedule(Parser::mapLessons()[CollegeClass(classToAdd, uc, {}, Schedule())]));
        Request request = Request(currentCC, this->student, UC, ADD, dataset);
        if (!request.addUc(dataset, currentCC)) failed = true;
    }
    if(failed) {
        dataset.setStudentClasses(oldClasses, this->student);
    }
    return !failed;
}
/**
 * Request for removing a given class to the Student Schedule by removing each Uc at a time, then calling the dataset object
 * to set the current state of the program. If request fails the Student Schedule goes back to what it was before.
 * Time Complexity: O(n²)
 * @param dataset DataSet object to be changed
 * @param classToRemove class to be removed
 * @return if request was successful
 */
bool Request::removeClass(DataSet &dataset, string classToRemove,list<string>& removedElements) {
    bool failed = false;
    list<string> classUcs = Parser::getUcsByClasses()[classToRemove]; // 
    set<CollegeClass> oldClasses = this->student.get_studentClasses();
    for(string uc : classUcs) {
        CollegeClass currentCC = CollegeClass(classToRemove, uc, {}, Schedule());
        Request request = Request(currentCC, this->student, UC, REMOVE, dataset);
        if (!request.removeUc(dataset, currentCC)) failed = true;
        for(CollegeClass cc : this->student.get_studentClasses()){
            if(cc == currentCC) removedElements.push_back(uc);
        }
    }
    if(failed) {
        dataset.setStudentClasses(oldClasses, this->student);
        removedElements.clear();
    }
    return !failed;
}

/**
 * Request for adding a combination of Uc and Class to a Student Schedule, then calling the dataset to change its
 * internal state. If request fails the Student Schedule goes back to what it was before.
 * Time Complexity: O(n²)
 * @param dataset DataSet object to be changed
 * @param collegeClassToAdd collegeClass to be added
 * @return if the request was successful
 */
bool Request::addUc(DataSet& dataset,CollegeClass collegeClassToAdd) {
    int numCurrentStudents = dataset.getNumStudentsInClassAndUc(collegeClassToAdd);
    if(!isConflictingSchedule(dataset.getScheduleByStudent(this->student.get_studentCode()), collegeClassToAdd.get_collegeClassSchedule().get_scheduleLessons())
    && numCurrentStudents < CLASS_CAP
    && maintainsClassBalance(numCurrentStudents)) {
        dataset.addStudentClass(collegeClassToAdd, this->student);
        dataset.addStudentInCollegeClass(this->student,collegeClassToAdd);
        return true;
    }
    return false;
}
/**
 * Request for removing a combination of Uc and Class to a Student Schedule, then calling the dataset to change its
 * internal state.If request fails the Student Schedule goes back to what it was before.
 * Time Complexity: O(n)
 * @param dataset DataSet object to be changed
 * @param collegeClassToRemove collegeClass to be added
 * @return if the request was successful
 */
bool Request::removeUc(DataSet& dataset, CollegeClass collegeClassToRemove){
    int numCurrentStudents = dataset.getNumStudentsInClassAndUc(collegeClassToRemove);
    if(maintainsClassBalance(numCurrentStudents)) {
        set<CollegeClass> toRemove = dataset.getStudentByNumber(this->student.get_studentCode()).get_studentClasses();
        toRemove.erase(collegeClassToRemove);
        dataset.setStudentClasses(toRemove, this->student);
        dataset.removeStudentFromCollegeClass(this->student,collegeClassToRemove);
        return true;
      }
     return false;
}

OPTION Request::get_option(){
    return this->option;
}

TYPE Request::get_type(){
    return this->type;
}

Student Request::get_student(){
    return this->student;
}

CollegeClass Request::get_collegeClass(){
    return this->collegeClass;
}

CollegeClass Request::get_newCollegeClass(){
    return this->newCollegeClass;
}
/**
 * Request for switching a given combination of Uc and Class to another in a Student Schedule,
 * then calling the dataset to change its internal state.If request fails the Student Schedule goes back to what it was before.
 * Time Complexity: O(n³)
 * @param dataset DataSet object to be changed
 * @param collegeClassToAdd collegeClass to be added
 * @param collegeClassToRemove collegeClass to be removed
 * @return if the request was successful
 */
bool Request::switchUc(DataSet& dataset, CollegeClass collegeClassToRemove, CollegeClass collegeClassToAdd) {
    if(removeUc(dataset, collegeClassToRemove)) {
        if(!addClass(dataset, collegeClassToAdd.get_classCode(),{collegeClassToAdd.get_ucCode()})){
            addClass(dataset, collegeClassToRemove.get_classCode(),{collegeClassToRemove.get_ucCode()});
            return false;
        }
    }
    return true;
}

/**
 * Request for switching a given class into another in a Student Schedule by changing each Uc at a time,then calling the dataset object
 * to set the current state of the program. If request fails the Student Schedule goes back to what it was before.
 * Time Complexity: O(n³)
 * @param dataset DataSet object to be changed
 * @param classToAdd class to be added
 * @param classToRemove class to be removed
 * @return if request was successful
 */
bool Request::switchClass(DataSet& dataset, string classToRemove, string classToAdd,list<string>& removedElements){
    if(removeClass(dataset, classToRemove,removedElements)){
        if(!addClass(dataset,classToAdd,removedElements)){
            addClass(dataset,classToRemove);
            return false;
        }
    }
    return true;
}