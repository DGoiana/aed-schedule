#include "Dataset.h"
#include <list>
#include <string>
#include "Student.h"
#include "Lesson.h"
#include "Parser.h"

using namespace std;

DataSet::DataSet(){
    this->students = Parser::parseStudents();
    this->lessons = Parser::mapLessons();
}

Schedule DataSet::getScheduleByStudent(string studentCode){
    for(Student s : students){
        if(s.get_studentCode() == studentCode) return s.get_studentSchedule();
    }
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
    return students;
}

list<Student> DataSet::getStudentsByYear(string year){
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