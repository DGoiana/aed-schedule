#ifndef AED_SCHEDULE_STUDENT_H
#define AED_SCHEDULE_STUDENT_H

#include <string>
#include <list>
#include "Schedule.h"

using namespace std;

class Student {
    private:
        long studentCode;
        string studentName;
        Schedule studentSchedule;
    public:
        Student();
        Student(long studentCode, string studentName, Schedule studentSchedule);
        long get_studentCode() const;
        string get_studentName() const;
        Schedule get_studentSchedule() const;
        void set_studentCode(long new_studentCode);
        void set_studentName(const string& new_studentName);
        void set_studentSchedule(const Schedule& new_studentSchedule);
        bool operator<(Student student2) const;
};

#endif