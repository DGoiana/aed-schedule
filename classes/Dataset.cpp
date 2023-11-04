#include "Dataset.h"
#include <list>
#include <string>
#include "Student.h"
#include <iostream>
#include "Parser.h"
#include <algorithm>
#include <fstream>

using namespace std;

DataSet::DataSet(){
    this->students = Parser::parseStudents();
    sort(this->students.begin(),this->students.end()); // for binary search purposes
    this->collegeClasses = Parser::parseCollegeClasses();
}

Student DataSet::binarySearchStudentbyNumber(string classCode) {
    int h = students.size() - 1;
    int l = 0;
    while(l <= h) {
        int m = l + (h-l) / 2;
        if(this->students[m].get_studentCode() == classCode) return this->students[m];
        if(this->students[m].get_studentCode() < classCode) l = m + 1;
        else h = m - 1;
    }
    return Student();
}

Schedule DataSet::getScheduleByStudent(string studentCode){
    Schedule schedule;
    Student foundStudent = binarySearchStudentbyNumber(studentCode);
    for(CollegeClass c : foundStudent.get_studentClasses()) {
        schedule.addLessonsFromList(c.get_collegeClassSchedule().get_scheduleLessons());
    }
    return schedule;
}

Schedule DataSet::getScheduleByClass(string classCode){
    Schedule schedule;
    for(CollegeClass c : collegeClasses){
        if(c.get_classCode() == classCode){
            schedule.addLessonsFromList(c.get_collegeClassSchedule().get_scheduleLessons());
        }
    }
    return schedule;
}

vector<Student> DataSet::getStudentsByClassOrUc(string code, string id){
    set<Student> students;
    for(CollegeClass c : collegeClasses){
        if(c.get_classCode() == code && id == "class"){
            for(Student s : c.get_registeredStudents()){
                students.insert(s);
            }
        }
        if(c.get_ucCode() == code && id == "uc"){
            for(Student s : c.get_registeredStudents()){
                students.insert(s);
            }
        }
    }
    return vector<Student>(students.begin(), students.end());
}

vector<string> DataSet::getClasses(){
    vector<string> classes;
    for(CollegeClass c : collegeClasses){
        if(find(classes.begin(), classes.end(), c.get_classCode()) != classes.end()) continue;
        classes.push_back(c.get_classCode());
    }
    return classes;
}

vector<string> DataSet::getUcs(){
    vector<string> ucs;
    for(CollegeClass c : collegeClasses){
        if(find(ucs.begin(), ucs.end(), c.get_ucCode()) != ucs.end()) continue;
        ucs.push_back(c.get_ucCode());
    }
    return ucs;
}

vector<string> DataSet::getStudents(){
    vector<string> students_codes;
    for(Student s : this->students){
        students_codes.push_back(s.get_studentCode());
    }
    return students_codes;
}

int DataSet::getNumStudentsInClassAndUc(CollegeClass ucClass)
{
    for(CollegeClass c : collegeClasses){
        if(c == ucClass) return c.get_registeredStudents().size();
    }
    return 0;
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
    for(Student s : students){
        if(s.get_studentClasses().size() >= num) count++;
    }
    return count;
}

int DataSet::consultClassorUcOccupation(string code, string id){
    return getStudentsByClassOrUc(code, id).size();
}

int DataSet::consultYearOccupation(string year){
    return getStudentsByYear(year).size();
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
    for(string uc: getUcs()){
        if(consultClassorUcOccupation(uc, "uc") > num){
            result = uc;
            num = consultClassorUcOccupation(uc, "uc");
        }
    }
    return result;
}


//CHECK
void DataSet::setStudentClasses(set<CollegeClass> newClasses, Student student) {
    auto it = find(students.begin(), students.end(), student);
    it->set_studentClasses(newClasses);
}

void DataSet::addStudentClass(CollegeClass c, Student student){
   auto it = find(students.begin(), students.end(), student);
   it->add_studentClass(c);
}

Student DataSet::getStudentByNumber(string studentCode)
{
    return binarySearchStudentbyNumber(studentCode);
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

void DataSet::dumpCurrentState() {
    ofstream output("../schedule/students_classes.csv");
    output << "StudentCode,StudentName,UcCode,ClassCode" << '\n';
    for(Student student : this->students) {
        for(CollegeClass cc : student.get_studentClasses()) {
            output << student.get_studentCode() <<","<< student.get_studentName() << "," << cc.get_ucCode() << "," << cc.get_classCode() << "\r\n";
        }
    }
}
