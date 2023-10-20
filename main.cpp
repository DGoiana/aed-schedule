#include <stdlib.h>
#include "classes/Menu.h"
#include "classes/allMenus.h"
#include "classes/Parser.h"
#include <iostream>

using namespace std;

int main(){
    /*FOR TESTING THE PARSER
    Parser parser;
    set<Student> students = parser.parseStudentClasses();
    for(const Student& student : students) {
        cout << student.get_studentName() << ", " << student.get_studentCode() << endl;
        parser.printLessons(student.get_studentSchedule().get_scheduleLessons());
    }
     */
    AllMenus();
    return 0;
}