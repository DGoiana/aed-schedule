#ifndef AED_SCHEDULE_REQUEST_H
#define AED_SCHEDULE_REQUEST_H

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

/**
 * The request class processes some calls made by the menu. It has:
 * <ul>
 *  <li> The dataset to change the programs state
 *  <li> A collegeClass to add or remove
 *  <li> A newColleClass for switch requests
 *  <li> The Student to have its Schedule changed
 *  <li> Type of the Request (CLASS or UC)
 *  <li> Option of the Request (ADD or REMOVE or SWITCH)
 * <ul>
 */
class Request {
    private:
        DataSet& dataset;
        CollegeClass collegeClass;
        CollegeClass newCollegeClass;
        Student& student;
        TYPE type;
        OPTION option;
    public:
        Request(CollegeClass collegeClass, Student& student, TYPE type, OPTION option, DataSet& dataset) : 
        collegeClass(collegeClass),newCollegeClass(collegeClass),student(student),type(type),option(option),dataset(dataset) {}; // SHHH

        Request(CollegeClass collegeClass,CollegeClass newCollegeClass,Student& student, TYPE type, OPTION option,DataSet& dataset) : 
        collegeClass(collegeClass),newCollegeClass(newCollegeClass),student(student),type(type),option(option), dataset(dataset) {};

        bool isConflictingSchedule(Schedule studentSchedule, vector<Lesson> lessonsToCompare);

        bool addClass(DataSet& dataset,string classToAdd, list<vector<string>> classesPerUc, list<string> newClassUcs = list<string>(), string undo = "");
        bool maintainsClassBalance(DataSet& dataset, int sizeStudentCompare, list<vector<string>> classesPerUc);
        bool removeClass(DataSet& dataset,string classToRemove, list<vector<string>> classesPerUc, list<string>& removedElements);
        bool switchClass(DataSet& dataset, string classToRemove, string classToAdd, list<vector<string>> classesPerUc, list<string>& removedElements, string undo="");


        bool addUc(DataSet& dataset,CollegeClass ucToAdd, list<vector<string>> classesPerUc);
        bool removeUc(DataSet& dataset,CollegeClass UcToRemove, list<vector<string>> classesPerUc);
        bool switchUc(DataSet& dataset,CollegeClass UcToRemove, CollegeClass UcToAdd, list<vector<string>> classesPerUc);

        OPTION get_option();
        TYPE get_type();
        Student get_student();
        CollegeClass get_collegeClass();
        CollegeClass get_newCollegeClass();
};

#endif