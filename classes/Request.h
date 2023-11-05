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
        Student& student;
        TYPE type;
        OPTION option;
        static list<Request> globalRequests;
    public:
        Request(CollegeClass collegeClass, Student& student, TYPE type, OPTION option, DataSet& dataset) : 
        collegeClass(collegeClass),newCollegeClass(collegeClass),student(student),type(type),option(option),dataset(dataset) {}; // SHHH

        Request(CollegeClass collegeClass,CollegeClass newCollegeClass,Student& student, TYPE type, OPTION option,DataSet& dataset) : 
        collegeClass(collegeClass),newCollegeClass(newCollegeClass),student(student),type(type),option(option), dataset(dataset) {};

        bool isConflictingSchedule(Schedule studentSchedule, vector<Lesson> lessonsToCompare);

        bool addClass(DataSet& dataset,string classToAdd, list<vector<string>> classesPerUc);
        bool maintainsClassBalance(DataSet& dataset, int sizeStudentCompare, list<vector<string>> classesPerUc);
        bool removeClass(DataSet& dataset,string classToRemove, list<vector<string>> classesPerUc);
        bool switchClass(DataSet& dataset, string classToRemove, string classToAdd, list<vector<string>> classesPerUc);


        bool addUc(DataSet& dataset,CollegeClass ucToAdd, list<vector<string>> classesPerUc);
        bool removeUc(DataSet& dataset,CollegeClass UcToRemove, list<vector<string>> classesPerUc);
        bool switchUc(DataSet& dataset,CollegeClass UcToRemove, CollegeClass UcToAdd, list<vector<string>> classesPerUc);

        OPTION get_option();
        TYPE get_type();
        Student get_student();
        CollegeClass get_collegeClass();
        CollegeClass get_newCollegeClass();
};