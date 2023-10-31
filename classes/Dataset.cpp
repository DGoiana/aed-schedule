#include "Dataset.h"
#include <list>
#include <string>
#include "Student.h"
#include "Lesson.h"
#include "Parser.h"
#include <algorithm>

using namespace std;

DataSet::DataSet(){
    this->students = Parser::parseStudents();
    this->lessons = Parser::mapLessons();
}
/**
 * Get the Schedule of a Student according to their studentCode
 * Time Complexity: O(n)
 * @param studentCode code of the student
 * @return the Schedule of the Student with the studentCode
 */
Schedule DataSet::getScheduleByStudent(string studentCode){
    for(Student s : students){
        if(s.get_studentCode() == studentCode) return s.get_studentSchedule();
    }
    return Schedule();
}
/**
 * Get the Schedule of a Class according to its classCode
 * Time Complexity: O(n)
 * @param classCode code of the Class
 * @return the Schedule of the Class with the classCode
 */
Schedule DataSet::getScheduleByClass(string classCode){
    Schedule result;
    auto it = lessons.begin();
    while(it != lessons.end()){
        if(it->first.get_classCode() == classCode) result.addLessonsFromList(it->second);
        it++;
    }
    return result;
}
/**
 * Get set of Student that belong either to a Class or an Uc
 * Time Complexity: O(n²)
 * @param code classCode or ucCode
 * @param id either "class" for Class or "uc" for Uc
 * @return a set of Student that belongs to a Class or an Uc
 */
set<Student> DataSet::getStudentsByClassOrUc(string code, string id){
    set<Student> students;
    for(Student s : this->students){
        for(Lesson l : s.get_studentSchedule().get_scheduleLessons()){
            if(l.get_LessonClass().get_classCode() == code && id == "class") students.insert(s);
            if(l.get_LessonClass().get_ucCode() == code && id == "uc") students.insert(s);
        }
    }
    return students;
}
/**
 * Get the number of Student in a given combination of Class and Uc
 * Time Complexity: O(n²)
 * @param ucClass combination of class and Uc
 * @return the number of Student in a given combination of Class and Uc
 */
int DataSet::getNumStudentsInClassAndUc(CollegeClass ucClass)
{
    list<Student> resultStudents;
    for(Student student : this->students) {
        for(Lesson lesson : student.get_studentSchedule().get_scheduleLessons()) {
            if(lesson.get_LessonClass() == ucClass) resultStudents.push_back(student); 
        }
    }
    resultStudents.unique();
    return resultStudents.size();
}
/**
 * Get the number of Student in a given Class
 * Time Complexity: O(n)
 * @param classCode code of the class
 * @return the number of Student in Class
 */
int DataSet::getNumStudentsInClass(string classCode)
{
    return getStudentsByClassOrUc(classCode,"class").size();
}
/**
 * Get the maximum number of Student enrolled in the Ucs of a given Class
 * Time Complexity: O(n)
 * @param classCode code of the Class
 * @return the maximum number of Student enrolled in the Ucs of a given Class
 */
int DataSet::maxStudentUcInClass(string classCode)
{
    map<string,list<string>> ucsByClasses = Parser::getUcsByClasses();
    list<string> ucsByClass = ucsByClasses[classCode];
    int max = 0;
    for(string uc : ucsByClass) {
        int ucClassStudents =  getNumStudentsInClassAndUc(CollegeClass(classCode,uc));
        if(ucClassStudents > max) max = ucClassStudents;
    }
    return max;
}
/**
 * Get set of Student born in a given year
 * Time Complexity: O(n)
 * @param year year of birth of students
 * @return a set of Student in a given year
 */
set<Student> DataSet::getStudentsByYear(string year){
    set<Student> students;
    for(Student s : this->students){
        if(s.get_studentCode().substr(0,4) == year) students.insert(s);
    }
    return students;
}
/**
 * Get number of Student registered in a given number of Ucs
 * Time complexity: O(n)
 * @param num number of Ucs
 * @return the number of Student that are registered in a given number of Ucs
 */
int DataSet::numStudentsRegisteredInUcs(int num){
    int count = 0;
    map<Student, list<CollegeClass>> mappedCollegeClasses = Parser::mapCollegeClasses();
    for(auto p : mappedCollegeClasses){
        int result = 0;
        string ucToCheck = "";
        for(CollegeClass c : p.second){
            if(c.get_ucCode() != ucToCheck) result++;
            ucToCheck = c.get_ucCode();
        }
        if(result >= num) count++;
    }
    return count;
}
/**
 * Get the number of Student that belong either to a Class or an Uc
 * Time Complexity: O(n²)
 * @param code classCode or ucCode
 * @param id either "class" for Class or "uc" for Uc
 * @return a list of Student that belongs to a Class or an Uc
 */
int DataSet::consultClassorUcOccupation(string code, string id){
    int num = 0;
    for(Student s : this->students){
        for(Lesson l : s.get_studentSchedule().get_scheduleLessons()){
            if(l.get_LessonClass().get_classCode() == code && id == "class") num++;
            if(l.get_LessonClass().get_ucCode() == code && id == "uc") num++;
        }
    }
    return num;
}
/**
 * Get the number of Student that were born in a given year by their studentCode
 * Time Complexity: O(n)
 * @param year year of birth of students
 * @return the number of Student that were born in a given year
 */
