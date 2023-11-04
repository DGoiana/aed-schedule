#include "allMenus.h"
#include "Schedule.h"
#include "Dataset.h"
#include "Lesson.h"
#include "Student.h"
#include "Request.h"
#include "Parser.h"
#include "CollegeClass.h"
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;


void AllMenus::sortStudentVector(vector<Student>& students){
    string decision;
    string sortOptions =
        "=================================\n"
        "|| 0-Sort by name (ASCENDING)  ||\n"
        "|| 1-Sort by name (DESCENDING) ||\n"
        "|| 2-Sort by year (ASCENDING)  ||\n"
        "|| 3-Sort by year (DESCENDING) ||\n"
        "=================================\n";
    cout << sortOptions;
    cout << "Choose an option: ";
    cin >> decision;
    while(decision != "0" && decision != "1" && decision != "2" && decision != "3") {
        cout << "INVALID SORT OPTION" << '\n';
        cout << sortOptions;
        cin >> decision;
    }
    switch (stoi(decision)) {
        case 0: dataset.sortStudentsByNameOrYear(students,"ascending","name"); break;
        case 1: dataset.sortStudentsByNameOrYear(students,"descending","name"); break;
        case 2: dataset.sortStudentsByNameOrYear(students,"ascending","year"); break;
        case 3: dataset.sortStudentsByNameOrYear(students,"descending","year"); break;
    }
}

AllMenus::AllMenus(DataSet &dataset) {
    this->dataset = dataset;
    menu_principal();
}

void AllMenus::menu_principal(){
    string banner = "==========================================================\n"
                    "||  ____  _             _            _                  ||\n"
                    "|| / ___|| |_ _   _  __| | ___ _ __ | |_                ||\n"
                    "|| \\___ \\| __| | | |/ _` |/ _ \\ '_ \\| __|               ||\n"
                    "||  ___) | |_| |_| | (_| |  __/ | | | |_                ||\n"
                    "|| |____/ \\__|\\__,_|\\__,_|\\___|_| |_|\\__|               ||\n"
                    "||                                                      ||\n"
                    "||  ____       _              _       _                 ||\n"
                    "|| / ___|  ___| |__   ___  __| |_   _| | ___ _ __       ||\n"
                    "|| \\___ \\ / __| '_ \\ / _ \\/ _` | | | | |/ _ \\ '__|      ||\n"
                    "||  ___) | (__| | | |  __/ (_| | |_| | |  __/ |         ||\n"
                    "|| |____/ \\___|_| |_|\\___|\\__,_|\\__,_|_|\\___|_|         ||\n"
                    "==========================================================\n"
                    "                                               ";
    string input;
    string menuOptions =
            " ===================\n"
            " || 0-Schedules   ||\n"
            " || 1-UC's        ||\n"
            " || 2-Students    ||\n"
            " || 3-Occupations ||\n"
            " || 4-Requests    ||\n"
            " || 5-Exit        ||\n"
            " ===================\n";
    do {
        cout << banner << '\n';
        cout << menuOptions;
        cout << "Choose an option: ";
        cin >> input;
        while(input != "0" && input != "1" && input != "2" && input != "3" && input != "4" && input != "5"){
            cout << "INVALID INPUT" << '\n';
            cout << "Choose an option: ";
            cin >> input;
        }
        switch (stoi(input)) {
            case 0:
                menu_schedule();
                break;
            case 1:
                menu_uc();
                break;
            case 2:
                menu_students();
                break;
            case 3:
                menu_occupations();
                break;
            case 4:
                menu_requests();
                break;
            case 5:
                exit(0);
                break;
        }
    } while(input !="5");
}

string AllMenus::toTime(float number) {
    string hour = (int)number < 10 ? "0"+ to_string((int)number) : to_string((int)number);
    string minutes = (int)(number*60)%60 == 0 ? "00" : to_string((int)(number*60)%60);
    return hour+":"+minutes;
}

void AllMenus::showSchedule(list<Lesson> lessons) {
    map<string,list<Lesson>> lessonsInWeekDay;
    vector<string> weekDays = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    for(Lesson lesson : lessons) {
        lessonsInWeekDay[lesson.get_LessonWeekday()].push_back(lesson);
    }
    for(string weekDay : weekDays) {
        cout << "                   " << weekDay << '\n';
        cout << "====================================================\n";
        cout << "   CLASS   ||    UC    || START ||  END  ||  TYPE\n";
        cout << "====================================================\n";
        for(Lesson lesson : lessonsInWeekDay[weekDay]){
            cout << "   " << lesson.get_classCode() << " || " << lesson.get_ucCode()
            << " || " << toTime(lesson.get_LessonStartHour())
            << " || " << toTime(lesson.get_LessonStartHour() + lesson.get_LessonDuration())
            << " || " << lesson.get_LessonType() ;
            cout << '\n';
        }
        cout << "====================================================\n";
        cout << '\n';
    }
}

