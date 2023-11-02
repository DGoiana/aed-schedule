#include "CollegeClass.h"
#include <list>
#include <queue>
#include "Student.h"
#include "Request.h"
#include "Dataset.h"
#include "Parser.h"
#include <iostream>

#define CLASS_CAP 25

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
    Parser parser;
    list<Lesson> classLessons = (dataset.getScheduleByClass(classToAdd.get_classCode())).get_scheduleLessons();
    list<Lesson> studentLessons = dataset.getScheduleByStudent(this->student.get_studentCode()).get_scheduleLessons();
    int numStudentsClass = dataset.maxStudentUcInClass(classToAdd.get_classCode());
    if(!isConflictingLessons(studentLessons,classLessons) && maintainsClassBalance(classToAdd.get_classCode(),numStudentsClass)
     && numStudentsClass < CLASS_CAP){
        for(Lesson lesson : studentLessons) classLessons.push_back(lesson);
        dataset.setStudentSchedule(classLessons,this->student);
        return true;
    }
    return false;
}

bool Request::maintainsClassBalance(string classCode,int sizeStudentCompare) {
    map<string,list<string>> ucsByClasses = Parser::getUcsByClasses();
    for(auto ucClass : ucsByClasses){
        if(ucClass.first[0] == classCode[0]){
            if(abs(dataset.maxStudentUcInClass(ucClass.first) - (sizeStudentCompare+1)) > 4 
            && abs(dataset.maxStudentUcInClass(ucClass.first) - (sizeStudentCompare-1)) > 4)
                return false;
        }
    }
    return true;
}

bool Request::removeClass(DataSet& dataset,CollegeClass classToRemove) {
    int removed = 0;
    list<Lesson> newLessons;
    list<Lesson> studentLessons = this->student.get_studentSchedule().get_scheduleLessons();
    int numStudentsClass = dataset.maxStudentUcInClass(classToRemove.get_classCode());
    if(maintainsClassBalance(classToRemove.get_classCode(),numStudentsClass)){
        for(Lesson lesson : studentLessons){
            if(lesson.get_LessonClass().get_classCode() != classToRemove.get_classCode()) {
                newLessons.push_back(lesson);
            }
            else{
                removed++;
            }
        }
        dataset.setStudentSchedule(newLessons,this->student);
    }
    
    if(removed == 0){
        return false;
    }
    return true;
}

bool Request::switchClass(DataSet& dataset,CollegeClass classToRemove, CollegeClass classToAdd) {
    removeClass(dataset,classToRemove);
    addClass(dataset,classToAdd);
    return true;
}

bool Request::isConflictingLessons(list<Lesson> studentLessons, list<Lesson> lessonsToCompare) {
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
    list<Lesson> studentSchedule = this->student.get_studentSchedule().get_scheduleLessons();
    list<Lesson> lessonsToCompare = Parser::mapLessons()[ucToAdd];
    if(dataset.getNumStudentsInClassAndUc(ucToAdd) < CLASS_CAP
    && !isConflictingLessons(studentSchedule,lessonsToCompare)) {
        for(Lesson lesson : studentSchedule) lessonsToCompare.push_back(lesson);
        dataset.setStudentSchedule(lessonsToCompare,this->student);
        return true;
        }
    return false;
}

bool Request::removeUc(DataSet& dataset,CollegeClass ucToRemove){
    int removed = 0;
    list<Lesson> newLessons;
    list<Lesson> studentLessons = dataset.getScheduleByStudent(this->student.get_studentCode()).get_scheduleLessons();
    for(Lesson lesson : studentLessons){
        if(lesson.get_LessonClass().get_ucCode() != ucToRemove.get_ucCode()) {
            newLessons.push_back(lesson);
        }
        else{
            removed++;
        }
    }

    dataset.setStudentSchedule(newLessons,this->student);
    
    if(removed == 0){
        return false;
    }
    return true;
}

bool Request::switchUc(DataSet& dataset,CollegeClass UcToRemove,CollegeClass UcToAdd) {
    return removeUc(dataset,UcToRemove) && addUc(dataset,UcToAdd);
}

void Request::addRequestToQueue(Request request){
    this->requests.push(request);
}

void Request::removeRequestFromQueue(){
    Request request = this->requests.front();
    if(request.get_type() == CLASS){
        if(request.get_option() == ADD){
            //È só fazer remove
        }
        if(request.get_option() == REMOVE){
            //È só fazer add
        }
        if(request.get_option() == SWITCH){
            //È só fazer add e remove
        }
    }
    else if(request.get_type() == UC){
        if(request.get_option() == ADD){
            //È só fazer remove
        }
        if(request.get_option() == REMOVE){
            //È só fazer add
        }
        if(request.get_option() == SWITCH){
            //È só fazer add e remove
        }
    }
    this->requests.pop();
}

OPTION Request::get_otption(){
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