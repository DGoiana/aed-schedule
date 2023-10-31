#include "CollegeClass.h"
#include <list>
#include "Student.h"
#include "Request.h"
#include "Dataset.h"
#include "Parser.h"
#include <iostream>

#define CLASS_CAP 25
/**
 * Handles the request according to its type and option
 * Time Complexity: O(1)
 * @return if the request was successful
 */
bool Request::handleRequest() {
    switch (this->option)
    {
    case ADD:
        if(this->type == UC) return addUc(this->dataset,this->collegeClass);
        else return addClass(this->dataset,this->collegeClass);
    case REMOVE:
        if(this->type == UC) return removeUc(this->dataset,this->collegeClass);
        else return removeClass(this->dataset,this->collegeClass);
    case SWITCH:
        if(this->type == UC) return switchUc(this->dataset,this->collegeClass,this->newCollegeClass);
        else return switchClass(this->dataset,this->collegeClass,this->newCollegeClass);
    default:
        return false;
    }
}
/**
 * Adds all the UCs of a Class into the Student Schedule
 * Time Complexity: O(n²)
 * @param dataset dataset to be changed
 * @param classToAdd classCode of the Class to add
 * @return if the request was successful
 */
bool Request::addClass(DataSet& dataset,CollegeClass classToAdd) {
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
/**
 * Checks if the alteration (Adding or Removing) destroys the balances between the classes
 * Time Complexity: O(n)
 * @param classCode classCode of the classed to be checked
 * @param sizeStudentCompare size of the class to be compared
 * @return if the alteration maintains the class balance
 */
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
/**
 * Removes all the UCs of a Class of the Student Schedule
 * Time Complexity: O(n)
 * @param dataset dataset to be changed
 * @param classToRemove classCode of the Class to Remove
 * @return if the request was successful
 */
bool Request::removeClass(DataSet& dataset,CollegeClass classToRemove) {
    list<Lesson> newLessons;
    list<Lesson> studentLessons = this->student.get_studentSchedule().get_scheduleLessons();
    cout<<"asd"<<'\n';
    int numStudentsClass = dataset.maxStudentUcInClass(classToRemove.get_classCode());
    cout<<"asd"<<'\n';
    if(maintainsClassBalance(classToRemove.get_classCode(),numStudentsClass)){
        for(Lesson lesson : studentLessons){
            if(lesson.get_LessonClass().get_classCode() != classToRemove.get_classCode()) {
                newLessons.push_back(lesson);
            }
        }
    }
    dataset.setStudentSchedule(newLessons,this->student);
    return true;
}
/**
 * Switches all the UCs of a Class into the Student Schedule
 * Time Complexity: O(n)
 * @param dataset
 * @param classToRemove classCode of the Class to Remove
 * @param classToAdd classCode of the Class to Add
 * @return
 */
bool Request::switchClass(DataSet& dataset,CollegeClass classToRemove, CollegeClass classToAdd) {
    removeClass(dataset,classToRemove);
    addClass(dataset,classToAdd);
    return true;
}
/**
 * Checks if a given list of Lesson conflicts with the Student Schedule
 * Time Complexity: O(n²)
 * @param studentLessons list of lessons of the Student Schedule
 * @param lessonsToCompare list of Lesson to be compared
 * @return if the Schedule conflicts with the list of Lesson
 */
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
/**
 * Adds a given UC into the Student Schedule
 * Time Complexity: O(n²)
 * @param dataset dataset to be changed
 * @param ucToAdd ucCode of the Uc to add
 * @return if the request was successful
 */
bool Request::addUc(DataSet& dataset,CollegeClass ucToAdd) {
    map<Student,list<CollegeClass>> currentUcs = Parser::mapCollegeClasses();
    map<string,list<string>> allUcClass = Parser::getClassesByUcs();
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
/**
 * Removes a given Uc of the Student Schedule
 * Time Complexity: O(n)
 * @param dataset dataset to be changed
 * @param classToRemove ucCode of the Uc to Remove
 * @return if the request was successful
 */
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
/**
 * Switches a given UC of the Student Schedule
 * Time Complexity: O(n)
 * @param dataset
 * @param ucToRemove ucCode of the Uc to Remove
 * @param ucToAdd ucCode of the Uc to Add
 * @return
 */
bool Request::switchUc(DataSet& dataset,CollegeClass UcToRemove,CollegeClass UcToAdd) {
    return removeUc(dataset,UcToRemove) && addUc(dataset,UcToAdd);
}