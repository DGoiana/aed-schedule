#ifndef AED_SCHEDULE_STUDENT_H
#define AED_SCHEDULE_STUDENT_H

#include <string>
#include <set>
#include "CollegeClass.h"

using namespace std;
class CollegeClass;

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second); 

        // Mainly for demonstration purposes, i.e. works but is overly simple
        // In the real world, use sth. like boost.hash_combine
        return h1 ^ h2;  
    }
};

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