#include "CollegeClass.h"

CollegeClass::CollegeClass(){
    this->classCode = "";
}

CollegeClass::CollegeClass(string classCode){
    this->classCode = classCode;
}

string CollegeClass::get_classCode() const{
    return this->classCode;
}

void CollegeClass::set_classCode(const string& new_classCode){
    this->classCode = new_classCode;
}