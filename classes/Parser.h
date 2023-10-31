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
    static map<CollegeClass, list<Lesson>> mapLessons();
    static map<string,list<string>> getUcsByClasses();
    static set<string> parseClassCodes();
    static set<string> parseUcCodes();
    static vector<string> split(std::string line,const std::string& delimiter);
    static list<vector<string>> readFile(const std::string &path);
    static list<Lesson> parseClassesFile();
    static set<Student> parseStudents();
    static list<Lesson> findLesson(list<Lesson> globalLessons, Lesson lessonToFind);
    static map<Student, list<CollegeClass>> mapCollegeClasses();
    void printLessons(list<Lesson> lessons);
};
#endif //AED_SCHEDULE_PARSER_H
