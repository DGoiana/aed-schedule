#ifndef AED_SCHEDULE_REQUEST_H
#define AED_SCHEDULE_REQUEST_H

#include "CollegeClass.h"
#include "Dataset.h"
#include <list>
#include <queue>
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

        bool isConflictingSchedule(Schedule studentSchedule, list<Lesson> lessonsToCompare);

        bool addClass(DataSet& dataset,string classToAdd, list<string> newClassUcs = list<string>());
        bool maintainsClassBalance(int sizeStudentCompare);
        bool removeClass(DataSet& dataset,string classToRemove,list<string>& removedElements);
        bool switchClass(DataSet& dataset, string classToRemove, string classToAdd,list<string>& removedElements);


        bool addUc(DataSet& dataset,CollegeClass ucToAdd);
        bool removeUc(DataSet& dataset,CollegeClass UcToRemove);
        bool switchUc(DataSet& dataset,CollegeClass UcToRemove,CollegeClass UcToAdd);

        OPTION get_option();
        TYPE get_type();
        Student get_student();
        CollegeClass get_collegeClass();
        CollegeClass get_newCollegeClass();
};

#endif