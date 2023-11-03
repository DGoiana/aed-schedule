#include "CollegeClass.h"
#include <list>
#include "Student.h"
#include "Request.h"
#include "Dataset.h"
#include "Parser.h"
#include <iostream>

#define CLASS_CAP 25


void Request::setStudent(Student student) {
    this->student = student;
}

Student Request::getStudent() {
    return this->student;
}

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

bool Request::addClass(DataSet &dataset, string classToAdd) {
    bool failed = false;
    list<string> classUcs = Parser::getUcsByClasses()[classToAdd]; // get all ucs from class
    set<CollegeClass> oldClasses = this->student.get_studentClasses();
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

bool Request::removeClass(DataSet &dataset, string classToRemove) {
    bool failed = false;
    list<string> classUcs = Parser::getUcsByClasses()[classToRemove]; // 
    set<CollegeClass> oldClasses = this->student.get_studentClasses();
    for(string uc : classUcs) {
        CollegeClass currentCC = CollegeClass(classToRemove, uc, {}, Schedule());
        Request request = Request(currentCC, this->student, UC, REMOVE, dataset);
        if (!request.removeUc(dataset, currentCC)) failed = true;
    }
    if(failed) {
        dataset.setStudentClasses(oldClasses, this->student);
    }
    return !failed;
}

bool Request::addUc(DataSet& dataset,CollegeClass collegeClassToAdd) {
    for(CollegeClass cc :dataset.getStudentByNumber(this->student.get_studentCode()).get_studentClasses()) {
        cout << cc.get_classCode() << " " << cc.get_ucCode() << endl;
    }
    int numCurrentStudents = dataset.getNumStudentsInClassAndUc(collegeClassToAdd);
    if(!isConflictingSchedule(dataset.getScheduleByStudent(this->student.get_studentCode()), collegeClassToAdd.get_collegeClassSchedule().get_scheduleLessons()) 
    && numCurrentStudents < CLASS_CAP
    && maintainsClassBalance(numCurrentStudents)) {
        dataset.addStudentClass(collegeClassToAdd, this->student);
        for(CollegeClass cc : dataset.getStudentByNumber(this->student.get_studentCode()).get_studentClasses()) {
            cout << cc.get_classCode() << " " << cc.get_ucCode() << endl;
        }
        return true;
    }
    return false;
}

bool Request::removeUc(DataSet& dataset, CollegeClass collegeClassToRemove){
    int numCurrentStudents = dataset.getNumStudentsInClassAndUc(collegeClassToRemove);
    if(maintainsClassBalance(numCurrentStudents)) {
        set<CollegeClass> toRemove = dataset.getStudentByNumber(this->student.get_studentCode()).get_studentClasses();
        toRemove.erase(collegeClassToRemove);
        dataset.setStudentClasses(toRemove, this->student);
        return true;
    }

    return false;
}

bool Request::switchUc(DataSet& dataset, CollegeClass collegeClassToRemove, CollegeClass collegeClassToAdd) {
    if(removeUc(dataset, collegeClassToRemove)) {
        if(!addUc(dataset, collegeClassToAdd)){
            addUc(dataset, collegeClassToRemove);
            return false;
        }
    }
    return true;
}

bool Request::switchClass(DataSet& dataset, string classToRemove, string classToAdd){
    if(removeClass(dataset, classToRemove)){
        if(!addClass(dataset,classToAdd)){
            addClass(dataset,classToRemove);
            return false;
        }
    }
    return true;
}