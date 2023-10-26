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
        string collegeClassTrimmed = classAndUc[1].substr(0, classAndUc[1].length() - 1);
        mappedLessons[CollegeClass(classAndUc[0], collegeClassTrimmed)] = findLesson(allClasses, Lesson(CollegeClass(collegeClassTrimmed, classAndUc[0]), "*", 0, 0, "*"));
    }
    return mappedLessons;
}

map<long, Student> Parser::parseStudentClasses() {
    map<long, Student> students;
    list<vector<string>> fileRead = readFile("../schedule/students_classes.csv"); // [{202042572,Manuel Andre,L.EIC011,2LEIC12}]
    map<CollegeClass, list<Lesson>> mappedLessons = mapLessons();

    for(vector<string> student : fileRead) {
        Schedule studentSchedule = Schedule(mappedLessons[CollegeClass(student[2], student[3])]);
        long studentCode = stoll(student[0]);

        if(students.count(studentCode) == 0){
            students[studentCode] = Student(studentCode, student[1], studentSchedule);
        }
        else{
            list<Lesson> studentCurrentLessons = students[studentCode].get_studentSchedule().get_scheduleLessons();
            studentCurrentLessons.push_back(studentSchedule.get_scheduleLessons().front());
            students[studentCode].set_studentSchedule(Schedule(studentCurrentLessons));
        }
    }
    return students;
}

void Parser::printLessons(list<Lesson> lessons) {
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
