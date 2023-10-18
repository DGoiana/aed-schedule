#include "Uc.h"

Uc::Uc(){
    this->ucCode = "";
}

Uc::Uc(string ucCode){
    this->ucCode = ucCode;
}

string Uc::get_ucCode() const{
    return this->ucCode; 
}

void Uc::set_ucCode(const string& new_ucCode){
    this->ucCode = new_ucCode;
}