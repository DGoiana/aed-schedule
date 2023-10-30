#include "Parser.h"
#include "Student.h"
#include <fstream>
#include <map>

using namespace std;
/**
 * @brief Splits the line read in the file to an vector of strings
 * @param line line of the file being read
 * @param delimiter delimiter to split the line
 * @return a vector of elements of the object to be created
 */
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
 * @brief Reads the file and returns a list of vectors of elements to be created
 * @param path path to the file to be read
 * @return a list of vector of elemts of the object to be created
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

/**
 * @brief Creates the Lesson objects from the classes.csv file
 * @return a list of all the lessons
 */
list<Lesson> Parser::parseClassesFile() {
    list<Lesson> lessons;
    list<vector<string>> fileRead = readFile("../schedule/classes.csv"); // something like this: [{1LEIC01,L.EIC001,Monday,10.5,1.5,TP}, {1LEIC02,L.EIC001,Thursday,9.5,1.5,TP}]
    for (vector<string> lesson: fileRead) {
        CollegeClass lessonClass = CollegeClass(lesson[0], lesson[1]);
        string lessonWeekday = lesson[2];
        double lessonStartHour = stod(lesson[3]);
        double lessonDuration = stod(lesson[4]);
        string lessonType = lesson[5];
        lessons.push_back(Lesson(lessonClass,lessonWeekday,lessonStartHour,lessonDuration,lessonType));
    }
    return lessons;
}

/**
 * @brief Creates a map of with the lessons for each combination of Uc and Class (CollegeClass)
 * @return a map with the keys as the combination of Uc and Class and the values as its Lessons
 */
map<CollegeClass, list<Lesson>> Parser::mapLessons(){
    list<vector<string>> classesPerUc = readFile("../schedule/classes_per_uc.csv"); // [{L.EIC001,1LEIC01}, {L.EIC001,1LEIC02}, ...]
    list<Lesson> allClasses = parseClassesFile();
    map<CollegeClass, list<Lesson>> mappedLessons;
    for(vector<string> classAndUc : classesPerUc){
        string classCodeTrimmed = classAndUc[1].substr(0, classAndUc[1].length() - 1);
        mappedLessons[CollegeClass(classCodeTrimmed, classAndUc[0])] = findLesson(allClasses, Lesson(CollegeClass(classCodeTrimmed, classAndUc[0]), "*", 0, 0, "*"));
    }
    return mappedLessons;
}

/**
 * @brief Creates a set of students with their lessons from a map of Student and their classes and a map of classes and its lessons 
 * @return a set of students and their lessons
 */
set<Student> Parser::parseStudents() {
    set<Student> students;
    map<Student, list<CollegeClass>> mappedCollegeClasses = mapCollegeClasses();
    map<CollegeClass, list<Lesson>> mappedLessons = mapLessons();

    for(const pair<Student, list<CollegeClass>> &p : mappedCollegeClasses) {
        Schedule toCreate;
        for(CollegeClass c : p.second){
            toCreate.addLessonsFromList(mappedLessons[c]);
        }
        students.insert(Student(p.first.get_studentCode(), p.first.get_studentName(), toCreate));
    }
    return students;
}
/**
 * @brief Creates a map of Student and their current classes from students_classes.csv
 * @return map of students and their classes
 */
map<Student, list<CollegeClass>> Parser::mapCollegeClasses(){
    map<Student, list<CollegeClass>> students;
    Schedule schedule;
    list<vector<string>> fileRead = readFile("../schedule/students_classes.csv");
    for(vector<string> student: fileRead){
        string classCodeTrimmed = student[3].substr(0, student[3].length() - 1);
        Student studentObject = Student(student[0], student[1], schedule);
        students[studentObject].push_back(CollegeClass(classCodeTrimmed, student[2]));
    }
    return students;
}
/**
 * @brief Prints lessons from a list of lessons
 * @param lessons list of lessons to be printed
 */
void Parser::printLessons(list<Lesson> lessons) {
    if(lessons.size() == 0) return;
    for(Lesson lesson : lessons) {
        lesson.printLesson();
    }
}
/**
 * Gets all the lessons for a given combination of Uc and Class of the lessonToFind
 * @param globalLessons list of all lessons
 * @param lessonToFind lesson to be found
 * @return list of lessons for the combination of Uc and Class of the lessonToFind
 */
list<Lesson> Parser::findLesson(list<Lesson> globalLessons, Lesson lessonToFind) {
    list<Lesson> lessons;
    for(Lesson lesson : globalLessons) {
        if(lesson.get_LessonClass() == lessonToFind.get_LessonClass())
            lessons.push_back(lesson);
    }
    return lessons;
}
