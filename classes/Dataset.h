#ifndef AED_SCHEDULE_DATASET_H
#define AED_SCHEDULE_DATASET_H

#include <string>
#include "Parser.h"
#include "Student.h"
#include "Lesson.h"

class DataSet{
    private:
        map<long, Student> students;
        list<Lesson> lessons;
    public:
        DataSet();

        Schedule getScheduleByStudent(long studentCode);
        Schedule getScheduleByClass(CollegeClass collegeClass);
        
        list<Student> getStudentsByClass(CollegeClass collegeClass);
        list<Student> getStudentsByCourse(CollegeClass collegeClass);
        list<Student> getStudentsByYear(std::string year);

        int numStudentsRegisteredInUcs(int num);

        list<Student> consultClassOccupation(CollegeClass collegeClass);
        list<Student> consultYearOccupation(std::string year);
        list<Student> consultUcOccupation(CollegeClass collegeClass);

        void sortByUcAscending(std::list<Student>& students);
        void sortByUcDescending(std::list<Student>& students);
        void sortByClassAscending(std::list<Student>& students);
        void sortByClassDescending(std::list<Student>& students);

        int getMostStudentsUC();
};
#endif