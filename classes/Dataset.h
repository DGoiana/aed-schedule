#ifndef AED_SCHEDULE_DATASET_H
#define AED_SCHEDULE_DATASET_H

#include <string>
#include "Parser.h"
#include "Student.h"
#include "Lesson.h"

class DataSet{
    private:
        vector<Student> students;
        list<CollegeClass> collegeClasses;
        map<CollegeClass, vector<Lesson>> mappedLessons;
        map<CollegeClass, vector<Student>> mappedStudentsFromClass;
    public:
        DataSet(list<vector<string>> classesPerUc, std::unordered_multimap<pair<string, string>, Lesson, pair_hash> classes, list<vector<string>> studentsClasses);

        vector<Student> get_students() { return students; }
        list<CollegeClass>& get_collegeClasses() { return collegeClasses; }

        vector<Student> populateStudents(list<vector<string>> studentsClasses);
        list<CollegeClass> populateCollegeClasses(list<vector<string>> classesPerUc);
        
        CollegeClass buildObject(string classCode, string ucCode);

        map<CollegeClass, vector<Lesson>> mapLessons(list<vector<string>> classesPerUc, std::unordered_multimap<pair<string, string>, Lesson, pair_hash> allClasses);
        map<CollegeClass, vector<Student>> mapStudents(list<vector<string>> studentsClasses);

        vector<Lesson> findLesson(std::unordered_multimap<pair<string, string>, Lesson, pair_hash> globalLessons, Lesson lessonToFind);

        map<string, list<string>> getUcsByClasses(list<vector<string>> classesPerUc);

        Student& binarySearchStudentbyNumber(string classCode);

        void dumpCurrentState();
};
#endif