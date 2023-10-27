#include "Dataset.h"
#include <list>
#include <string>
#include "Student.h"
#include "Lesson.h"
#include "Parser.h"

using namespace std;

DataSet::DataSet(){
    this->students = Parser::parseStudentClasses();
    this->lessons = Parser::parseClassesFile();
}

Schedule DataSet::getScheduleByStudent(long studentCode){
    return this->students[studentCode].get_studentSchedule();
}