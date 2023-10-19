#ifndef AED_SCHEDULE_LESSON_H
#define AED_SCHEDULE_LESSON_H

#include <string>
#include <list>
#include "Uc.h"
#include "CollegeClass.h"

using namespace std;

class Lesson{
    private:
        string lessonWeekday;
        double lessonStartHour;
        double lessonDuration;
        string lessonType;
        Uc lessonUc;
        CollegeClass lessonClass;
    public:
        Lesson();
        Lesson(string lessonWeekday,double lessonStartHour,double lessonDuration,string lessonType,Uc lessonUc,CollegeClass lessonClass);
        
        string get_LessonWeekday() const;
        void set_LessonWeekday(const string& new_lessonWeekday);

        double get_LessonStartHour() const;
        void set_LessonStartHour(double new_lessonStartHour);

        double get_LessonDuration() const;
        void set_LessonDuration(double new_lessonDuration);

        string get_LessonType() const;
        void set_LessonType(const string& new_lessonType);

        Uc get_LessonUc() const;
        void set_LessonUc(const Uc& new_lessonUc);

        CollegeClass get_LessonClass() const;
        void set_LessonClass(const CollegeClass& new_lessonClass);
};

#endif