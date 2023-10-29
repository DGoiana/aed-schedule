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
        int getNumStudentsInClass(CollegeClass ucClass);
        int getNumStudentsInUc(CollegeClass ucClass);
        list<Student> getStudentsByYear(string year);

        int numStudentsRegisteredInUcs(int num);

        void setStudentSchedule(list<Lesson> lessonToAdd,Student student);
        void setStudentsList(set<Student> newStudentList);

        int consultClassorUcOccupation(string code, string id);
        list<int> consultOccupationClassByUc(string classCode);
        int consultYearOccupation(std::string year);

        Student getStudentByNumber(string studentCode);
        list<Student> getStudentByName(string studentName);

        void sortByUcAscending(std::list<Student>& students);
        void sortByUcDescending(std::list<Student>& students);
        void sortByClassAscending(std::list<Student>& students);
        void sortByClassDescending(std::list<Student>& students);

        int getMostStudentsUC();
};
#endif