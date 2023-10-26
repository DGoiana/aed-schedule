#ifndef AED_SCHEDULE_COLLEGECLASS_H
#define AED_SCHEDULE_COLLEGECLASS_H

#include <list>
#include <string>

using namespace std;

class CollegeClass {
    private:
        string classCode;
        string ucCode;
        // if parsing through all students classes takes too long, create a list of students
    public:
        CollegeClass();
        CollegeClass(string classCode, string ucCode);
        string get_classCode() const;
        string get_ucCode() const;
        void set_classCode(const string& new_classCode);
        void set_ucCode(const string& new_ucCode);
        bool operator==(CollegeClass college_class) const;
        bool operator<(CollegeClass college_class) const;
};

#endif