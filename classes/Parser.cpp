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
        CollegeClass lessonClass = CollegeClass(lesson[0]);
        Uc lessonUc = Uc(lesson[1]);
        string lessonWeekday = lesson[2];
        double lessonStartHour = stod(lesson[3]);
        double lessonDuration = stod(lesson[4]);
        string lessonType = lesson[5];
        lessons.push_back(Lesson(lessonClass,lessonUc,lessonWeekday,lessonStartHour,lessonDuration,lessonType));
    }
    return lessons;
}

map<long long, Student> Parser::parseStudentClasses() {
    map<long long, Student> students;
    list<vector<string>> fileRead = readFile("../schedule/students_classes.csv");
    list<Lesson> globalLessons = parseClassesFile();

    for(vector<string> student : fileRead) {
        string studentCollegeClassTrimmed = student[3].substr(0,student[3].length()-1);
        Lesson studentLesson = Lesson(
                CollegeClass(studentCollegeClassTrimmed),
                Uc(student[2]),
                "*",0,0,"*"
        );
        Schedule studentSchedule= Schedule(findLesson(globalLessons,studentLesson));
        long long studentCode = stoll(student[0]);

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
    for(Lesson lesson : globalLessons) {
        if(lesson.get_LessonClass().get_classCode() == lessonToFind.get_LessonClass().get_classCode()
        && lesson.get_LessonUc().get_ucCode() == lessonToFind.get_LessonUc().get_ucCode())
            return {lesson};
    }
    return list<Lesson>();
}
