#include "Dataset.h"
#include <list>
#include <string>
#include "Student.h"
#include "Lesson.h"
#include <iostream>
#include "Parser.h"

using namespace std;

DataSet::DataSet(){
    // CHANGE TO POINTER
    this->students = Parser::parseStudents();
    this->lessons = Parser::mapLessons();
}

Schedule DataSet::getScheduleByStudent(string studentCode){
    for(Student s : students){
        if(s.get_studentCode() == studentCode) return s.get_studentSchedule();
    }
    return Schedule();
}

Schedule DataSet::getScheduleByClass(string classCode){
    Schedule result;
    auto it = lessons.begin();
    while(it != lessons.end()){
        if(it->first.get_classCode() == classCode) result.addLessonsFromList(it->second);
        it++;
    }
    return result;
}

list<Student> DataSet::getStudentsByClassOrUc(string code, string id){
    list<Student> students;
    for(Student s : this->students){
        for(Lesson l : s.get_studentSchedule().get_scheduleLessons()){
            if(l.get_LessonClass().get_classCode() == code && id == "class") students.push_back(s);
            if(l.get_LessonClass().get_ucCode() == code && id == "uc") students.push_back(s);
        }
    }
    students.unique();
    return students;
}

int DataSet::getNumStudentsInClassAndUc(CollegeClass ucClass)
{
    list<Student> resultStudents;
    for(Student student : this->students) {
        for(Lesson lesson : student.get_studentSchedule().get_scheduleLessons()) {
            if(lesson.get_LessonClass() == ucClass) resultStudents.push_back(student); 
        }
    }
    resultStudents.unique();
    return resultStudents.size();
}

int DataSet::getNumStudentsInClass(string classCode)
{
    list<Student> resultStudents = getStudentsByClassOrUc(classCode,"class");
    return resultStudents.size();
}

int DataSet::maxStudentUcInClass(string classCode)
{
    map<string,list<string>> ucsByClasses = Parser::getUcsByClasses();
    list<string> ucsByClass = ucsByClasses[classCode];
    int max = 0;
    for(string uc : ucsByClass) {
        int ucClassStudents =  getNumStudentsInClassAndUc(CollegeClass(classCode,uc));
        if(ucClassStudents > max) max = ucClassStudents;
    }
    return max;
}

list<Student> DataSet::getStudentsByYear(string year)
{
    list<Student> students;
    for(Student s : this->students){
        if(s.get_studentCode().substr(0,4) == year) students.push_back(s);
    }
    return students;
}

int DataSet::numStudentsRegisteredInUcs(int num){
    int result = 0;
    map<Student, list<CollegeClass>> mappedCollegeClasses = Parser::mapCollegeClasses();
    for(auto p : mappedCollegeClasses){
        string ucToCheck = "";
        for(CollegeClass c : p.second){
            if(c.get_ucCode() != ucToCheck) result++;
            ucToCheck = c.get_ucCode();
        }
    }
    return result;
}

int DataSet::consultClassorUcOccupation(string code, string id){
    int num = 0;
    for(Student s : this->students){
        for(Lesson l : s.get_studentSchedule().get_scheduleLessons()){
            if(l.get_LessonClass().get_classCode() == code && id == "class") num++;
            if(l.get_LessonClass().get_ucCode() == code && id == "uc") num++;
        }
    }
    return num;
}

int DataSet::consultYearOccupation(string year){
    int num = 0;
    for(Student s : this->students){
        if(s.get_studentCode().substr(0,4) == year) num++;
    }
    return num;
}

void DataSet::setStudentSchedule(list<Lesson> newLessons,Student student) {
    this->students.erase(this->students.find(student));
    student.set_studentSchedule(newLessons);
    this->students.insert(student);
}

Student DataSet::getStudentByNumber(string studentCode)
{
    return *this->students.find(Student(studentCode,"",Schedule()));
}

list<Student> DataSet::getStudentByName(string studentName)
{
    list<Student> sameNameStudents;
    for(Student student : this->students){
        if(student.get_studentName() == studentName)
            sameNameStudents.push_back(student);
    }
    return sameNameStudents;
}