void AllMenus::menu_schedule() {
    string input;
    string menuOptions =
            "=====================================\n"
            "|| 0-Consult schedule of a student ||\n"
            "|| 1-Consult schedule of a class   ||\n"
            "|| 2-Go back                       ||\n"
            "=====================================\n";
    string studentCode;
    string classCode;
    do {
        cout << menuOptions;
        cout << "Choose an option: ";
        cin >> input;
        switch (stoi(input)) {
            case 0:
                cout << "studentCode: ";
                cin >> studentCode;
                showSchedule(dataset.getScheduleByStudent(studentCode).get_scheduleLessons());
                break;
            case 1:
                cout << "classCode: ";
                cin >> classCode;
                showSchedule(dataset.getScheduleByClass(classCode).get_scheduleLessons());
                break;
            case 2: break;
            default:
                cout << "Invalid option\n";
                break;
        }
    } while(input != "2");
}

void AllMenus::showPages(vector<Student> students) {
    int page = 0;
    string decision;
    do {
        cout << "===============================\n";
        cout << "STUDENT CODE || STUDENT NAME   \n";
        cout << "===============================\n";
        int numStudents = (20*(page+1)) > students.size() ? students.size()%20 : 20;
        for(int i = 0; i < numStudents; i++) {
            Student currentStudent = students[i+(20*page)];
            cout <<"  "<< currentStudent.get_studentCode() << "  || " << currentStudent.get_studentName() << '\n';
        }
        cout << "===============================\n";
        cout << "Page: "<<page+1 << " of " << students.size()/20 + 1 <<'\n';
        cout << "Options: "<<'\n';
        do {
            cout << "0 - Go to next Page" <<'\n';
            cout << "1 - Go to last Page" << '\n';
            cout << "2- Leave" << '\n';
            cin >> decision;
        } while(decision != "0" && decision != "1" && decision != "2");
        if(decision == "0") page++;
        if(decision == "1") page--;
    } while(decision != "2" && 20*(page) <= students.size());
}

void AllMenus::menu_students(){
    string input;
    string menuOptions =
            "================================================================\n"
            "|| 0-Consult students within a given class                    ||\n"
            "|| 1-Consult students within a given Uc                       ||\n"
            "|| 2-Consult students within a given year                     ||\n"
            "|| 3-Consult number of students registered in at least n UCs  ||\n"
            "|| 4-Go back                                                  ||\n"
            "================================================================\n";
    string classCode, ucCode, id, year;
    int n;
    vector<string> sortOptions;
    vector<Student> studentsToBeOrdered;

    do {
        cout << menuOptions;
        cout << "Choose an option: ";
        cin >> input;
        while(input != "0" && input != "1" && input != "2" && input != "3" && input != "4"){
            cout << "INVALID INPUT" << '\n';
            cout << "Choose an option: ";
            cin >> input;
        }
        switch (stoi(input))
        {
            case 0:
                cout << "classCode: ";
                cin >> classCode;

                studentsToBeOrdered = dataset.getStudentsByClassOrUc(classCode, "class");
                sortStudentVector(studentsToBeOrdered);
                showPages(studentsToBeOrdered);
                break;
            case 1:
                cout << "ucCode: ";
                cin >> ucCode;

                studentsToBeOrdered = dataset.getStudentsByClassOrUc(ucCode, "uc");
                sortStudentVector(studentsToBeOrdered);
                showPages(studentsToBeOrdered);
                break;
            case 2:
                cout << "Year: ";
                cin >> year;

                studentsToBeOrdered = dataset.getStudentsByYear(year);
                sortStudentVector(studentsToBeOrdered);
                showPages(studentsToBeOrdered);
                break;
            case 3:
                cout << "Number of Ucs: ";
                cin >> n;

                cout << "==============================================\n";
                cout <<"There are "<< dataset.numStudentsRegisteredInNUcs(n) << " students in at least " << n << " Ucs"<< "\n";
                cout << "==============================================\n";
                break;
            case 4:
                break;
            default:
                cout << "Invalid option\n";
        }
    } while(input != "4");
}

void AllMenus::menu_uc(){
    string input;
    string menuOptions =
            "========================================================\n"
            "|| 0-Consult UCs with the GREATEST number of students ||\n"
            "|| 1-Go back                                          ||\n"
            "========================================================\n";

    do {
        cout << menuOptions;
        cout << "Choose an option: ";
        cin >> input;
        while (input != "0" && input != "1") {
            cout << "INVALID INPUT" << '\n';
            cout << "Choose an option: ";
            cin >> input;
        }
        switch(stoi(input))
        {
            case 0:
                cout << "===========================================\n";
                cout << dataset.getMostStudentsUC() << " has "
                     << dataset.consultClassorUcOccupation(dataset.getMostStudentsUC(),"uc") << " students"<<"\n";
                cout << "===========================================\n";
                cout << '\n';
                break;
            case 1: break;
            default:
                cout << "Invalid option\n";
        }
    } while (input != "1");
}

