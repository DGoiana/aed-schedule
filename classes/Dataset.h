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
        
        list<Student> getStudentsByClassOrUc(string code, string id);
        list<Student> getStudentsByYear(string year);

        int numStudentsRegisteredInUcs(int num);

        int consultClassorUcOccupation(string code, string id);
        int consultYearOccupation(std::string year);

        void sortStudentsByName(vector<Student> &students, string order);
        void sortStudentsByYear(vector<Student> &students, string order);

        void sortClassesByOccupation(vector<string> &codes, string order);
        void sortUcsByOccupation(vector<string> &codes, string order);
        void sortYearsByOccupation(vector<string> &years, string order);

        pair<string, int> getMostStudentsUC();
};
#endif