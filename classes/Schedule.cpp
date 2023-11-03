#include "Schedule.h"
#include "Lesson.h"

Schedule::Schedule(){
}

Schedule::Schedule(list<Lesson> scheduleLessons){
    this->scheduleLessons = scheduleLessons;
}

list<Lesson> Schedule::get_scheduleLessons() const{
    return this->scheduleLessons;
}

void Schedule::set_scheduleLessons(list<Lesson> new_scheduleLessons){
    this->scheduleLessons = new_scheduleLessons;
}

void Schedule::addLessonsFromList(list<Lesson> lessons){
    for(Lesson l : lessons) this->scheduleLessons.push_back(l);
}

void Schedule::addLesson(Lesson lesson){
    this->scheduleLessons.push_back(lesson);
}