string AllMenus::sortOption() {
    string decision;
    string sortOptions =
            "=================================\n"
            "|| 0-Sort by ASCENDING order   ||\n"
            "|| 1-Sort by DESCENDING order  ||\n"
            "=================================\n";
    cout << sortOptions;
    cout << "Choose an option: ";
    cin >> decision;
    while(decision != "0" && decision != "1"){
        cout << "INVALID SORT OPTION" << '\n';
        cout << "Choose an option: ";
        cin >> decision;
    }
    return decision == "0" ? "ascending" : "descending";
}

void AllMenus::menu_occupations(){
    string whichOccupation;
    string SpecificOrFullConsult;
    string menuOptions =
        "==================================\n"
        "|| 0-Consult classes occupation ||\n"
        "|| 1-Consult years occupation   ||\n"
        "|| 2-Consult UCs occupation     ||\n"
        "|| 3-Go back                    ||\n"
        "==================================\n";
    string options =
            "=============================\n"
            "|| 0-Consult full list     ||\n"
            "|| 1-Consult specific one  ||\n"
            "=============================\n";

    string code, year, id;
    vector<string> sortOptions, ToBeOrdered;
    do{
        cout << menuOptions;
        cout << "Choose an option: ";
        cin >> whichOccupation;
        while(whichOccupation != "0" && whichOccupation !="1" && whichOccupation != "2" && whichOccupation != "3"){
            cout << "INVALID INPUT" << '\n';
            cout << "Choose an option: ";
            cin >> whichOccupation;
        }
        if(whichOccupation == "3") break;
        cout << options;
        cout << "Choose an option; ";
        cin >> SpecificOrFullConsult;
        while(SpecificOrFullConsult != "0" && SpecificOrFullConsult !="1"){
            cout << "INVALID INPUT" << '\n';
            cout << "Choose an option: ";
            cin >> SpecificOrFullConsult;
        }
        switch (stoi(whichOccupation)) {
            case 0:
                if(SpecificOrFullConsult == "0") {
                    vector<string> classesToBeOrdered = dataset.getClasses();
                    dataset.sortClassesByOccupation(classesToBeOrdered,sortOption());
                    for(string c: classesToBeOrdered) cout << c << ": " << dataset.consultClassorUcOccupation(c, "class") << '\n';
                } else if (SpecificOrFullConsult == "1") {
                    string classCode;
                    cout << "Class: ";
                    cin >> classCode;
                    cout << code << ':' << dataset.consultClassorUcOccupation(code, "class") << '\n';
                }
                break;
            case 1:
                if(SpecificOrFullConsult == "0"){
                    cout << "2020: " << dataset.consultYearOccupation("2020") << '\n';
                    cout << "2019: " << dataset.consultYearOccupation("2019") << '\n';
                } else if(SpecificOrFullConsult == "1"){
                    string yearNum;
                    cout << "Year: ";
                    cin >> yearNum;
                    cout << year << ": " << dataset.consultYearOccupation(year) << '\n';
                }
                break;
            case 2:
                if(SpecificOrFullConsult == "0") {
                    vector<string> ucsToBeOrdered = dataset.getUcs();
                    dataset.sortUcsByOccupation(ucsToBeOrdered,sortOption());
                    for(string c: ucsToBeOrdered) cout << c << ": " << dataset.consultClassorUcOccupation(c, "uc") << '\n';
                } else if (SpecificOrFullConsult == "1") {
                    string ucCode;
                    cout << "Uc: ";
                    cin >> ucCode;
                    cout << code << ':' << dataset.consultClassorUcOccupation(code, "uc") << '\n';
                }
                break;
        }
    } while(whichOccupation != "3");
}

void AllMenus::menu_requests(){
    string input;
    string menuOptions =
            "==============================\n"
            "|| 0-Add class request      ||\n"
            "|| 1-Add Uc request         ||\n"
            "|| 2-Remove class request   ||\n"
            "|| 3-Remove Uc request      ||\n"
            "|| 4-Change class request   ||\n"
            "|| 5-Change Uc request      ||\n"
            "|| 6-Go back                ||\n"
            "==============================\n";

    do {
        cout << menuOptions;
        cout << "Choose an option: ";
        cin >> input;
        while (input != "0" && input != "1" && input != "2" && input != "3" && input != "4" && input != "5" &&
               input != "6") {
            cout << "INVALID INPUT" << '\n';
            cout << "Choose an option: ";
            cin >> input;
        }
        switch(stoi(input))
        {
            case 0:
                addClassFunction(dataset);
                break;
            case 1:
                addUcFunction(dataset);
                break;
            case 2:
                removeClassFunction(dataset);
                break;
            case 3:
                removeUcFunction(dataset);
                break;
            case 4:
                switchClassFunction(dataset);
                break;
            case 5:
                switchUcFunction(dataset);
                break;
            case 6: break;
            default:
                cout << "Invalid option\n";
        }
    }while(input != "6");
}

