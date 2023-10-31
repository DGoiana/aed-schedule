#include "allMenus.h"
#include "Schedule.h"
#include "Dataset.h"
#include "Lesson.h"
#include "Student.h"
#include <vector>
#include <list>
#include <string>
#include <limits>
#include <utility>
#include <iostream>

using namespace std;

AllMenus::AllMenus() {
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

    DataSet dataSet;

    while (true) {
        cout << "Choose an option: ";
        if (cin >> input) {
            switch (input) {
                case 0:
                    cout << "studentCode: ";
                    cin >> studentCode;
                    for (Lesson l : dataSet.getScheduleByStudent(studentCode).get_scheduleLessons()) {
                        cout << l.get_LessonClass().get_classCode() << "," << l.get_LessonClass().get_ucCode() << "," << l.get_LessonStartHour() << "," << l.get_LessonDuration() << "," << l.get_LessonType() << endl;
                    }
                    break;
                case 1:
                    cout << "classCode: ";
                    cin >> classCode;
                    for (Lesson l : dataSet.getScheduleByClass(classCode).get_scheduleLessons()) {
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

    string classCode, ucCode, id;
    string year;
    int n;
    int sort;

    DataSet dataSet;
    
    while (true) {
        cout << "Choose an option: ";
        if (cin >> input) {
            switch (input)
            {
                case 0:
                    cout << "classCode: ";
                    cin >> classCode;
                    id = "class";

                    for(Student s : dataSet.getStudentsByClassOrUc(classCode,id)){
                        cout << s.get_studentCode() << "," << s.get_studentName() << endl;
                    }

                    /* cout << "0-ascending\n1-descending";
                    cout << "sort: ";
                    cin >> sort;
                    if(sort == 0){

                    }
                    else if(sort == 1){

                    } */
                    break;
                case 1:
                    cout << "ucCode: ";
                    cin >> ucCode;
                    id = "uc";

                    for(Student s : dataSet.getStudentsByClassOrUc(ucCode,id)){
                        cout << s.get_studentCode() << "," << s.get_studentName() << endl;
                    }

                    /* cout << "0-ascending\n1-descending";
                    cout << "sort: ";
                    cin >> sort;
                    if(sort == 0){

                    }
                    else if(sort == 1){

                    } */
                    break;
                case 2:
                    cout << "year: ";
                    cin >> year;

                    for(Student s : dataSet.getStudentsByYear(year)){
                        cout << s.get_studentCode() << "," << s.get_studentName() << endl;
                    }

                    /* cout << "0-ascending\n1-descending";
                    cout << "sort: ";
                    cin >> sort;
                    if(sort == 0){

                    }
                    else if(sort == 1){

                    } */
                    break;
                case 3:
                    cout << "n: ";
                    cin >> n;

                    cout << dataSet.numStudentsRegisteredInUcs(n) << endl;
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

    DataSet dataSet;

    while (true) {
        cout << "Choose an option: ";
        if (cin >> input) {
            switch(input)
            {
                case 0:
                    cout << dataSet.getMostStudentsUC().first << " -> " << dataSet.getMostStudentsUC().second << endl;
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
        "0-Consult class occupation",
        "1-Consult year occupation",
        "2-Consult UC occupation",
        "3-Go back"
    };

    int width = 33;
    int height = 7;
    draw_rectangle(width, height, menuOptions);

    string classCode, ucCode, year, id;
    
    DataSet dataSet;

    while (true) {
        cout << "Choose an option: ";
        if (cin >> input) {
            switch(input)
            {
                case 0:
                    cout << "classCode: ";
                    cin >> classCode;
                    id = "class";

                    cout << dataSet.consultClassorUcOccupation(classCode,id) << endl;
                    break;
                case 1:
                    cout << "year: ";
                    cin >> year;

                    cout << dataSet.consultYearOccupation(year) << endl;
                    break;
                case 2:
                    cout << "ucCode: ";
                    cin >> ucCode;
                    id = "uc";

                    cout << dataSet.consultClassorUcOccupation(ucCode,id) << endl;
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
            break;
        } else {
            cout << "Invalid input" << endl;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); 
        }
    }

    switch(input)
    {
        case 0:
            //TODO
            break;
        case 1:
            //TODO
            break;
        case 2:
            //TODO
            break;
        case 3:
            //TODO
            break;
        case 4:
            //TODO
            break;
        case 5:
            //TODO
            break;
        case 6:
            menu_principal();
            break;
        default:
            cout << "Invalid option\n";
            menu_requests();

    }
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