#include "Parser.h"
#include "Student.h"
#include <fstream>
#include <iostream>
#include <map>

using namespace std;
vector<string> Parser::split(std::string line, const string &delimiter) {
    size_t pos;
    string token;
    vector<string> result;
    while(line.find(delimiter) != string::npos) {
        pos = line.find(delimiter);
        token = line.substr(0,pos);
        result.push_back(token);
        line = line.substr(pos + delimiter.length());
    }
    result.push_back(line.substr(0));
    return result;
}

list<vector<string>> Parser::readFile(const string &path) {
    ifstream file(path);
    string line;
    list<vector<string>> result;
    while (getline(file,line)) {
        result.push_back(split(line,","));
    }
    file.close();
    result.pop_front();
    return result;
}

list<Lesson> Parser::parseClassesFile() {
    list<Lesson> lessons;
    list<vector<string>> fileRead = readFile("../schedule/classes.csv"); // something like this: [{1LEIC01,L.EIC001,Monday,10.5,1.5,TP}, {1LEIC02,L.EIC001,Thursday,9.5,1.5,TP}]
    for (vector<string> lesson: fileRead) {
        CollegeClass lessonClass = CollegeClass(lesson[0], lesson[1]);
        string lessonWeekday = lesson[2];
        double lessonStartHour = stod(lesson[3]);
        double lessonDuration = stod(lesson[4]);
        string lessonType = lesson[5];
        lessons.push_back(Lesson(lessonClass,lessonWeekday,lessonStartHour,lessonDuration,lessonType));
    }
    return lessons;
}

map<CollegeClass, list<Lesson>> Parser::mapLessons(){
    list<vector<string>> classesPerUc = readFile("../schedule/classes_per_uc.csv"); // [{L.EIC001,1LEIC01}, {L.EIC001,1LEIC02}, ...]
    list<Lesson> allClasses = parseClassesFile();
    map<CollegeClass, list<Lesson>> mappedLessons;
    for(vector<string> classAndUc : classesPerUc){
        string classCodeTrimmed = classAndUc[1].substr(0, classAndUc[1].length() - 1);
        mappedLessons[CollegeClass(classCodeTrimmed, classAndUc[0])] = findLesson(allClasses, Lesson(CollegeClass(classCodeTrimmed, classAndUc[0]), "*", 0, 0, "*"));
    }
    return mappedLessons;
}

map<string, list<string>> Parser::getUcsByClasses() // [LEIC01: {L.EIC01, L.EIC02}, ...]
{
    map<string,list<string>> result;
    list<vector<string>> classesPerUc = readFile("../schedule/classes_per_uc.csv");
    for(vector<string> classAndUc : classesPerUc) {
        string classCodeTrimmed = classAndUc[1].substr(0, classAndUc[1].length() - 1);
        result[classCodeTrimmed].push_back(classAndUc[0]);
    }
    return result;
}

set<string> Parser::parseClassCodes() {
    set<string> classes;
    for(auto p: mapLessons()){
        classes.insert(p.first.get_classCode());
    }
    return classes;
}

set<string> Parser::parseUcCodes() {
    set<string> ucs;
    for(auto p: mapLessons()){
        ucs.insert(p.first.get_ucCode());
    }
    return ucs;
}

set<Student> Parser::parseStudents() {
    set<Student> students;
    map<Student, list<CollegeClass>> mappedCollegeClasses = mapCollegeClasses();
    map<CollegeClass, list<Lesson>> mappedLessons = mapLessons();

    for(const pair<Student, list<CollegeClass>> &p : mappedCollegeClasses) {
        Schedule toCreate;
        for(CollegeClass c : p.second){
            toCreate.addLessonsFromList(mappedLessons[c]);
        }
        students.insert(Student(p.first.get_studentCode(), p.first.get_studentName(), toCreate));
    }
    return students;
}

map<Student, list<CollegeClass>> Parser::mapCollegeClasses(){
    map<Student, list<CollegeClass>> students;
    Schedule schedule;
    list<vector<string>> fileRead = readFile("../schedule/students_classes.csv");
    for(vector<string> student: fileRead){
        string classCodeTrimmed = student[3].substr(0, student[3].length() - 1);
        Student studentObject = Student(student[0], student[1], schedule);
        students[studentObject].push_back(CollegeClass(classCodeTrimmed, student[2]));
    }
    return students;
}

void Parser::printLessons(list<Lesson> lessons) {
    if(lessons.size() == 0) return;
    for(Lesson lesson : lessons) {
        lesson.printLesson();
    }
}

list<Lesson> Parser::findLesson(list<Lesson> globalLessons, Lesson lessonToFind) {
    list<Lesson> lessons;
    for(Lesson lesson : globalLessons) {
        if(lesson.get_LessonClass() == lessonToFind.get_LessonClass())
            lessons.push_back(lesson);
    }
    return lessons;
}
