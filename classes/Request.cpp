#include "CollegeClass.h"
#include <list>
#include "Student.h"
#include <iostream>
#include "Request.h"
#include "Dataset.h"
#include "Parser.h"
#include "menuFunctions.h"

#define CLASS_CAP 25

bool Request::maintainsClassBalance(DataSet &dataset, int sizeStudentCompare, list<vector<string>> classesPerUc) {
    string currentUc = this->collegeClass.get_ucCode();
    list<string> classes = dataset.getUcsByClasses(classesPerUc)[currentUc];
    for(string currentClass : classes){
        int ucClassStudents =  getNumStudentsInClassAndUc(CollegeClass(currentClass,currentUc, {}, Schedule()), dataset);
        if(abs(ucClassStudents - (sizeStudentCompare + 1) > 4) && this->option == ADD) return false;
        if(abs(ucClassStudents - (sizeStudentCompare - 1) > 4) && this->option == REMOVE) return false;
    }
    return true;
}

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

bool Request::addClass(DataSet &dataset, string classToAdd, list<vector<string>> classesPerUc) {
    bool failed = false;
    list<string> classUcs = dataset.getUcsByClasses(classesPerUc)[classToAdd]; // get all ucs from class
    vector<CollegeClass> oldClasses = student.get_studentClasses();
    for(string uc : classUcs) {
        CollegeClass currentCC = dataset.buildObject(classToAdd, uc);
        Request request = Request(currentCC, student, UC, ADD, dataset);
        if (!request.addUc(dataset, currentCC, classesPerUc)) failed = true;
    }
    if(failed) {
        setStudentClasses(oldClasses, student);
    }
    return !failed;
}

bool Request::removeClass(DataSet &dataset, string classToRemove, list<vector<string>> classesPerUc) {
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
    }
    if(failed) {
        setStudentClasses(oldClasses, student);
    }
    return !failed;
}

bool Request::addUc(DataSet& dataset, CollegeClass collegeClassToAdd, list<vector<string>> classesPerUc) {
    int numCurrentStudents = getNumStudentsInClassAndUc(collegeClassToAdd, dataset);
    if(!isConflictingSchedule(getScheduleByStudent(student.get_studentCode(), dataset), collegeClassToAdd.get_collegeClassSchedule().get_scheduleLessons()) 
    && numCurrentStudents < CLASS_CAP
    && maintainsClassBalance(dataset, numCurrentStudents, classesPerUc)) {
        addStudentClass(collegeClassToAdd, student);
        addStudentInCollegeClass(student, dataset, collegeClassToAdd);
        return true;
    }
    return false;
}

bool Request::removeUc(DataSet& dataset, CollegeClass collegeClassToRemove, list<vector<string>> classesPerUc){
    int numCurrentStudents = getNumStudentsInClassAndUc(collegeClassToRemove, dataset);
    if(maintainsClassBalance(dataset, numCurrentStudents, classesPerUc)) {
        vector<CollegeClass> toRemove = student.get_studentClasses();
        toRemove.erase(remove(toRemove.begin(), toRemove.end(), collegeClassToRemove), toRemove.end());
        setStudentClasses(toRemove, student);
        removeStudentFromCollegeClass(student, dataset, collegeClassToRemove);
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

bool Request::switchUc(DataSet& dataset, CollegeClass collegeClassToRemove, CollegeClass collegeClassToAdd, list<vector<string>> classesPerUc) {
    if(removeUc(dataset, collegeClassToRemove, classesPerUc)) {
        if(!addUc(dataset, collegeClassToAdd, classesPerUc)){
            addUc(dataset, collegeClassToRemove, classesPerUc);
            return false;
        }
    }
    return true;
}

bool Request::switchClass(DataSet& dataset, string classToRemove, string classToAdd, list<vector<string>> classesPerUc){
    if(removeClass(dataset, classToRemove, classesPerUc)){
        if(!addClass(dataset,classToAdd, classesPerUc)){
            addClass(dataset,classToRemove, classesPerUc);
            return false;
        }
    }
    return true;
}