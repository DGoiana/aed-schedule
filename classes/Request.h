#include "CollegeClass.h"
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
        CollegeClass collegeClass;
        CollegeClass newCollegeClass;
        Student& student;
        TYPE type;
        OPTION option;
        static list<Request> globalRequests;
    private:
        Request(CollegeClass collegeClass,Student& student, TYPE type, OPTION option) : 
        collegeClass(collegeClass),newCollegeClass(collegeClass),student(student),type(type),option(option) {}; // SHHH
        Request(CollegeClass collegeClass,CollegeClass newCollegeClass,Student& student, TYPE type, OPTION option) : 
        collegeClass(collegeClass),student(student),type(type),option(option) {};

        bool handleRequest();
        bool isConflictingLesson(list<Lesson> studentLessons, Lesson lessonToCompare);

        bool addClass(CollegeClass classToAdd);
        bool isConflictingClass();
        bool maintainsClassBalance();
        bool removeClass(CollegeClass classToRemove);
        bool switchClass(CollegeClass classToRemove,CollegeClass classToAdd);


        bool addUc(CollegeClass UcToAdd);
        bool isConflictingUc();
        list<Lesson> getVacancies(list<Lesson> currentUcLessons);
        bool removeUc(CollegeClass UcToRemove);
        bool switchUc(CollegeClass UcToRemove,CollegeClass UcToAdd);



};