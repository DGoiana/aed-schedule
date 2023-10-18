#include "Lesson.h"

Lesson::Lesson(){
    this->lessonWeekday = "";
    this->lessonStartHour = 0.0;
    this->lessonDuration = 0.0;
    this->lessonType = "";
    this->lessonUc = Uc();
    this->lessonClass = CollegeClass(); 
}

Lesson::Lesson(string lessonWeekday, double lessonStartHour, double lessonDuration, string lessonType, Uc lessonUc, CollegeClass lessonClass){
    this->lessonWeekday = lessonWeekday;
    this->lessonStartHour = lessonStartHour;
    this->lessonDuration = lessonDuration;
    this->lessonType = lessonType;
    this->lessonUc = lessonUc;
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

Uc Lesson::get_LessonUc() const {
    return this->lessonUc;
}

void Lesson::set_LessonUc(const Uc& new_lessonUc) {
    this->lessonUc = new_lessonUc;
}

CollegeClass Lesson::get_LessonClass() const {
    return this->lessonClass;
}

void Lesson::set_LessonClass(const CollegeClass& new_lessonClass) {
    this->lessonClass = new_lessonClass;
}