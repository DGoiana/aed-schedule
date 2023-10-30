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
    public:
        DataSet();

        Schedule getScheduleByStudent(string studentCode);
        Schedule getScheduleByClass(string classCode);
        
        set<Student> getStudentsByClassOrUc(string code, string id);
        set<Student> getStudentsByYear(string year);
  
        int getNumStudentsInClassAndUc(CollegeClass ucClass);
        int getNumStudentsInClass(string classCode);
        int maxStudentUcInClass(string classCode);

        int numStudentsRegisteredInUcs(int num);

        void setStudentSchedule(list<Lesson> lessonToAdd,Student student);

        int consultClassorUcOccupation(string code, string id);
        int consultYearOccupation(std::string year);

        void sortStudentsByName(vector<Student> &students, string order);
        void sortStudentsByYear(vector<Student> &students, string order);

        Student getStudentByNumber(string studentCode);
        list<Student> getStudentByName(string studentName);

        void sortClassesByOccupation(vector<string> &codes, string order);
        void sortUcsByOccupation(vector<string> &codes, string order);
        void sortYearsByOccupation(vector<string> &years, string order);

        pair<string, int> getMostStudentsUC();
};
#endif