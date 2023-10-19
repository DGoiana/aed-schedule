#include "Menu.h"
#include <iostream>

using namespace std;

Menu::Menu(string input, vector<string> menuOptions){
    this->inputPrompt = input;
    this->menuOptions = menuOptions;
}

void Menu::printMenu(){
    for(int i = 0; i < menuOptions.size(); i++){
        cout << menuOptions.at(i) << '\n';
    }
    cout << inputPrompt;
    cin >> chosenInput;
}

string Menu::getInput(){
    return this->chosenInput;
}