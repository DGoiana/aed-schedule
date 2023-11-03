#include "CollegeClass.h"

CollegeClass::CollegeClass(){
    this->classCode = "";
    this->ucCode = "";
    this->registeredStudents = {};
    this->collegeClassSchedule = Schedule();
}

CollegeClass::CollegeClass(string classCode, string ucCode, set<Student> registeredStudents, Schedule collegeClassSchedule){
    this->ucCode = ucCode;
    this->classCode = classCode;
    this->collegeClassSchedule = collegeClassSchedule;
    this->registeredStudents = registeredStudents;
}

string CollegeClass::get_classCode() const{
    return this->classCode;
}

string CollegeClass::get_ucCode() const{
    return this->ucCode;
}

set<Student> CollegeClass::get_registeredStudents() const {
    return this->registeredStudents;
}

Schedule CollegeClass::get_collegeClassSchedule() const {
    return this->collegeClassSchedule;
}

void CollegeClass::set_classCode(const string& new_classCode){
    this->classCode = new_classCode;
}

void CollegeClass::set_ucCode(const string& new_ucCode){
    this->ucCode = new_ucCode;
}

void CollegeClass::set_collegeClassSchedule(const Schedule& new_collegeClassSchedule) {
    this->collegeClassSchedule = new_collegeClassSchedule;
}

void CollegeClass::set_registeredStudents(const set<Student>& new_registeredStudents) {
    this->registeredStudents = new_registeredStudents;
}

bool CollegeClass::operator==(CollegeClass college_class) const {
    return this->ucCode == college_class.get_ucCode() && this->classCode == college_class.get_classCode();
}

bool CollegeClass::operator<(CollegeClass college_class) const {
    string toCompare = college_class.get_ucCode() + college_class.get_classCode();
    string thisToCompare = ucCode + classCode;
    return thisToCompare < toCompare;
}
