#include <stdlib.h>
#include "classes/allMenus.h"
#include "classes/Parser.h"
#include <iostream>

using namespace std;

int main(){
    list<vector<string>> classesPerUc = Parser::readFile("../schedule/classes_per_uc.csv");
    list<vector<string>> classes = Parser::readFile("../schedule/classes.csv");
    list<vector<string>> studentsClasses = Parser::readFile("../schedule/students_classes.csv");

    DataSet dataset = DataSet(classesPerUc, Parser::parseClassesFile(classes), studentsClasses);

    AllMenus menu = AllMenus(dataset, classesPerUc);
    return 0;
}
