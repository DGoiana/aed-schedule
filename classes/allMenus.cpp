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
#include <limits>
#include <utility>
#include <iostream>

using namespace std;

vector<string> occupationsOptions = {
    "0-Consult full list",
    "1-Consult specific one",
};

vector<string> AllMenus::showSortOptions(string id){
    int result;
    vector<string> options;
    vector<string> sortOptions = {
        "0-Sort by name",
        "1-Sort by year",
    };
    vector<string> sortOrder = {
        "0-Sort ascending",
        "1-Sort descending",
    };
    if(id == "both" || id == "first") {
        draw_rectangle(20, 5, sortOptions);
        cout << "Choose a sort option: ";
        cin >> result;

        if(result == 0) options.push_back("name");
        else options.push_back("year");
    }
    if(id == "both" || id == "second") {
        draw_rectangle(20, 5, sortOrder);
        cout << "Choose a sort order: ";
        cin >> result;

        if(result == 0) options.push_back("ascending");
        else options.push_back("descending");
    } 
    return options;
}

AllMenus::AllMenus(DataSet &dataset) {
    this->dataset = dataset;
    menu_principal();
}

void AllMenus::menu_principal(){
    int input;
    vector<string> menuOptions = {
        "0-Schedules",
        "1-UC's",
        "2-Students",
        "3-Occupations",
        "4-Requests",
        "5-Exit"
    }; 

    int width = 20;
    int height = 9;
    draw_rectangle(width, height, menuOptions);

    while (true) {
        cout << "Choose an option: ";
        if (cin >> input) {
            break;
        } else {
            cout << "Invalid input" << endl;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); 
        }
    }

    switch (input)
    {
    case 0:
        menu_schedule();
        break;
    case 1:
        menu_uc();
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
    default:
        cout << "Invalid option\n";
        menu_principal();
    }
}

