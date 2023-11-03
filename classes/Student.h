#ifndef AED_SCHEDULE_STUDENT_H
#define AED_SCHEDULE_STUDENT_H

#include <string>
#include <set>
#include "CollegeClass.h"

using namespace std;
class CollegeClass;

class Student {
    private:
        string studentCode;
        string studentName;
        set<CollegeClass> studentClasses;
    public:
        Student();
        Student(string studentCode, string studentName, set<CollegeClass> studentClasses);

        string get_studentCode() const;
        void set_studentCode(string new_studentCode);

        string get_studentName() const;
        void set_studentName(const string& new_studentName);

        set<CollegeClass> get_studentClasses() const;
        void set_studentClasses(const set<CollegeClass>& new_studentClasses);
        
        void add_studentClass(CollegeClass& c);
        
        bool operator<(Student student2) const;
        bool operator==(Student student2) const;
};

#endif