int DataSet::consultYearOccupation(string year){
    int num = 0;
    for(Student s : this->students){
        if(s.get_studentCode().substr(0,4) == year) num++;
    }
    return num;
}
/**
 * Sorts a Student vector by their name (ascending or descending)
 * Time Complexity: O(nlogn)
 * @param students
 * @param order
 */
void DataSet::sortStudentsByName(vector<Student> &students, string order){
    if(order == "ascending") sort(students.begin(), students.end(), [](Student s1, Student s2){
        return s1.get_studentName() < s2.get_studentName();
    });
    else sort(students.begin(), students.end(), [](Student s1, Student s2){
        return s1.get_studentName() > s2.get_studentName();
    });
}
/**
 * Sorts a Student vector by their year of birth (ascending or descending)
 * Time Complexity: O(nlogn)
 * @param students
 * @param order
 */
void DataSet::sortStudentsByYear(vector<Student> &students, string order){
    if(order == "ascending") sort(students.begin(), students.end(), [](Student s1, Student s2){
        return s1.get_studentCode() < s2.get_studentCode();
    });
    else sort(students.begin(), students.end(), [](Student s1, Student s2){
        return s1.get_studentCode() > s2.get_studentCode();
    });
}
/**
 * Sorts a Classes by its occupation (ascending or descending)
 * Time Complexity: O(nlogn)
 * @param students
 * @param order
 */
void DataSet::sortClassesByOccupation(vector<string> &codes, string order){
    if(order == "ascending") sort(codes.begin(), codes.end(), [this](string code1, string code2){
        return consultClassorUcOccupation(code1, "class") < consultClassorUcOccupation(code2, "class");
    });
    else sort(codes.begin(), codes.end(), [this](string code1, string code2){
        return consultClassorUcOccupation(code1, "class") > consultClassorUcOccupation(code2, "class");
    });
}
/**
 * Sorts a Ucs by their occupation (ascending or descending)
 * Time Complexity: O(nlogn)
 * @param students
 * @param order
 */
void DataSet::sortUcsByOccupation(vector<string> &codes, string order){
    if(order == "ascending") sort(codes.begin(), codes.end(), [this](string code1, string code2){
        return consultClassorUcOccupation(code1, "uc") < consultClassorUcOccupation(code2, "uc");
    });
    else sort(codes.begin(), codes.end(), [this](string code1, string code2){
        return consultClassorUcOccupation(code1, "uc") > consultClassorUcOccupation(code2, "uc");
    });
}
/**
 * Sorts a Years by their occupation (ascending or descending)
 * Time Complexity: O(nlogn)
 * @param students
 * @param order
 */
void DataSet::sortYearsByOccupation(vector<string> &years, string order){
    if(order == "ascending") sort(years.begin(), years.end(), [this](string year1, string year2){
        return consultYearOccupation(year1) < consultYearOccupation(year2);
    });
    else sort(years.begin(), years.end(), [this](string year1, string year2){
        return consultYearOccupation(year1) > consultYearOccupation(year2);
    });
}
/**
 * Gets the Uc with the most number of Student
 * Time Complexity: O(n²)
 * @return a pair of the ucCode and the number of Student
 */
pair<string, int> DataSet::getMostStudentsUC(){
    map<Student, list<CollegeClass>> mappedCollegeClasses = Parser::mapCollegeClasses(); // [{Student, {{1LEIC01, L.EIC001}, {1LEIC01, L.EIC002}}, ...}]
    map<string, int> ucByNumStudents;
    for(auto p : mappedCollegeClasses){
        string ucToCheck = "";
        for(CollegeClass c : p.second){
            if(c.get_ucCode() != ucToCheck) ucByNumStudents[c.get_ucCode()]++;
            ucToCheck = c.get_ucCode();
        }
    }
    pair<string, int> result = {"", 0};
    for(auto it = ucByNumStudents.begin(); it != ucByNumStudents.end(); it++){
        if(it->second > result.second){
            result = *it;
        }
    }
    return result;
}
/**
 * Sets the current Schedule of a Student in the dataset
 * Time Complexity: O(1)
 * @param newLessons list of lessons of the new Schedule
 * @param student student to get Schedule changed
 */
void DataSet::setStudentSchedule(list<Lesson> newLessons,Student student) {
    this->students.erase(this->students.find(student));
    student.set_studentSchedule(newLessons);
    this->students.insert(student);
}
/**
 * Get Student by their studentCode
 * Time Complexity: O(logn)
 * @param studentCode code of the student
 * @return the Student with studentCode
 */
Student DataSet::getStudentByNumber(string studentCode)
{
    return *this->students.find(Student(studentCode,"",Schedule()));
}
/**
 * Get list of Student with a given name
 * Time Complexity: O(n)
 * @param studentName name of the student
 * @return a list of Student that have studentName
 */
list<Student> DataSet::getStudentByName(string studentName)
{
    list<Student> sameNameStudents;
    for(Student student : this->students){
        if(student.get_studentName() == studentName)
            sameNameStudents.push_back(student);
    }
    return sameNameStudents;
}
