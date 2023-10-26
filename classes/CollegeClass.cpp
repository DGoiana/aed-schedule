#include "CollegeClass.h"

CollegeClass::CollegeClass(){
    this->classCode = "";
}

CollegeClass::CollegeClass(string classCode, string ucCode){
    this->ucCode = ucCode;
    this->classCode = classCode;
}

string CollegeClass::get_classCode() const{
    return this->classCode;
}

string CollegeClass::get_ucCode() const{
    return this->ucCode;
}

void CollegeClass::set_classCode(const string& new_classCode){
    this->classCode = new_classCode;
}

void CollegeClass::set_ucCode(const string& new_ucCode){
    this->ucCode = new_ucCode;
}

bool CollegeClass::operator==(CollegeClass college_class) const {
    return this->ucCode == college_class.get_ucCode() && this->classCode == college_class.get_classCode();
}

bool CollegeClass::operator<(CollegeClass college_class) const {
    string toCompare = college_class.get_ucCode() + college_class.get_classCode();
    string thisToCompare = ucCode + classCode;
    return thisToCompare < toCompare;
}
