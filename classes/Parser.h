#ifndef AED_SCHEDULE_PARSER_H
#define AED_SCHEDULE_PARSER_H

#include <utility>
#include <list>
#include <string>
#include <vector>
#include <set>
#include "Lesson.h"
#include "Student.h"
#include "CollegeClass.h"
#include <map>

using namespace std;

class Parser {
public:
    static list<CollegeClass> parseCollegeClasses();
    static map<string,list<string>> getUcsByClasses();
    static map<CollegeClass, set<Student>> studentsFromCollegeClass();
    static vector<string> split(std::string line,const std::string& delimiter);
    static list<vector<string>> readFile(const std::string &path);
    static list<Lesson> parseClassesFile();
    static map<CollegeClass, list<Lesson>> mapLessons();
    static vector<Student> parseStudents();
    static list<Lesson> findLesson(list<Lesson> globalLessons, Lesson lessonToFind);
    void printLessons(list<Lesson> lessons);
};
#endif //AED_SCHEDULE_PARSER_H
