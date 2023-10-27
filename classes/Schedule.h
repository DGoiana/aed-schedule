#ifndef AED_SCHEDULE_SCHEDULE_H
#define AED_SCHEDULE_SCHEDULE_H

#include <string>
#include <list>
#include "Lesson.h"

using namespace std;

class Schedule {
    private:
        list<Lesson> scheduleLessons;
    public:
        Schedule();
        Schedule(list<Lesson> scheduleLessons);
        list<Lesson> get_scheduleLessons() const;
        void set_scheduleLessons(list<Lesson> new_scheduleLessons);
        void addLessonsFromList(list<Lesson> lessons);
};

#endif