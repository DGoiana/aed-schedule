#include "Dataset.h"
#include <list>
#include <string>
#include "Student.h"
#include "Lesson.h"
#include <iostream>
#include "Parser.h"
#include <algorithm>

using namespace std;

DataSet::DataSet(){
    // CHANGE TO POINTER
    this->students = Parser::parseStudents();
    this->lessons = Parser::mapLessons();
    this->ucs = Parser::parseUcCodes();
    this->classes = Parser::parseClassCodes();
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

vector<Student> DataSet::getStudentsByClassOrUc(string code, string id){
    set<Student> students;
    for(Student s : this->students){
        for(Lesson l : s.get_studentSchedule().get_scheduleLessons()){
            if(l.get_LessonClass().get_classCode() == code && id == "class") students.insert(s);
            if(l.get_LessonClass().get_ucCode() == code && id == "uc") students.insert(s);
        }
    }
    vector<Student> result(students.begin(), students.end());
    return result;
}

int DataSet::getNumStudentsInClassAndUc(CollegeClass ucClass)
{
    set<Student> resultStudents;
    for(Student student : this->students) {
        for(Lesson lesson : student.get_studentSchedule().get_scheduleLessons()) {
            if(lesson.get_LessonClass() == ucClass) resultStudents.insert(student); 
        }
    }
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

vector<Student> DataSet::getStudentsByYear(string year){
    set<Student> students;
    for(Student s : this->students){
        if(s.get_studentCode().substr(0,4) == year) students.insert(s);
    }
    vector<Student> result(students.begin(), students.end());
    return result;
}

int DataSet::numStudentsRegisteredInNUcs(int num){
    int count = 0;
    map<Student, list<CollegeClass>> mappedCollegeClasses = Parser::mapCollegeClasses();
    for(auto p : mappedCollegeClasses){
        int result = 0;
        string ucToCheck = "";
        for(CollegeClass c : p.second){
            if(c.get_ucCode() != ucToCheck) result++;
            ucToCheck = c.get_ucCode();
        }
        if(result >= num) count++;
    }
    return count;
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

void DataSet::sortStudentsByNameOrYear(vector<Student> &students, string order, string input){
    if(input == "name"){
        if(order == "ascending") sort(students.begin(), students.end(), [](Student s1, Student s2){
            return s1.get_studentName() < s2.get_studentName();
        });
        else sort(students.begin(), students.end(), [](Student s1, Student s2){
            return s1.get_studentName() > s2.get_studentName();
        });
    }
    else{
        if(order == "ascending") sort(students.begin(), students.end(), [](Student s1, Student s2){
            return s1.get_studentCode() < s2.get_studentCode();
        });
        else sort(students.begin(), students.end(), [](Student s1, Student s2){
            return s1.get_studentCode() > s2.get_studentCode();
        });
    }
}

void DataSet::sortClassesByOccupation(vector<string> &codes, string order){
    if(order == "ascending") sort(codes.begin(), codes.end(), [this](string code1, string code2){
        return consultClassorUcOccupation(code1, "class") < consultClassorUcOccupation(code2, "class");
    });
    else sort(codes.begin(), codes.end(), [this](string code1, string code2){
        return consultClassorUcOccupation(code1, "class") > consultClassorUcOccupation(code2, "class");
    });
}

void DataSet::sortUcsByOccupation(vector<string> &codes, string order){
    if(order == "ascending") sort(codes.begin(), codes.end(), [this](string code1, string code2){
        return consultClassorUcOccupation(code1, "uc") < consultClassorUcOccupation(code2, "uc");
    });
    else sort(codes.begin(), codes.end(), [this](string code1, string code2){
        return consultClassorUcOccupation(code1, "uc") > consultClassorUcOccupation(code2, "uc");
    });
}

void DataSet::sortYearsByOccupation(vector<string> &years, string order){
    if(order == "ascending") sort(years.begin(), years.end(), [this](string year1, string year2){
        return consultYearOccupation(year1) < consultYearOccupation(year2);
    });
    else sort(years.begin(), years.end(), [this](string year1, string year2){
        return consultYearOccupation(year1) > consultYearOccupation(year2);
    });
}

string DataSet::getMostStudentsUC(){
    string result;
    int num = 0;
    for(string uc: ucs){
        if(consultClassorUcOccupation(uc, "uc") > num){
            result = uc;
            num = consultClassorUcOccupation(uc, "uc");
        }
    }
    return result;
}


//CHECK
void DataSet::setStudentSchedule(list<Lesson> newLessons,Student student) {
    this->students.erase(this->students.find(student));
    student.set_studentSchedule(newLessons);
    this->students.insert(student);
}

//CHECK
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
