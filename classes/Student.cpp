#include "Student.h"
#include "Schedule.h"
#include <iostream>

Student::Student(){
    this->studentCode = "";
    this->studentName = "";
    this->studentClasses = {};
}

Student::Student(string studentCode, string studentName, set<CollegeClass> studentClasses){
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

set<CollegeClass> Student::get_studentClasses() const{
    return this->studentClasses;
}

void Student::set_studentCode(string new_studentCode){
    this->studentCode = new_studentCode;
}

void Student::set_studentName(const string& new_studentName){
    this->studentName = new_studentName;
}

void Student::set_studentClasses(const set<CollegeClass>& new_studentClasses){
    this->studentClasses = new_studentClasses;
}

void Student::add_studentClass(CollegeClass& c){
    this->studentClasses.insert(c);
}

bool Student::operator<(Student student2) const{
    return this->get_studentCode() < student2.get_studentCode();
}

bool Student::operator==(Student student2) const
{
    return this->get_studentCode() == student2.get_studentCode();
}
