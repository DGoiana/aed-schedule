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
        "Consult schedule",
        "Consult UC",
        "New regist"
    };
    Menu menu_principal = Menu("Escolhe: ", menuOptions);
    menu_principal.printMenu();
    cout << menu_principal.getInput();
}