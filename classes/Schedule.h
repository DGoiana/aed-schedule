#ifndef AED_SCHEDULE_SCHEDULE_H
#define AED_SCHEDULE_SCHEDULE_H

#include <string>
#include <list>
#include "Lesson.h"

using namespace std;

class Schedule {
    private:
        vector<Lesson> scheduleLessons;
    public:
        Schedule();
        Schedule(vector<Lesson> scheduleLessons);
        vector<Lesson> get_scheduleLessons() const;
        void set_scheduleLessons(vector<Lesson> new_scheduleLessons);
        void addLessonsFromList(vector<Lesson> lessons);
        void addLesson(Lesson lesson);
};

#endif