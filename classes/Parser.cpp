#include "Parser.h"
#include "Student.h"
#include <fstream>
#include <map>
#include <algorithm>

using namespace std;

list<vector<string>> classesPerUc = Parser::readFile("../schedule/classes_per_uc.csv");
list<vector<string>> classes = Parser::readFile("../schedule/classes.csv");
list<vector<string>> studentsClasses = Parser::readFile("../schedule/students_classes.csv");
map<CollegeClass, list<Lesson>> mappedLessons = Parser::mapLessons();
map<CollegeClass, set<Student>> mappedStudentsFromClass =  Parser::studentsFromCollegeClass();

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
/**
 * Reads a given file.
 * Time Complexity: O(n)
 * @param path
 * @return a list of vector of all possible objects
 */
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

map<CollegeClass, list<Lesson>> Parser::mapLessons(){
    list<Lesson> allClasses = parseClassesFile();
    map<CollegeClass, list<Lesson>> mappedLessons;
    for(vector<string> classAndUc : classesPerUc){
        string classCodeTrimmed = classAndUc[1].substr(0, classAndUc[1].length() - 1);
        mappedLessons[CollegeClass(classCodeTrimmed, classAndUc[0], {}, Schedule())] = findLesson(allClasses, Lesson({classCodeTrimmed, classAndUc[0]}, "*", 0, 0, "*"));
    }
    return mappedLessons;
}
/**
 * Creates a list of all the available lessons.
 * Time Complexity: O(n)
 * @return a list of lessons
 */
list<Lesson> Parser::parseClassesFile() {
    list<Lesson> lessons;
    for (vector<string> lesson: classes) {
        string lessonWeekday = lesson[2];
        double lessonStartHour = stod(lesson[3]);
        double lessonDuration = stod(lesson[4]);
        string lessonType = lesson[5];
        lessons.push_back(Lesson({lesson[0], lesson[1]},lessonWeekday,lessonStartHour,lessonDuration,lessonType));
    }
    return lessons;
}

map<string, list<string>> Parser::getUcsByClasses() // [LEIC01: {L.EIC01, L.EIC02}, ...]
{
    map<string,list<string>> result;
    for(vector<string> classAndUc : classesPerUc) {
        string classCodeTrimmed = classAndUc[1].substr(0, classAndUc[1].length() - 1);
        result[classCodeTrimmed].push_back(classAndUc[0]);
    }
    return result;
}

map<CollegeClass, set<Student>> Parser::studentsFromCollegeClass(){
    map<CollegeClass, set<Student>> mappedCollegeClass;
    for(vector<string> student: studentsClasses){
        string classCodeTrimmed = student[3].substr(0, student[3].length() - 1);
        mappedCollegeClass[CollegeClass(classCodeTrimmed, student[2], {}, Schedule())].insert(Student(student[0], student[1], {}));
    }
    return mappedCollegeClass;
}

/**
 * Creates a list of all available CollegeClass objects.
 * Time Complexity: O(n)
 * @return a list of CollegeClass
 */
list<CollegeClass> Parser::parseCollegeClasses(){
    list<CollegeClass> classes;
    for(vector<string> cc : classesPerUc){
        string classCodeTrimmed = cc[1].substr(0, cc[1].length() - 1);
        CollegeClass toCompare = CollegeClass(classCodeTrimmed, cc[0], {}, Schedule());
        classes.push_back(CollegeClass(classCodeTrimmed, cc[0], mappedStudentsFromClass[toCompare], Schedule(mappedLessons[toCompare])));
    }
    return classes;
}
/**
 * Creates a list of all current Student.
 * Time Complexity: O(n)
 * @return a list of Student
 */
vector<Student> Parser::parseStudents(){
    vector<Student> students;
    map<pair<string, string>, set<CollegeClass>> mappedStudents;
    for(vector<string> student: studentsClasses){
        string classCodeTrimmed = student[3].substr(0, student[3].length() - 1);
        CollegeClass toAdd = CollegeClass(classCodeTrimmed, student[2], {}, Schedule());
        mappedStudents[{student[0], student[1]}].insert(CollegeClass(classCodeTrimmed, student[2], mappedStudentsFromClass[toAdd], Schedule(mappedLessons[toAdd])));
    }

    for(auto p : mappedStudents){
        students.push_back(Student(p.first.first, p.first.second, p.second));
    }
    return students;
}

void Parser::printLessons(list<Lesson> lessons) {
    if(lessons.size() == 0) return;
    for(Lesson lesson : lessons) {
        lesson.printLesson();
    }
}

list<Lesson> Parser::findLesson(list<Lesson> globalLessons, Lesson lessonToFind) {
    list<Lesson> lessons;
    for(Lesson lesson : globalLessons) {
        if(lesson.get_ucCode() == lessonToFind.get_ucCode() && lesson.get_classCode() == lessonToFind.get_classCode())
            lessons.push_back(lesson);
    }
    return lessons;
}
