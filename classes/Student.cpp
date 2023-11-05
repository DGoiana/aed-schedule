#include "Student.h"
#include "Schedule.h"
#include <iostream>

Student::Student(){
    this->studentCode = "";
    this->studentName = "";
    this->studentClasses = {};
}

Student::Student(string studentCode, string studentName, vector<CollegeClass> studentClasses){
    this->studentCode = studentCode;
    this->studentName = studentName;
    this->studentClasses = studentClasses;
}

string Student::get_studentCode() const{
    return this->studentCode;
}

string Student::get_studentName() const{
    return this->studentName;
}

vector<CollegeClass> Student::get_studentClasses() const{
    return this->studentClasses;
}

void Student::set_studentCode(string new_studentCode){
    this->studentCode = new_studentCode;
}

void Student::set_studentName(const string& new_studentName){
    this->studentName = new_studentName;
}

void Student::set_studentClasses(const vector<CollegeClass>& new_studentClasses){
    cout << "Setting student classes" << endl;
    this->studentClasses = new_studentClasses;
}

void Student::add_studentClass(CollegeClass &c){
    this->studentClasses.push_back(c);
}

bool Student::operator<(Student student2) const{
    return this->get_studentCode() < student2.get_studentCode();
}

bool Student::operator==(Student student2) const
{
    return this->get_studentCode() == student2.get_studentCode();
}
