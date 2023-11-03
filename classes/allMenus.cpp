#include "allMenus.h"
#include "Schedule.h"
#include "Dataset.h"
#include "Lesson.h"
#include "Student.h"
#include "Request.h"
#include "CollegeClass.h"
#include <vector>
#include <string>
#include <limits>
#include <iostream>
#include <cmath>
#include <map>

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
    this->globalRequests = stack<Request>();
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
            cout << "Invalid input" << "\n";
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

    vector<string> weekDays = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

    while (true) {
        cout << "Choose an option: ";
        if (cin >> input) {
            switch (input) {
                case 0:
                    cout << "studentCode: ";
                    cin >> studentCode;
                    for (string s : weekDays) {
                        cout << s << ":\n";
                        for (Lesson l : dataset.getScheduleByStudent(studentCode).get_scheduleLessons()) {
                            if (l.get_LessonWeekday() == s) {
                                double parte_inteira_begin = floor(l.get_LessonStartHour());
                                double parte_decimal_begin = modf(l.get_LessonStartHour(),&parte_inteira_begin);
                                double end_hour = l.get_LessonStartHour() + l.get_LessonDuration();
                                double parte_inteira_end = floor(end_hour);
                                double parte_decimal_end = modf(end_hour,&parte_inteira_end);
                                double parte_inteira_duration = floor(l.get_LessonDuration());
                                double parte_decimal_duration = modf(l.get_LessonDuration(),&parte_inteira_duration);
                                cout << l.get_classCode() << " " << l.get_ucCode() << " begin:" << parte_inteira_begin << "h" <<  parte_decimal_begin * 60 << " end:" << parte_inteira_end << "h" <<  parte_decimal_end * 60 << " duration:" << parte_inteira_duration << "h" << parte_decimal_duration * 60 << " " << l.get_LessonType() << "\n";
                            }
                        }
                    }
                    break;
                case 1:
                    cout << "classCode: ";
                    cin >> classCode;
                    for (string s : weekDays) {
                        cout << s << ":\n";
                        for (Lesson l : dataset.getScheduleByClass(classCode).get_scheduleLessons()) {
                            if (l.get_LessonWeekday() == s) {
                                double parte_inteira_begin = floor(l.get_LessonStartHour());
                                double parte_decimal_begin = modf(l.get_LessonStartHour(),&parte_inteira_begin);
                                double end_hour = l.get_LessonStartHour() + l.get_LessonDuration();
                                double parte_inteira_end = floor(end_hour);
                                double parte_decimal_end = modf(end_hour,&parte_inteira_end);
                                double parte_inteira_duration = floor(l.get_LessonDuration());
                                double parte_decimal_duration = modf(l.get_LessonDuration(),&parte_inteira_duration);
                                cout << l.get_classCode() << " " << l.get_ucCode() << " begin:" << parte_inteira_begin << "h" <<  parte_decimal_begin * 60 << " end:" << parte_inteira_end << "h" <<  parte_decimal_end * 60 << " duration:" << parte_inteira_duration << "h" << parte_decimal_duration * 60 << " " << l.get_LessonType() << "\n";
                            }
                        }
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
            cout << "Invalid input" << "\n";
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
                        cout << s.get_studentCode() << "," << s.get_studentName() << "\n";
                    }
                    break;
                case 1:
                    cout << "ucCode: ";
                    cin >> ucCode;

                    sortOptions = showSortOptions("both");
                    studentsToBeOrdered = dataset.getStudentsByClassOrUc(ucCode, "uc");
                    dataset.sortStudentsByNameOrYear(studentsToBeOrdered, sortOptions[1], sortOptions[0]);
                    
                    for(Student s : studentsToBeOrdered){
                        cout << s.get_studentCode() << "," << s.get_studentName() << "\n";
                    }
                    break;
                case 2:
                    cout << "Year: ";
                    cin >> year;

                    sortOptions = showSortOptions("both");
                    studentsToBeOrdered = dataset.getStudentsByYear(year);
                    dataset.sortStudentsByNameOrYear(studentsToBeOrdered, sortOptions[1], sortOptions[0]);
                    
                    for(Student s : studentsToBeOrdered){
                        cout << s.get_studentCode() << "," << s.get_studentName() << "\n";
                    }
                    break;
                case 3:
                    cout << "n: ";
                    cin >> n;

                    cout << dataset.numStudentsRegisteredInNUcs(n) << "\n";
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
            cout << "Invalid input" << "\n";
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
                    cout << dataset.getMostStudentsUC() << "\n";
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
            cout << "Invalid input" << "\n";
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
                        dataset.sortClassesByOccupation(ToBeOrdered, sortOptions[0]);
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
                        dataset.sortUcsByOccupation(ToBeOrdered, sortOptions[0]);
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
            cout << "Invalid input" << "\n";
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    menu_occupations();
}

void AllMenus::seeGlobalRequestsTop() {
    map<OPTION,string> optionToString = {{ADD,"add"},{REMOVE,"remove"},{SWITCH,"switch"}};
    map<TYPE,string> typeToString = {{CLASS,"class"},{UC,"uc"}};
    if(this->globalRequests.empty()) cout << "globalRequests empty." << '\n';
    else{
        Request request = globalRequests.top();
        cout << request.getStudent().get_studentCode()
        << " " << optionToString[request.get_option()]
        << " " << typeToString[request.get_type()] << '\n';
    }
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
        "6-See Last Request",
        "7-Undo Last Request",
        "8-Go back"
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
                    seeGlobalRequestsTop();
                    break;
                case 7:
                    undoRequest(dataset);
                    break;
                case 8:
                    menu_principal();
                    break;
                default:
                    cout << "Invalid option\n";
                    menu_requests();
            }
            break;
        } else {
            cout << "Invalid input" << "\n";
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
        cout << "\n";
    }
}

