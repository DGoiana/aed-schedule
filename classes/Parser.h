#ifndef AED_SCHEDULE_PARSER_H
#define AED_SCHEDULE_PARSER_H

#include <utility>
#include <list>
#include <string>
#include <vector>
#include <set>
#include "Lesson.h"
#include "Student.h"
#include "CollegeClass.h"
#include <map>
#include <unordered_map>

using namespace std;

/**
 * The parser class is responsible for reading the given CSV files and creating the corresponding objects.
 */
class Parser {
    public:
        static vector<string> split(std::string line,const std::string& delimiter);
        static list<vector<string>> readFile(const std::string &path);
        static std::unordered_multimap<pair<string, string>, Lesson, pair_hash> parseClassesFile(list<vector<string>> classes);
};
#endif //AED_SCHEDULE_PARSER_H
