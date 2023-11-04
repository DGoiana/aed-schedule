#pragma once

#include <set>
#include <string>
#include "Schedule.h"
#include "Student.h"

using namespace std;
class Student;

class CollegeClass {
    private:
        string classCode;
        string ucCode;
        vector<Student> registeredStudents;
        Schedule collegeClassSchedule;
    public:
        CollegeClass();
        CollegeClass(string classCode, string ucCode, vector<Student> registeredStudents, Schedule collegeClassSchedule);

        string get_classCode() const;
        void set_classCode(const string& new_classCode);

        string get_ucCode() const;
        void set_ucCode(const string& new_ucCode);

        vector<Student> get_registeredStudents() const;
        void set_registeredStudents(const vector<Student>& new_registeredStudents);

        Schedule get_collegeClassSchedule() const;
        void set_collegeClassSchedule(const Schedule& new_collegeClassSchedule);
        
        bool operator==(CollegeClass college_class) const;
        bool operator<(CollegeClass college_class) const;
};
