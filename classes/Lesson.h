#ifndef AED_SCHEDULE_LESSON_H
#define AED_SCHEDULE_LESSON_H

#include <string>
#include <list>

using namespace std;
/**
 * This class represents a given lesson, which has:
 * <ul>
 *  <li> a week day
 *  <li> a start hour
 *  <li> a duration
 *  <li> a type
 *  <li> an identifier of the combination of Class and Uc.
 * <ul>
 */
class Lesson{
    private:
        string lessonWeekday;
        double lessonStartHour;
        double lessonDuration;
        string lessonType;
        pair<string, string> lessonCodes;
    public:
        Lesson();
        Lesson(pair<string, string> lessonCodes,
               string lessonWeekday,
               double lessonStartHour,
               double lessonDuration,
               string lessonType);

        string get_LessonWeekday() const;
        void set_LessonWeekday(const string& new_lessonWeekday);

        double get_LessonStartHour() const;
        void set_LessonStartHour(double new_lessonStartHour);

        double get_LessonDuration() const;
        void set_LessonDuration(double new_lessonDuration);

        string get_LessonType() const;
        void set_LessonType(const string& new_lessonType);

        string get_classCode() const;
        string get_ucCode() const;
        void set_LessonCodes(const pair<string, string> &new_classCodes);

        void printLesson();
        bool operator==(Lesson lesson2) const;
};

#endif