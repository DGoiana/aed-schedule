#include "Lesson.h"
#include <iostream>

Lesson::Lesson(){
    this->lessonWeekday = "";
    this->lessonStartHour = 0.0;
    this->lessonDuration = 0.0;
    this->lessonType = "";
    this->lessonClass = CollegeClass(); 
}

Lesson::Lesson(CollegeClass lessonClass,string lessonWeekday,double lessonStartHour,double lessonDuration,string lessonType){
    this->lessonWeekday = lessonWeekday;
    this->lessonStartHour = lessonStartHour;
    this->lessonDuration = lessonDuration;
    this->lessonType = lessonType;
    this->lessonClass = lessonClass;  
}

string Lesson::get_LessonWeekday() const {
    return this->lessonWeekday;
}

void Lesson::set_LessonWeekday(const string& new_lessonWeekday) {
    this->lessonWeekday = new_lessonWeekday;
}

double Lesson::get_LessonStartHour() const {
    return this->lessonStartHour;
}

void Lesson::set_LessonStartHour(double new_lessonStartHour) {
    this->lessonStartHour = new_lessonStartHour;
}

double Lesson::get_LessonDuration() const {
    return this->lessonDuration;
}

void Lesson::set_LessonDuration(double new_lessonDuration) {
    this->lessonDuration = new_lessonDuration;
}

string Lesson::get_LessonType() const {
    return this->lessonType;
}

void Lesson::set_LessonType(const string& new_lessonType) {
    this->lessonType = new_lessonType;
}

CollegeClass Lesson::get_LessonClass() const {
    return this->lessonClass;
}

void Lesson::set_LessonClass(const CollegeClass& new_lessonClass) {
    this->lessonClass = new_lessonClass;
}

void Lesson::printLesson() {
    cout << this->lessonClass.get_classCode() << ", ";
    cout << this->lessonClass.get_ucCode() << ", ";
    cout << this->lessonWeekday << ", ";
    cout << this->lessonStartHour << ", ";
    cout << this->lessonDuration << ", ";
    cout << this->lessonType << endl;
}

bool Lesson::operator==(Lesson lesson2) const {
    return this->get_LessonClass() == lesson2.get_LessonClass() 
    && this->get_LessonType() == lesson2.get_LessonType();
}