void AllMenus::menu_schedule() {
    int input;
    vector<string> menuOptions = {
        "0-Consult schedule of a student",
        "1-Consult schedule of a class",
        "2-Go back"
    };

    int width = 38;
    int height = 6;
    draw_rectangle(width, height, menuOptions);

    string studentCode; 
    string classCode;

    while (true) {
        cout << "Choose an option: ";
        if (cin >> input) {
            switch (input) {
                case 0:
                    cout << "studentCode: ";
                    cin >> studentCode;
                    for (Lesson l : dataset.getScheduleByStudent(studentCode).get_scheduleLessons()) {
                        cout << l.get_LessonClass().get_classCode() << "," << l.get_LessonClass().get_ucCode() << "," << l.get_LessonStartHour() << "," << l.get_LessonDuration() << "," << l.get_LessonType() << endl;
                    }
                    break;
                case 1:
                    cout << "classCode: ";
                    cin >> classCode;
                    for (Lesson l : dataset.getScheduleByClass(classCode).get_scheduleLessons()) {
                        cout << l.get_LessonClass().get_classCode() << "," << l.get_LessonClass().get_ucCode() << "," << l.get_LessonStartHour() << "," << l.get_LessonDuration() << "," << l.get_LessonType() << endl;
                    }
                    break;
                case 2:
                    menu_principal();
                    break;
                default:
                    cout << "Invalid option\n";
                    break;
            }
            break;
        } else {
            cout << "Invalid input" << endl;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    menu_schedule();
}


void AllMenus::menu_students(){
    int input;
    vector<string> menuOptions = {
        "0-Consult students within a given class",
        "1-Consult students within a given Uc",
        "2-Consult students within a given year",
        "3-Consult number of students registered in at least n UCs",
        "4-Go back"
    };

    int width = 64;
    int height = 8;
    draw_rectangle(width, height, menuOptions);

    string classCode, ucCode, id, year;
    int n, sort;
    vector<string> sortOptions;
    vector<Student> studentsToBeOrdered;
    
    while (true) {
        cout << "Choose an option: ";
        if (cin >> input) {
            switch (input)
            {
                case 0:
                    cout << "classCode: ";
                    cin >> classCode;

                    sortOptions = showSortOptions("both");
                    studentsToBeOrdered = dataset.getStudentsByClassOrUc(classCode, "class");
                    dataset.sortStudentsByNameOrYear(studentsToBeOrdered, sortOptions[1], sortOptions[0]);
                    
                    for(Student s : studentsToBeOrdered){
                        cout << s.get_studentCode() << "," << s.get_studentName() << endl;
                    }
                    break;
                case 1:
                    cout << "ucCode: ";
                    cin >> ucCode;

                    sortOptions = showSortOptions("both");
                    studentsToBeOrdered = dataset.getStudentsByClassOrUc(ucCode, "uc");
                    dataset.sortStudentsByNameOrYear(studentsToBeOrdered, sortOptions[1], sortOptions[0]);
                    
                    for(Student s : studentsToBeOrdered){
                        cout << s.get_studentCode() << "," << s.get_studentName() << endl;
                    }
                    break;
                case 2:
                    cout << "year: ";
                    cin >> year;

                    sortOptions = showSortOptions("");
                    studentsToBeOrdered = dataset.getStudentsByYear(year);
                    dataset.sortStudentsByNameOrYear(studentsToBeOrdered, sortOptions[1], sortOptions[0]);
                    
                    for(Student s : studentsToBeOrdered){
                        cout << s.get_studentCode() << "," << s.get_studentName() << endl;
                    }
                    break;
                case 3:
                    cout << "n: ";
                    cin >> n;

                    cout << dataset.numStudentsRegisteredInNUcs(n) << endl;
                    break;
                case 4:
                    menu_principal();
                    break;
                default:
                    cout << "Invalid option\n";
                    menu_students();
            }
            break;
        } else {
            cout << "Invalid input" << endl;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    menu_students();
}

void AllMenus::menu_uc(){
    int input;
    vector<string> menuOptions = {
        "0-Consult UCs with the greatest number of students",
        "1-Go back"
    };

    int width = 57;
    int height = 5;
    draw_rectangle(width, height, menuOptions);

    while (true) {
        cout << "Choose an option: ";
        if (cin >> input) {
            switch(input)
            {
                case 0:
                    cout << dataset.getMostStudentsUC();
                    break;
                case 1:
                    menu_principal();
                    break;
                default:
                    cout << "Invalid option\n";
                    menu_uc();
            }
            break;
        } else {
            cout << "Invalid input" << endl;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    menu_uc();
}

void AllMenus::menu_occupations(){
    int input;
    vector<string> menuOptions = {
        "0-Consult classes occupation",
        "1-Consult years occupation",
        "2-Consult UCs occupation",
        "3-Go back"
    };

    int width = 33;
    int height = 7;
    draw_rectangle(width, height, menuOptions);

    string code, year, id;
    vector<string> sortOptions, ToBeOrdered;

    while (true) {
        cout << "Choose an option: ";
        if (cin >> input) {
            switch(input)
            {
                case 0:
                    draw_rectangle(20, 5, occupationsOptions);
                    cout << "Choose an option; ";
                    cin >> input;
                    switch (input)
                    {
                    case 0:
                        sortOptions = showSortOptions("second");
                        ToBeOrdered = dataset.getClasses();
                        dataset.sortClassesByOccupation(ToBeOrdered, sortOptions[1]);
                        for(string c: ToBeOrdered){
                            cout << c << ": " << dataset.consultClassorUcOccupation(c, "class") << '\n';
                        }
                        break;
                    case 1:
                        cout << "Class: ";
                        cin >> code;
                        cout << code << ':' << dataset.consultClassorUcOccupation(code, "class") << '\n';
                        break;
                    default:
                        break;
                    }
                    break;
                case 1:
                    draw_rectangle(20, 5, occupationsOptions);
                    cout << "Choose an option; ";
                    cin >> input;
                    switch (input)
                    {
                    case 0:
                        cout << "2020: " << dataset.consultYearOccupation("2020") << '\n';
                        cout << "2019: " << dataset.consultYearOccupation("2019") << '\n';
                        break;
                    case 1:
                        cout << "Year: ";
                        cin >> year;
                        cout << year << ": " << dataset.consultYearOccupation(year) << '\n';
                        break;
                    default:
                        break;
                    }
                    break;
                case 2:
                    draw_rectangle(20, 5, occupationsOptions);
                    cout << "Choose an option; ";
                    cin >> input;
                    switch (input)
                    {
                    case 0:
                        sortOptions = showSortOptions("second");
                        ToBeOrdered = dataset.getUcs();
                        dataset.sortUcsByOccupation(ToBeOrdered, sortOptions[1]);
                        for(string c: ToBeOrdered){
                            cout << c << ": " << dataset.consultClassorUcOccupation(c, "uc") << '\n';
                        }
                        break;
                    case 1:
                        cout << "Uc: ";
                        cin >> code;
                        cout << code << ':' << dataset.consultClassorUcOccupation(code, "uc") << '\n';
                        break;
                    default:
                        break;
                    }
                    break;
                case 3:
                    menu_principal();
                    break;
                default:
                    cout << "Invalid option\n";
                    menu_occupations();

            }
            break;
        } else {
            cout << "Invalid input" << endl;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    menu_occupations();
}

void AllMenus::menu_requests(){
    int input;
    vector<string> menuOptions = {
        "0-Add class request",
        "1-Add Uc request",
        "2-Remove class request",
        "3-Remove Uc request",
        "4-Change class request",
        "5-Change Uc request",
        "6-Go back"
    };

    int width = 29;
    int height = 10;
    draw_rectangle(width, height, menuOptions);

    while (true) {
        cout << "Choose an option: ";
        if (cin >> input) {
            switch(input)
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
                case 6:
                    menu_principal();
                    break;
                default:
                    cout << "Invalid option\n";
                    menu_requests();
            }
            break;
        } else {
            cout << "Invalid input" << endl;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    menu_requests();
}


// Function to design a rectangle with text inside
void AllMenus::draw_rectangle(int width, int height, const std::vector<std::string>& text) {
    string reset = "\033[0m";  // Escape code to reset formatting
    string fg_blue = "\033[34m";  // Escape code for blue text
    string border_char = "█";     // Character for the border

    // Calculate the maximum width of the text
    int max_text_width = 0;
    for (const string& line : text) {
        if (line.length() > max_text_width) {
            max_text_width = line.length();
        }
    }

    // Loop to draw the rectangle and print the text
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                cout << fg_blue << border_char << reset;  // Rectangle border
            } else {
                // Center the text vertically in the rectangle
                int text_x = (width - max_text_width) / 2;
                int text_y = (height - text.size()) / 2;

                if (text_y <= i && text_y + text.size() > i && j - text_x >= 1 && j - text_x <= text[i - text_y].length()) {
                    cout << text[i - text_y][j - text_x - 1];
                } else {
                    cout << " ";  // Blank space inside the rectangle
                }
            }
        }
        cout << endl;
    }
}

void AllMenus::addClassFunction(DataSet &dataset) {
    string classToAdd;
    cout << "Class to Add: ";
    cin >> classToAdd;
    string studentCode;
    cout << "Student code: ";
    cin >> studentCode;

    Student student = dataset.getStudentByNumber(studentCode);
    Request addRequest = Request(CollegeClass(classToAdd,"*"),student,CLASS,REMOVE,dataset);
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
    Request addRequest = Request(CollegeClass(classToRemove,"*"),student,CLASS,ADD,dataset);
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

    CollegeClass collegeClassToRemove = CollegeClass(classToRemove,"*");
    CollegeClass collegeClassToAdd = CollegeClass(classToAdd,"*");
    Student student = dataset.getStudentByNumber(studentCode);
    Request request = Request(collegeClassToRemove,collegeClassToAdd,student,CLASS,SWITCH,dataset);
    list<Lesson> oldLessons = request.getStudent().get_studentSchedule().get_scheduleLessons();
    if(request.removeClass(dataset,classToRemove)){
        request.setStudent(dataset.getStudentByNumber(studentCode));
        if(!request.addClass(dataset,classToAdd)){
            dataset.setStudentSchedule(oldLessons,student);
            cout << "switch class failed" << '\n';
        }
    }
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
    CollegeClass collegeClass = CollegeClass(classToAdd,ucToAdd);
    Student student = dataset.getStudentByNumber(studentCode);
    Request request = Request(collegeClass,student,UC,ADD,dataset);
    if(!request.addUc(dataset,collegeClass)) cout << "add uc failed";
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
    CollegeClass collegeClass = CollegeClass(classToRemove,ucToRemove);
    Student student = dataset.getStudentByNumber(studentCode);
    Request request = Request(collegeClass,student,UC,REMOVE,dataset);
    if(request.removeUc(dataset,collegeClass)) cout << "uc remove failed";
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
    
    CollegeClass collegeClassToRemove = CollegeClass(classToRemove,ucToRemove);
    CollegeClass collegeClassToAdd = CollegeClass(classToAdd,ucToAdd);
    Student student = dataset.getStudentByNumber(studentCode);
    Request request = Request(collegeClassToRemove,collegeClassToAdd,student,UC,SWITCH,dataset);
    if(request.switchUc(dataset,collegeClassToRemove,collegeClassToAdd))
        cout << "switch uc failed"; return;
}