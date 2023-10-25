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
        "Consulting",
        "Requests",
        "Exit"
    };
    Menu principal = Menu("Choose an option: ", menuOptions);
    principal.printMenu();
    switch (stoi(principal.get_input()))
    {
    case 0:
        menu_consulting();
        break;
    case 1:
        menu_requests();
        break;
    case 2:
        exit(0);
        break;
    default:
        cout << "Invalid option\n";
        menu_principal();
    }
}

void AllMenus::menu_consulting(){
    string input;
    vector<string> menuOptions = {
        "Schedules",
        "Students",
        "Classes",
        "Years",
        "UC's",
        "Back"
    };
    Menu schedule = Menu("Choose an option: ", menuOptions);
    schedule.printMenu();
    switch (stoi(schedule.get_input()))
    {
    case 0:
        menu_schedule_consulting();
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
        menu_principal();
        break;
    default:
        cout << "Invalid option\n";
        menu_consulting();
    }
}

void AllMenus::menu_requests(){
    string input;
    vector<string> menuOptions = {
        "Registration",
        "Switch",
        "Removal",
        "Back"
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
        //TODO
        break;
    case 3:
        menu_principal();
        break;
    default:
        cout << "Invalid option\n";
        menu_requests();
    }
}

void AllMenus::menu_schedule_consulting(){
    string input;
    vector<string> menuOptions;
}