#include "allMenus.h"
#include <vector>
#include <string>
#include <iostream>
#include "Menu.h"

using namespace std;

AllMenus::AllMenus() {
    menu_principal();
}

void AllMenus::menu_principal(){
    string input;
    vector<string> menuOptions = {
        "Schedules",
        "UC's",
        "Students",
        "Occupations",
        "Requests",
    };
    Menu principal = Menu("Choose an option: ", menuOptions);
    principal.printMenu();
    switch (stoi(principal.get_input()))
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
    default:
        cout << "Invalid option\n";
        menu_principal();
    }
}

void AllMenus::menu_schedule(){
    string input;
    vector<string> menuOptions = {
        "Consult schedule of a student",
        "Consult schedule of a class",
        "Go back"
    };
    Menu schedule = Menu("Choose an option: ", menuOptions);
    schedule.printMenu();
    switch (stoi(schedule.get_input()))
    {
    case 0:
        //TODO
        break;
    case 1:
        //TODO
        break;
    case 2:
        menu_principal();
        break;
    default:
        cout << "Invalid option\n";
        menu_schedule();
    }
}

void AllMenus::menu_students(){
    string input;
    vector<string> menuOptions = {
        "Consult students within a given class",
        "Consult students within a given course",
        "Consult students within a given year",
        "Consult number of students registered in at least n UCs",
        "Go back"
    };
    Menu students = Menu("Choose an option: ", menuOptions);
    students.printMenu();
    switch (stoi(students.get_input()))
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
            menu_principal();
            break;
        default:
            cout << "Invalid option\n";
            menu_students();
    }
}

void AllMenus::menu_uc(){
    string input;
    vector<string> menuOptions = {
        "Consult UCs with the greatest number of students",
        "Go back"
    };
    Menu uc = Menu("Choose an option: ", menuOptions);
    uc.printMenu();
    switch(stoi(uc.get_input()))
    {
        case 0:
            //TODO
            break;
        case 1:
            menu_principal();
            break;
        default:
            cout << "Invalid option\n";
            menu_uc();

    }
}

void AllMenus::menu_occupations(){
    string input;
    vector<string> menuOptions = {
        "Consult class occupation",
        "Consult year occupation",
        "Consult UC occupation",
        "Go back"
    };
    Menu occupation = Menu("Choose an option: ", menuOptions);
    occupation.printMenu();
    switch(stoi(occupation.get_input()))
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
            menu_principal();
            break;
        default:
            cout << "Invalid option\n";
            menu_occupations();

    }
}

void AllMenus::menu_requests(){
    string input;
    vector<string> menuOptions = {
        "Add class request",
        "Add Uc request",
        "Remove class request",
        "Remove Uc request",
        "Change class request",
        "Change Uc request",
        "Go back"
    };
    Menu requests = Menu("Choose an option: ", menuOptions);
    requests.printMenu();
    switch(stoi(requests.get_input()))
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