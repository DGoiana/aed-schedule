#include "CollegeClass.h"
#include <list>
#include "Student.h"
#include <algorithm>
#include "Request.h"
#include "Dataset.h"
#include "menuFunctions.h"

#define CLASS_CAP 25

/**
 * For making a change in the Student Schedule needs to maintain class balance (the difference between the number of
 * students in all classes is less than 4).
 * Time complexity: O(n)
 * @param dataset dataset to change the programs state
 * @param sizeStudentCompare size of the CollegeClass to be changed
 * @param classesPerUc classes of the Uc
 * @return if change maintains class balance
 */
bool Request::maintainsClassBalance(DataSet &dataset, int sizeStudentCompare, list<vector<string>> classesPerUc) {
    string currentUc = this->collegeClass.get_ucCode();
    list<string> classes = dataset.getUcsByClasses(classesPerUc)[currentUc];
    for(string currentClass : classes){
        int ucClassStudents =  MenuFunctions::getNumStudentsInClassAndUc(CollegeClass(currentClass,currentUc, {}, Schedule()), dataset);
        if(abs(ucClassStudents - (sizeStudentCompare + 1) > 4) && this->option == ADD) return false;
        if(abs(ucClassStudents - (sizeStudentCompare - 1) > 4) && this->option == REMOVE) return false;
    }
    return true;
}

/**
 * For making a change in the Student Schedule any given Uc needs not to conflict with the Student current Schedule.
 * Time complexity: O(n²)
 * @param studentSchedule current Student Schedule
 * @param lessonsToCompare list of lessons to compare
 * @return if the current Schedule conflicts with the new Schedule
 */
bool Request::isConflictingSchedule(Schedule studentSchedule, vector<Lesson> lessonsToCompare) {
    vector<Lesson> studentLessons = studentSchedule.get_scheduleLessons();
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
 * @param newClassUcs chosen Ucs to undo
 * @param undo "undo" if it is an undo request
 * @return if request was successful
 */
bool Request::addClass(DataSet &dataset, string classToAdd, list<vector<string>> classesPerUc, list<string> newClassUcs, string undo) {
    bool failed = false;
    list<string> classUcs = dataset.getUcsByClasses(classesPerUc)[classToAdd]; // get all ucs from class
    vector<CollegeClass> oldClasses = student.get_studentClasses();
    if(!newClassUcs.empty() && undo == "undo") classUcs = newClassUcs;
    for(string uc : classUcs) {
        CollegeClass currentCC = dataset.buildObject(classToAdd, uc);
        Request request = Request(currentCC, student, UC, ADD, dataset);
        if (!request.addUc(dataset, currentCC, classesPerUc)) failed = true;
    }
    if(failed) {
        MenuFunctions::setStudentClasses(oldClasses, student);
    }
    return !failed;
}

/**
 * Request for removing a given class to the Student Schedule by removing each Uc at a time, then calling the dataset object
 * to set the current state of the program. If request fails the Student Schedule goes back to what it was before.
 * Time Complexity: O(n²)
 * @param dataset DataSet object to be changed
 * @param classToRemove class to be removed
 * @param removedElements list that contains removed elements for undo request
 * @return if request was successful
 */
bool Request::removeClass(DataSet &dataset, string classToRemove, list<vector<string>> classesPerUc, list<string>& removedElements) {
    bool failed = false;

    list<string> classUcs;
    for(CollegeClass cc : student.get_studentClasses()){ 
        if(cc.get_classCode() == classToRemove) classUcs.push_back(cc.get_ucCode());
    }

    vector<CollegeClass> oldClasses = student.get_studentClasses();

    for(string uc : classUcs) {
        CollegeClass currentCC = CollegeClass(classToRemove, uc, {}, Schedule());
        Request request = Request(currentCC, student, UC, REMOVE, dataset);
        if (!request.removeUc(dataset, currentCC, classesPerUc)) failed = true;
        for(CollegeClass cc : oldClasses){
            if(cc == currentCC) removedElements.push_back(uc);
        }
    }
    if(failed) {
        MenuFunctions::setStudentClasses(oldClasses, student);
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
 * @param classesPerUc classes of the Uc
 * @return if the request was successful
 */
bool Request::addUc(DataSet& dataset, CollegeClass collegeClassToAdd, list<vector<string>> classesPerUc) {
    int numCurrentStudents = MenuFunctions::getNumStudentsInClassAndUc(collegeClassToAdd, dataset);
    if(!isConflictingSchedule(MenuFunctions::getScheduleByStudent(student.get_studentCode(), dataset), collegeClassToAdd.get_collegeClassSchedule().get_scheduleLessons()) 
    && numCurrentStudents < CLASS_CAP
    && maintainsClassBalance(dataset, numCurrentStudents, classesPerUc)) {
        MenuFunctions::addStudentClass(collegeClassToAdd, student);
        MenuFunctions::addStudentInCollegeClass(student, dataset, collegeClassToAdd);
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
 * @param classesPerUc classes of the Uc
 * @return if the request was successful
 */
bool Request::removeUc(DataSet& dataset, CollegeClass collegeClassToRemove, list<vector<string>> classesPerUc){
    int numCurrentStudents = MenuFunctions::getNumStudentsInClassAndUc(collegeClassToRemove, dataset);
    if(maintainsClassBalance(dataset, numCurrentStudents, classesPerUc)) {
        vector<CollegeClass> toRemove = student.get_studentClasses();
        toRemove.erase(remove(toRemove.begin(), toRemove.end(), collegeClassToRemove), toRemove.end());
        MenuFunctions::setStudentClasses(toRemove, student);
        MenuFunctions::removeStudentFromCollegeClass(student, dataset, collegeClassToRemove);
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
 * @param classesPerUc classes of the Uc
 * @return if the request was successful
 */
bool Request::switchUc(DataSet& dataset, CollegeClass collegeClassToRemove, CollegeClass collegeClassToAdd, list<vector<string>> classesPerUc) {
    if(removeUc(dataset, collegeClassToRemove, classesPerUc)) {
        if(!addUc(dataset, collegeClassToAdd, classesPerUc)){
            addUc(dataset, collegeClassToRemove, classesPerUc);
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
 * @param classesPerUc classes of the Uc
 * @param undo "undo" if it is an undo request
 * @return if request was successful
 */
bool Request::switchClass(DataSet& dataset, string classToRemove, string classToAdd, list<vector<string>> classesPerUc, list<string>& removedElements, string undo){
    list<string> temp = removedElements;
    if(removeClass(dataset, classToRemove, classesPerUc, removedElements)){
        if(!addClass(dataset,classToAdd, classesPerUc, temp, undo)){
            addClass(dataset,classToRemove, classesPerUc);
            return false;
        }
    }
    return true;
}