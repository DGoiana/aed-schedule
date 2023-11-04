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
    public:
        DataSet();

        Schedule getScheduleByStudent(string studentCode);
        Schedule getScheduleByClass(string classCode);
        
        vector<Student> getStudentsByClassOrUc(string code, string id);
        vector<Student> getStudentsByYear(string year);
  
        int getNumStudentsInClassAndUc(CollegeClass ucClass);

        int numStudentsRegisteredInNUcs(int num);

        void setStudentClasses(set<CollegeClass> newClasses, Student student);
        void addStudentClass(CollegeClass c, Student student);

        int consultClassorUcOccupation(string code, string id);
        int consultYearOccupation(std::string year);

        void sortStudentsByNameOrYear(vector<Student> &students, string order, string input);

        Student getStudentByNumber(string studentCode);
        list<Student> getStudentByName(string studentName);

        vector<string> getClasses();
        vector<string> getUcs();

        void sortClassesByOccupation(vector<string> &codes, string order);
        void sortUcsByOccupation(vector<string> &codes, string order);
        void sortYearsByOccupation(vector<string> &years, string order);

        void dumpCurrentState();

        string getMostStudentsUC();
};
#endif