void AllMenus::undoRequest(DataSet &dataset){
    if(this->globalRequests.empty()){
        cout << "UNABLE TO UNDO LAST REQUEST (STACK EMPTY)\n";
        return;
    }
    Request lastRequest = this->globalRequests.top();
    switch (lastRequest.get_option()) {
        case ADD:
            if(lastRequest.get_type() == CLASS) lastRequest.removeClass(dataset,lastRequest.get_collegeClass().get_classCode());
            if(lastRequest.get_type() == UC) lastRequest.removeUc(dataset,lastRequest.get_collegeClass());
            break;
        case REMOVE:
            if(lastRequest.get_type() == CLASS) lastRequest.addClass(dataset,lastRequest.get_collegeClass().get_classCode());
            if(lastRequest.get_type() == UC) lastRequest.addUc(dataset,lastRequest.get_collegeClass());
            break;
        case SWITCH:
            if(lastRequest.get_type() == CLASS) lastRequest.switchClass(dataset,lastRequest.get_newCollegeClass().get_classCode(),lastRequest.get_collegeClass().get_classCode());
            if(lastRequest.get_type() == UC) lastRequest.switchUc(dataset,lastRequest.get_newCollegeClass(),lastRequest.get_collegeClass());
            break;
    }
    cout << "last request: "; seeGlobalRequestsTop();
    this->globalRequests.pop();
    cout << "new last request: "; seeGlobalRequestsTop();
}

void AllMenus::addClassFunction(DataSet &dataset) {
    string classToAdd;
    cout << "Class to Add: ";
    cin >> classToAdd;
    string studentCode;
    cout << "Student code: ";
    cin >> studentCode;

    Student student = dataset.getStudentByNumber(studentCode);
    Request addClassRequest = Request(CollegeClass(classToAdd, "*", {}, Schedule()), student, CLASS, REMOVE, dataset);
    if(addClassRequest.addClass(dataset,classToAdd)){
        this->globalRequests.push(addClassRequest);
    }else cout << "add class failed" << '\n';
}

void AllMenus::removeClassFunction(DataSet &dataset) {
    string classToRemove;
    cout << "Class to Remove: ";
    cin >> classToRemove;
    string studentCode;
    cout << "Student code: ";
    cin >> studentCode;

    Student student = dataset.getStudentByNumber(studentCode);
    Request removeClassRequest = Request(CollegeClass(classToRemove, "*", {}, Schedule()),student,CLASS,REMOVE,dataset);
    if(removeClassRequest.removeClass(dataset,classToRemove)){
        this->globalRequests.push(removeClassRequest);
    }else cout << "remove class failed" << '\n';
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
    Request switchClassRequest = Request(collegeClassToRemove,collegeClassToAdd, student, CLASS, SWITCH, dataset);
    if(switchClassRequest.switchClass(dataset, classToRemove, classToAdd)){
        this->globalRequests.push(switchClassRequest);
    }else cout << "switch class failed" << '\n';
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
    Request addUcRequest = Request(collegeClass,student,UC,ADD,dataset);
    if(addUcRequest.addUc(dataset,collegeClass)){
        this->globalRequests.push(addUcRequest);
    }else cout << "add uc failed" << '\n';
}

void AllMenus::removeUcFunction(DataSet& dataset) {
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
    Request removeUcRequest = Request(collegeClass,student,UC,REMOVE,dataset);
    if(removeUcRequest.removeUc(dataset,collegeClass)){
        this->globalRequests.push(removeUcRequest);
    }else cout << "uc remove failed" << '\n';
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
    Request switchUcRequest = Request(collegeClassToRemove,collegeClassToAdd,student,UC,SWITCH,dataset);
    if(switchUcRequest.switchUc(dataset,collegeClassToRemove,collegeClassToAdd)){
        this->globalRequests.push(switchUcRequest);
    }else cout << "switch uc failed\n"; return;
}


