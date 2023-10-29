#include "CollegeClass.h"
#include <list>
#include "Student.h"
#include "Request.h"
#include "Dataset.h"
#include "Parser.h"
#include <iostream>

#define CLASS_CAP 30

bool Request::handleRequest() {
    switch (this->option)
    {
    case ADD:
        if(this->type == UC) return addUc(this->dataset,this->collegeClass);
        else return addClass(this->dataset,this->collegeClass);
    case REMOVE:
        if(this->type == UC) return removeUc(this->dataset,this->collegeClass);
        else return removeClass(this->dataset,this->collegeClass);
        break;
    case SWITCH:
        if(this->type == UC) return switchUc(this->dataset,this->collegeClass,this->newCollegeClass);
        else return switchClass(this->dataset,this->collegeClass,this->newCollegeClass);
    default:
        return false;
    }
}

bool Request::addClass(DataSet& dataset,CollegeClass classToAdd) {

    return true;
}

bool Request::removeClass(DataSet& dataset,CollegeClass classToRemove) {
    return true;
}

bool Request::switchClass(DataSet& dataset,CollegeClass classToRemove, CollegeClass classToAdd) {
    return true;
}

bool Request::isConflictingUcClass(list<Lesson> studentLessons, list<Lesson> lessonsToCompare) {
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
            
            if (hasConflictTime && hasSameWeekDay)
                return true;
        }
    }
    return false;
}

bool Request::addUc(DataSet& dataset,CollegeClass ucToAdd) {
    map<Student,list<CollegeClass>> currentUcs = Parser::mapCollegeClasses();
    int numUcs = currentUcs[this->student].size();
    map<string,list<string>> allUcClass = Parser::getClassesByUcs();
    list<Lesson> studentSchedule = this->student.get_studentSchedule().get_scheduleLessons();
    list<Lesson> lessonsToCompare = Parser::mapLessons()[ucToAdd];
    if(dataset.getNumStudentsInClass(ucToAdd) < CLASS_CAP
    && !isConflictingUcClass(studentSchedule,lessonsToCompare)) {
        for(Lesson lesson : studentSchedule) lessonsToCompare.push_back(lesson);
        dataset.setStudentSchedule(lessonsToCompare,this->student);
        return true;
        }
    return false;
}

bool Request::removeUc(DataSet& dataset,CollegeClass ucToRemove){
    list<Lesson> newLessons;
    list<Lesson> studentLessons = dataset.getScheduleByStudent(this->student.get_studentCode()).get_scheduleLessons();
    for(Lesson lesson : studentLessons){
        if(lesson.get_LessonClass().get_ucCode() != ucToRemove.get_ucCode()) {
            newLessons.push_back(lesson);
        }
    }
    dataset.setStudentSchedule(newLessons,this->student);
    return true;
}

bool Request::switchUc(DataSet& dataset,CollegeClass UcToRemove,CollegeClass UcToAdd) {
    return removeUc(dataset,UcToRemove) && addUc(dataset,UcToAdd);
}