#ifndef AED_SCHEDULE_MENU_H
#define AED_SCHEDULE_MENU_H

#include <vector>
#include <string>

using namespace std;

class Menu{
    private:
        string inputPrompt;
        vector<string> menuOptions;
        string chosenInput;
    public:
        Menu(string inputPrompt, vector<string> menuOptions);
        void printMenu();
        string get_input() const;
};

#endif