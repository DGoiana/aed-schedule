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
    this->collegeClasses = populateCollegeClasses(classesPerUc);
}

vector<Student> DataSet::populateStudents(list<vector<string>> studentsClasses){
    vector<Student> students;
    map<pair<string, string>, set<CollegeClass>> mappedStudents;
    for(vector<string> student: studentsClasses){
        mappedStudents[{student[0], student[1]}].insert(buildObject(trimClassCode(student[3]), student[2]));
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

CollegeClass DataSet::buildObject(string classCode, string ucCode) {
    Schedule schedule = Schedule(mappedLessons[CollegeClass(classCode, ucCode, {}, Schedule())]);
    set<Student> students = mappedStudentsFromClass[CollegeClass(classCode, ucCode, {}, Schedule())];
    return CollegeClass(classCode, ucCode, students, schedule);
}

map<CollegeClass, vector<Lesson>> DataSet::mapLessons(list<vector<string>> classesPerUc, std::unordered_multimap<pair<string, string>, Lesson, pair_hash> allClasses){
    map<CollegeClass, vector<Lesson>> mappedLessons;
    for(vector<string> classAndUc : classesPerUc){
        mappedLessons[CollegeClass(trimClassCode(classAndUc[1]), classAndUc[0], {}, Schedule())] = findLesson(allClasses, Lesson({trimClassCode(classAndUc[1]), classAndUc[0]}, "*", 0, 0, "*"));
    }
    return mappedLessons;
}

map<CollegeClass, set<Student>> DataSet::mapStudents(list<vector<string>> studentsClasses){
    map<CollegeClass, set<Student>> mappedCollegeClass;
    for(vector<string> student: studentsClasses){
        mappedCollegeClass[CollegeClass(trimClassCode(student[3]), student[2], {}, Schedule())].insert(Student(student[0], student[1], {}));
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