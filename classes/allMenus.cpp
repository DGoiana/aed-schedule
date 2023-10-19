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
        "Students"
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
    //TODO
}

void AllMenus::menu_uc(){
    //TODO
}