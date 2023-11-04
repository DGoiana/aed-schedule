#include "Parser.h"
#include "Student.h"
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

vector<string> Parser::split(std::string line, const string &delimiter) {
    size_t pos;
    string token;
    vector<string> result;
    while(line.find(delimiter) != string::npos) {
        pos = line.find(delimiter);
        token = line.substr(0,pos);
        result.push_back(token);
        line = line.substr(pos + delimiter.length());
    }
    result.push_back(line.substr(0));
    return result;
}

list<vector<string>> Parser::readFile(const string &path) {
    ifstream file(path);
    string line;
    list<vector<string>> result;
    while (getline(file,line)) {
        result.push_back(split(line,","));
    }
    file.close();
    result.pop_front();
    return result;
}

std::unordered_multimap<pair<string, string>, Lesson, pair_hash> Parser::parseClassesFile(list<vector<string>> classes) {
    std::unordered_multimap<pair<string, string>, Lesson, pair_hash> lessons;
    for (vector<string> lesson: classes) {
        string lessonWeekday = lesson[2];
        double lessonStartHour = stod(lesson[3]);
        double lessonDuration = stod(lesson[4]);
        string lessonType = lesson[5];
        lessons.insert({{lesson[0], lesson[1]}, Lesson({lesson[0], lesson[1]},lessonWeekday,lessonStartHour,lessonDuration,lessonType)});
    }
    return lessons;
}