#include "CollegeClass.h"
#include "Dataset.h"
#include <list>
#include "Student.h"

enum TYPE {
    UC,
    CLASS
};

enum OPTION {
    ADD,
    REMOVE,
    SWITCH
};

class Request {
    private:
        DataSet& dataset;
        CollegeClass collegeClass;
        CollegeClass newCollegeClass;
        Student student;
        TYPE type;
        OPTION option;
        static list<Request> globalRequests;
    public:
        Request(CollegeClass collegeClass,Student& student, TYPE type, OPTION option, DataSet& dataset) : 
        collegeClass(collegeClass),newCollegeClass(collegeClass),student(student),type(type),option(option),dataset(dataset) {}; // SHHH
        Request(CollegeClass collegeClass,CollegeClass newCollegeClass,Student& student, TYPE type, OPTION option,DataSet dataset) : 
        collegeClass(collegeClass),newCollegeClass(newCollegeClass),student(student),type(type),option(option),dataset(dataset) {};

        void setStudent(Student student);
        Student getStudent();

        bool isConflictingSchedule(Schedule studentSchedule, list<Lesson> lessonsToCompare);

        bool addClass(DataSet& dataset,string classToAdd);
        bool maintainsClassBalance(int sizeStudentCompare);
        bool removeClass(DataSet& dataset,string classToRemove);


        bool addUc(DataSet& dataset,CollegeClass ucToAdd);
        bool removeUc(DataSet& dataset,CollegeClass UcToRemove);
        bool switchUc(DataSet& dataset,CollegeClass UcToRemove,CollegeClass UcToAdd);



};