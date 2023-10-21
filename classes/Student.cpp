#include "Student.h"
#include "Schedule.h"

Student::Student(){
    this->studentCode = 0;
    this->studentName = "";
    this->studentSchedule = Schedule();
}

Student::Student(long studentCode, string studentName, Schedule studentSchedule){
    this->studentCode = studentCode;
    this->studentName = studentName;
    this->studentSchedule = studentSchedule;
}

long Student::get_studentCode() const{
    return this->studentCode;
}

string Student::get_studentName() const{
    return this->studentName;
}

Schedule Student::get_studentSchedule() const{
    return this->studentSchedule;
}

void Student::set_studentCode(long new_studentCode){
    this->studentCode = new_studentCode;
}

void Student::set_studentName(const string& new_studentName){
    this->studentName = new_studentName;
}

void Student::set_studentSchedule(const Schedule& new_studentSchedule){
    this->studentSchedule = new_studentSchedule;
}

bool Student::operator<(Student student2) const{
    return this->studentCode < student2.studentCode;
}