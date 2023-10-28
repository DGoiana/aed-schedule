#include <iostream>
#include "Dataset.h"
#include "Parser.h"
#include "Student.h"


void testListingFunctions() {
    DataSet dataset;
    Parser parser;
    
    cout << "Class Schedule Example: " << '\n';
    Schedule exampleClassSchedule = dataset.getScheduleByClass("1LEIC01");
    parser.printLessons(exampleClassSchedule.get_scheduleLessons());
    cout << '\n';

    cout << "Student Schedule Example: " << '\n';
    Schedule exampleStudentSchedule = dataset.getScheduleByStudent("202028717");
    parser.printLessons(exampleStudentSchedule.get_scheduleLessons());
    cout << '\n';
    
    
    cout << "Uc Students Example: " << '\n';
    list<Student> exampleUcStudents = dataset.getStudentsByClassOrUc("L.EIC003","uc");
    for(Student student: exampleUcStudents) {
        cout << student.get_studentName() << " " << student.get_studentCode() << '\n';
    }
    cout << '\n';

    cout << "Class Students Example: " << '\n';
    list<Student> exampleClassStudents = dataset.getStudentsByClassOrUc("1LEIC01","class");
    for(Student student: exampleClassStudents) {
        cout << student.get_studentName() << " " << student.get_studentCode() << '\n';
    }
    cout << '\n';

    cout << "Year Students Example: " << '\n';
    list<Student> exampleYearStudents = dataset.getStudentsByYear("2020");
    for(Student student: exampleYearStudents) {
        cout << student.get_studentName() << " " << student.get_studentCode() << '\n';
    }
    cout << '\n';
    
    cout << "Num Student Registered in UC example: NOT WORKING ";
    cout << dataset.numStudentsRegisteredInUcs(1) << '\n';

    cout << "Consult Class Occupation Example: ";
    cout << dataset.consultClassorUcOccupation("1LEIC01","class") << '\n';

    cout << "Consult UC Occupation Example: ";
    cout << dataset.consultClassorUcOccupation("L.EIC003","uc") << '\n';

    cout << "Consult Year Occupation Example: ";
    cout << dataset.consultYearOccupation("2020") << '\n';

}