void AllMenus::addClassFunction(DataSet &dataset) {
    string classToAdd;
    cout << "Class to Add: ";
    cin >> classToAdd;
    string studentCode;
    cout << "Student code: ";
    cin >> studentCode;

    Student student = dataset.getStudentByNumber(studentCode);
    Request addRequest = Request(CollegeClass(classToAdd, "*", {}, Schedule()), student, CLASS, REMOVE, dataset);
    if(!addRequest.addClass(dataset,classToAdd)) cout << "add class failed" << '\n';
}

void AllMenus::removeClassFunction(DataSet &dataset) {
    string classToRemove;
    cout << "Class to Remove: ";
    cin >> classToRemove;
    string studentCode;
    cout << "Student code: ";
    cin >> studentCode;

    Student student = dataset.getStudentByNumber(studentCode);
    Request addRequest = Request(CollegeClass(classToRemove, "*", {}, Schedule()),student,CLASS,REMOVE,dataset);
    if(!addRequest.removeClass(dataset,classToRemove)) cout << "remove class failed" << '\n';
}

void AllMenus::switchClassFunction(DataSet &dataset) {
    string classToAdd;
    cout << "Class to Add: ";
    cin >> classToAdd;
    string classToRemove;
    cout << "Class to Remove: ";
    cin >> classToRemove;
    string studentCode;
    cout << "Student code: ";
    cin >> studentCode;

    CollegeClass collegeClassToRemove = CollegeClass(classToRemove,"*", {}, Schedule());
    CollegeClass collegeClassToAdd = CollegeClass(classToAdd,"*", {}, Schedule());
    Student student = dataset.getStudentByNumber(studentCode);
    Request request = Request(collegeClassToRemove,collegeClassToAdd, student, CLASS, SWITCH, dataset);
    if(!request.switchClass(dataset, classToRemove, classToAdd)) cout << "switch class failed" << '\n';
}

void AllMenus::addUcFunction(DataSet& dataset) {
    string ucToAdd;
    cout << "Uc to Add: "; 
    cin >> ucToAdd;
    string classToAdd;
    cout << "Class to Add: ";
    cin >> classToAdd;
    string studentCode;
    cout << "Student code: ";
    cin >> studentCode;
    CollegeClass collegeClass = CollegeClass(classToAdd, ucToAdd, {}, Schedule());
    Student student = dataset.getStudentByNumber(studentCode);
    Request request = Request(collegeClass,student,UC,ADD,dataset);
    if(!request.addUc(dataset,collegeClass)) cout << "add uc failed" << '\n';
}

void AllMenus::removeUcFunction(DataSet& dataset) {
    Parser parser;
    string ucToRemove;
    cout << "Uc to Remove: "; 
    cin >> ucToRemove;
    string classToRemove;
    cout << "Class to Remove: ";
    cin >> classToRemove;
    string studentCode;
    cout << "Student code: ";
    cin >> studentCode;
    CollegeClass collegeClass = CollegeClass(classToRemove, ucToRemove, {}, Schedule());
    Student student = dataset.getStudentByNumber(studentCode);
    Request request = Request(collegeClass,student,UC,REMOVE,dataset);
    if(!request.removeUc(dataset,collegeClass)) cout << "uc remove failed";
}

void AllMenus::switchUcFunction(DataSet& dataset) {
    string ucToRemove;
    cout << "Uc to Remove: ";
    cin >> ucToRemove;
    string classToRemove;
    cout << "Class to Remove: ";
    cin >> classToRemove;

    string ucToAdd;
    cout << "Uc to Add: ";
    cin >> ucToAdd;
    string classToAdd;
    cout << "Class to Add: ";
    cin >> classToAdd;

    string studentCode;
    cout << "Student code: ";
    cin >> studentCode;
    
    CollegeClass collegeClassToRemove = CollegeClass(classToRemove, ucToRemove, {}, Schedule());
    CollegeClass collegeClassToAdd = CollegeClass(classToAdd, ucToAdd, {}, Schedule());
    Student student = dataset.getStudentByNumber(studentCode);
    Request request = Request(collegeClassToRemove,collegeClassToAdd,student,UC,SWITCH,dataset);
    if(!request.switchUc(dataset,collegeClassToRemove,collegeClassToAdd))
        cout << "switch uc failed"; return;
}


