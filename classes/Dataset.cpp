#include "Dataset.h"
#include <list>
#include <string>
#include "Student.h"
#include "Lesson.h"
#include <iostream>
#include "Parser.h"
#include <map>
#include <set>
#include <vector>
#include "CollegeClass.h"
#include <algorithm>

using namespace std;

string trimClassCode(string classCode) {
    return classCode.substr(0, classCode.length() - 1);
}

DataSet::DataSet(list<vector<string>> classesPerUc, std::unordered_multimap<pair<string, string>, Lesson, pair_hash> allClasses, list<vector<string>> studentsClasses){
    this->mappedLessons = mapLessons(classesPerUc, allClasses);
    this->mappedStudentsFromClass = mapStudents(studentsClasses);

    this->students = populateStudents(studentsClasses);
    sort(this->students.begin(),this->students.end()); // for binary search purposes
    this->collegeClasses = populateCollegeClasses(classesPerUc);
}

/**
 * Populates the Student with their CollegeClass
 * @param studentsClasses vector of the classes for each Student
 * @return a vector of all Student with their CollegeClass
 */
vector<Student> DataSet::populateStudents(list<vector<string>> studentsClasses){
    vector<Student> students;
    map<pair<string, string>, vector<CollegeClass>> mappedStudents;
    for(vector<string> student: studentsClasses){
        mappedStudents[{student[0], student[1]}].push_back(buildObject(trimClassCode(student[3]), student[2]));
    }

    for(auto p : mappedStudents){
        students.push_back(Student(p.first.first, p.first.second, p.second));
    }
    return students;
} 

list<CollegeClass> DataSet::populateCollegeClasses(list<vector<string>> classesPerUc){
    list<CollegeClass> classes;
    for(vector<string> cc : classesPerUc){
        classes.push_back(buildObject(trimClassCode(cc[1]), cc[0]));
    }
    return classes;
}

/**
 * Builds a college class according to their Schedule, vector of Student
 * @param classCode class identifier
 * @param ucCode uc identifier
 * @return an instance of CollegeClass
 */
CollegeClass DataSet::buildObject(string classCode, string ucCode) {
    Schedule schedule = Schedule(mappedLessons[CollegeClass(classCode, ucCode, {}, Schedule())]);
    vector<Student> students = mappedStudentsFromClass[CollegeClass(classCode, ucCode, {}, Schedule())];
    return CollegeClass(classCode, ucCode, students, schedule);
}

map<CollegeClass, vector<Lesson>> DataSet::mapLessons(list<vector<string>> classesPerUc, std::unordered_multimap<pair<string, string>, Lesson, pair_hash> allClasses){
    map<CollegeClass, vector<Lesson>> mappedLessons;
    for(vector<string> classAndUc : classesPerUc){
        mappedLessons[CollegeClass(trimClassCode(classAndUc[1]), classAndUc[0], {}, Schedule())] = findLesson(allClasses, Lesson({trimClassCode(classAndUc[1]), classAndUc[0]}, "*", 0, 0, "*"));
    }
    return mappedLessons;
}

map<CollegeClass, vector<Student>> DataSet::mapStudents(list<vector<string>> studentsClasses){
    map<CollegeClass, vector<Student>> mappedCollegeClass;
    for(vector<string> student: studentsClasses){
        mappedCollegeClass[CollegeClass(trimClassCode(student[3]), student[2], {}, Schedule())].push_back(Student(student[0], student[1], {}));
    }
    return mappedCollegeClass;
}

vector<Lesson> DataSet::findLesson(std::unordered_multimap<pair<string, string>, Lesson, pair_hash> globalLessons, Lesson lessonToFind) {
    vector<Lesson> lessons;
    auto range = globalLessons.equal_range({lessonToFind.get_classCode(), lessonToFind.get_ucCode()});
    for (auto i = range.first; i != range.second; ++i) {
        lessons.push_back(i->second);
    }
    return lessons;
}

map<string, list<string>> DataSet::getUcsByClasses(list<vector<string>> classesPerUc) // [LEIC01: {L.EIC01, L.EIC02}, ...]
{
    map<string,list<string>> result;
    for(vector<string> classAndUc : classesPerUc) {
        result[trimClassCode(classAndUc[1])].push_back(classAndUc[0]);
    }
    return result;
}

/**
 * Searches a given Student in the vector of all Student.
 * Time Complexity: O(log N)
 * @param classCode classCode of the Student to be found
 * @return the Student to be found
 */
Student& DataSet::binarySearchStudentbyNumber(string classCode) {
    int h = students.size() - 1;
    int l = 0;
    while(l <= h) {
        int m = l + (h-l) / 2;
        if(this->students[m].get_studentCode() == classCode) return students[m];
        if(this->students[m].get_studentCode() < classCode) l = m + 1;
        else h = m - 1;
    }
    throw std::runtime_error("Student not found");
}