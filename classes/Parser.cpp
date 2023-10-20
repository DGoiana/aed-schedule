#include "Parser.h"
#include "Student.h"
#include <set>
#include <vector>
#include <fstream>
#include <iostream>

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
    list<vector<string>> fileRead = readFile("schedule/classes.csv");
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

set<Student> Parser::parseStudentClasses() {
    set<Student> students;
    list<vector<string>> fileRead = readFile("schedule/students_classes.csv");
    list<Lesson> globalLessons = parseClassesFile();
    for(vector<string> student : fileRead) {
        string studentCollegeClassTrimmed = student[3].substr(0,student[3].length()-1);
        Lesson studentLesson = Lesson(
                CollegeClass(studentCollegeClassTrimmed),
                Uc(student[2]),
                "*",0,0,"*"
        );
        Schedule studentSchedule= Schedule(findLesson(globalLessons,studentLesson));
        Student studentToAdd =Student(stoll(student[0]),
                                      student[1],
                                      studentSchedule);
        auto findStudent = students.find(studentToAdd);
        if(findStudent == students.end()){
            students.insert(studentToAdd);
        }
        else{
            list<Lesson> newSchedule = findStudent->get_studentSchedule().get_scheduleLessons();
            newSchedule.push_back(studentSchedule.get_scheduleLessons().front());
            Student newStudent =Student(findStudent->get_studentCode(),
                                        findStudent->get_studentName(),
                                        newSchedule);
            students.erase(findStudent);
            students.insert(newStudent);

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
