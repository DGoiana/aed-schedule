#include "Parser.h"
#include <fstream>

using namespace std;

list<string> split(string line,const string& delimiter) {
    size_t pos;
    string token;
    list<string> result;
    while(line.find(delimiter) != string::npos) {
        pos = line.find(delimiter);
        token = line.substr(0,pos);
        result.push_back(token);
        line = line.substr(pos + delimiter.length());
    }
    result.push_back(line.substr(0));
    return result;
}

list<list<string>> readFile(const string& path) {
    ifstream file(path);
    string line;
    list<list<string>> result;
    while (getline(file,line)) {
        result.push_back(split(line,","));
    }
    file.close();
    return result;
}