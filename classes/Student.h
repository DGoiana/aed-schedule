#ifndef AED_SCHEDULE_STUDENT_H
#define AED_SCHEDULE_STUDENT_H

#include <string>
#include <list>
#include "Schedule.h"

using namespace std;

class Student {
    private:
        string studentCode;
        string studentName;
        Schedule studentSchedule;
    public:
        Student();
        Student(string studentCode, string studentName, Schedule studentSchedule);
        string get_studentCode() const;
        string get_studentName() const;
        Schedule get_studentSchedule() const;
        void set_studentCode(string new_studentCode);
        void set_studentName(const string& new_studentName);
        void set_studentSchedule(const Schedule& new_studentSchedule);
        bool operator<(Student student2) const;
};

#endif