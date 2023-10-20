#include "Menu.h"
#include <iostream>

using namespace std;

Menu::Menu(string input, vector<string> menuOptions){
    this->inputPrompt = input;
    this->menuOptions = menuOptions;
}

void Menu::printMenu(){
    for(size_t i = 0; i < menuOptions.size(); i++){
        cout << i << '-' << menuOptions.at(i) << '\n';
    }
    cout << inputPrompt;
    cin >> chosenInput;
}

string Menu::get_input() const{
    return this->chosenInput;
}