#ifndef AED_SCHEDULE_DATASET_H
#define AED_SCHEDULE_DATASET_H

#include <string>
#include "Parser.h"
#include "Student.h"
#include "Lesson.h"

class DataSet{
    private:
        set<Student> students;
        map<CollegeClass, list<Lesson>> lessons;
        set<string> classes;
        set<string> ucs;
    public:
        DataSet();

        Schedule getScheduleByStudent(string studentCode);
        Schedule getScheduleByClass(string classCode);
        
        vector<Student> getStudentsByClassOrUc(string code, string id);
        vector<Student> getStudentsByYear(string year);
  
        int getNumStudentsInClassAndUc(CollegeClass ucClass);;
        int maxStudentUcInClass(string classCode);

        int numStudentsRegisteredInNUcs(int num);

        void setStudentSchedule(list<Lesson> lessonToAdd,Student student);

        int consultClassorUcOccupation(string code, string id);
        int consultYearOccupation(std::string year);

        void sortStudentsByNameOrYear(vector<Student> &students, string order, string input);

        Student getStudentByNumber(string studentCode);
        list<Student> getStudentByName(string studentName);

        void sortClassesByOccupation(vector<string> &codes, string order);
        void sortUcsByOccupation(vector<string> &codes, string order);
        void sortYearsByOccupation(vector<string> &years, string order);

        string getMostStudentsUC();
};
#endif