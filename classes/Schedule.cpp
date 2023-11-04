#include "Schedule.h"
#include "Lesson.h"

Schedule::Schedule(){
}

Schedule::Schedule(vector<Lesson> scheduleLessons){
    this->scheduleLessons = scheduleLessons;
}

vector<Lesson> Schedule::get_scheduleLessons() const{
    return this->scheduleLessons;
}

void Schedule::set_scheduleLessons(vector<Lesson> new_scheduleLessons){
    this->scheduleLessons = new_scheduleLessons;
}

void Schedule::addLessonsFromList(vector<Lesson> lessons){
    for(Lesson l : lessons) this->scheduleLessons.push_back(l);
}

void Schedule::addLesson(Lesson lesson){
    this->scheduleLessons.push_back(lesson);
}