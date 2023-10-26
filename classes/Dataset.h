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
        DataSet();

        Schedule getScheduleByStudent(Student student);
        Schedule getScheduleByClass(CollegeClass collegeClass);
        
        list<Student> getStudentsByClass(CollegeClass collegeClass);
        list<Student> getStudentsByCourse(Uc uc);
        list<Student> getStudentsByYear(std::string year);

        int numStudentsRegisteredInUcs(int num);

        list<Student> consultClassOccupation(CollegeClass collegeClass);
        list<Student> consultYearOccupation(std::string year);
        list<Student> consultUcOccupation(Uc uc);

        void sortByUcAscending(std::list<Student>& students);
        void sortByUcDescending(std::list<Student>& students);
        void sortByClassAscending(std::list<Student>& students);
        void sortByClassDescending(std::list<Student>& students);

        int getMostStudentsUC();
};
#endif