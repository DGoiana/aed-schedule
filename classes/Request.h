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

        bool handleRequest();
        bool isConflictingUcClass(list<Lesson> studentLessons, list<Lesson> lessonsToCompare);

        bool addClass(DataSet& dataset,CollegeClass classToAdd);
        bool removeClass(DataSet& dataset,CollegeClass classToRemove);
        bool switchClass(DataSet& dataset,CollegeClass classToRemove,CollegeClass classToAdd);


        bool addUc(DataSet& dataset,CollegeClass ucToAdd);
        bool removeUc(DataSet& dataset,CollegeClass UcToRemove);
        bool switchUc(DataSet& dataset,CollegeClass UcToRemove,CollegeClass UcToAdd);



};