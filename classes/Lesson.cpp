#include "Lesson.h"
#include <iostream>

Lesson::Lesson(){
    this->lessonWeekday = "";
    this->lessonStartHour = 0.0;
    this->lessonDuration = 0.0;
    this->lessonType = "";
    this->lessonCodes = {}; 
}

Lesson::Lesson(pair<string, string> lessonCodes,string lessonWeekday,double lessonStartHour,double lessonDuration,string lessonType){
    this->lessonWeekday = lessonWeekday;
    this->lessonStartHour = lessonStartHour;
    this->lessonDuration = lessonDuration;
    this->lessonType = lessonType;
    this->lessonCodes = lessonCodes;  
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

string Lesson::get_classCode() const {
    return this->lessonCodes.first;
}

string Lesson::get_ucCode() const {
    return this->lessonCodes.second;
}

void Lesson::set_LessonCodes(const pair<string, string>& new_lessonCodes) {
    this->lessonCodes = new_lessonCodes;
}

void Lesson::printLesson() {
    cout << this->lessonCodes.first << ", ";
    cout << this->lessonCodes.second << ", ";
    cout << this->lessonWeekday << ", ";
    cout << this->lessonStartHour << ", ";
    cout << this->lessonDuration << ", ";
    cout << this->lessonType << endl;
}

bool Lesson::operator==(Lesson lesson2) const {
    return this->lessonCodes.first == lesson2.lessonCodes.first 
    && this->lessonCodes.second == lesson2.lessonCodes.second
    && this->lessonType == lesson2.get_LessonType();
}