#ifndef AED_SCHEDULE_PARSER_H
#define AED_SCHEDULE_PARSER_H

#include <list>
#include <string>
class Parser {
public:
    std::list<std::string> split(std::string line,const std::string& delimiter);
    std::list<std::list<std::string>> readFile(const std::string& path);
};
#endif //AED_SCHEDULE_PARSER_H
