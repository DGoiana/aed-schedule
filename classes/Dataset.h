#ifndef AED_SCHEDULE_DATASET_H
#define AED_SCHEDULE_DATASET_H

#include <string>
#include "Parser.h"
#include "Student.h"
#include "Lesson.h"

class DataSet{
    private:
        set<Student> students;
        list<Lesson> lessons;
    public:
        void showStudentSchedule(Student student);
        void showClassSchedule(CollegeClass collegeClass);
        
        list<Student> getStudentsByClass(CollegeClass collegeClass);
        list<Student> getStudentsByCourse(Uc uc);
        list<Student> getStudentsByYear(string year);

        int numStudentsRegisteredInUcs(int num);

        list<Student> consultClassOccupation(CollegeClass collegeClass);
        list<Student> consultYearOccupation(string year);
        list<Student> consultUcOccupation(Uc uc);

        void sortByUcAscending(list<Student>& students);
        void sortByUcDescending(list<Student>& students);
        void sortByClassAscending(list<Student>& students);
        void sortByClassDescending(list<Student>& students);
        
        int getMostStudentsUC();
};
#endif