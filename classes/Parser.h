#ifndef AED_SCHEDULE_PARSER_H
#define AED_SCHEDULE_PARSER_H

#include <list>
#include <string>
#include <vector>
#include <set>
#include "Lesson.h"
#include "Student.h"
#include <map>

using namespace std;

class Parser {
public:
    vector<string> split(std::string line,const std::string& delimiter);
    list<vector<string>> readFile(const std::string &path);
    list<Lesson> parseClassesFile();
    map<long long, Student> parseStudentClasses();
    list<Lesson> findLesson(list<Lesson> globalLessons, Lesson lessonToFind);
    void printLessons(list<Lesson> lessons);
};
#endif //AED_SCHEDULE_PARSER_H
