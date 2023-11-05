#include "CollegeClass.h"
#include <list>
#include <queue>
#include "Student.h"
#include <iostream>
#include "Request.h"
#include "Dataset.h"
#include "Parser.h"
#include "menuFunctions.h"

#define CLASS_CAP 25

bool Request::maintainsClassBalance(DataSet &dataset, int sizeStudentCompare, list<vector<string>> classesPerUc) {
    string currentUc = this->collegeClass.get_ucCode();
    list<string> classes = dataset.getUcsByClasses(classesPerUc)[currentUc];
    for(string currentClass : classes){
        int ucClassStudents =  getNumStudentsInClassAndUc(CollegeClass(currentClass,currentUc, {}, Schedule()), dataset);
        if(abs(ucClassStudents - (sizeStudentCompare + 1) > 4) && this->option == ADD) return false;
        if(abs(ucClassStudents - (sizeStudentCompare - 1) > 4) && this->option == REMOVE) return false;
    }
    return true;
}

bool Request::isConflictingSchedule(Schedule studentSchedule, vector<Lesson> lessonsToCompare) {
    vector<Lesson> studentLessons = studentSchedule.get_scheduleLessons();
    for(Lesson lessonToCompare : lessonsToCompare) {
        for(Lesson studentLesson : studentLessons){
            double studentStartTime = studentLesson.get_LessonStartHour();
            double studentFinishTime = studentStartTime + studentLesson.get_LessonDuration();
            double lessonToCompareStartTime = lessonToCompare.get_LessonStartHour(); 
            double lessonToCompareFinishTime = lessonToCompareStartTime + lessonToCompare.get_LessonDuration();

            bool hasSameWeekDay = lessonToCompare.get_LessonWeekday() == studentLesson.get_LessonWeekday();
            bool hasConflictTime =  (lessonToCompareStartTime > studentStartTime && lessonToCompareStartTime < studentFinishTime) 
                                || (lessonToCompareFinishTime > studentStartTime && lessonToCompareFinishTime < studentFinishTime)
                                || (lessonToCompareStartTime < studentStartTime && lessonToCompareFinishTime > studentFinishTime);

            if (lessonToCompare.get_ucCode() == studentLesson.get_ucCode())
                return true;
            if (hasConflictTime && hasSameWeekDay) return true;
        }
    }
    return false;
}

bool Request::addClass(DataSet &dataset, string classToAdd, list<vector<string>> classesPerUc) {
    bool failed = false;
    list<string> classUcs = dataset.getUcsByClasses(classesPerUc)[classToAdd]; // get all ucs from class
    vector<CollegeClass> oldClasses = find(dataset.get_students().begin(), dataset.get_students().end(), Student(studentCode, "", {}))->get_studentClasses();
    for(string uc : classUcs) {
        CollegeClass currentCC = dataset.buildObject(classToAdd, uc);
        Request request = Request(currentCC, studentCode, UC, ADD, dataset);
        if (!request.addUc(dataset, currentCC, classesPerUc)) failed = true;
    }
    if(failed) {
        setStudentClasses(oldClasses, studentCode, dataset);
    }
    return !failed;
}

bool Request::removeClass(DataSet &dataset, string classToRemove, list<vector<string>> classesPerUc) {
    bool failed = false;
    list<string> classUcs = dataset.getUcsByClasses(classesPerUc)[classToRemove]; // 
    vector<CollegeClass> oldClasses = find(dataset.get_students().begin(), dataset.get_students().end(), Student(studentCode, "", {}))->get_studentClasses();
    for(string uc : classUcs) {
        CollegeClass currentCC = CollegeClass(classToRemove, uc, {}, Schedule());
        Request request = Request(currentCC, studentCode, UC, REMOVE, dataset);
        if (!request.removeUc(dataset, currentCC, classesPerUc)) failed = true;
    }
    if(failed) {
        setStudentClasses(oldClasses, studentCode, dataset);
    }
    return !failed;
}

bool Request::addUc(DataSet& dataset,CollegeClass collegeClassToAdd, list<vector<string>> classesPerUc) {
    int numCurrentStudents = getNumStudentsInClassAndUc(collegeClassToAdd, dataset);
    if(!isConflictingSchedule(getScheduleByStudent(studentCode, dataset), collegeClassToAdd.get_collegeClassSchedule().get_scheduleLessons()) 
    && numCurrentStudents < CLASS_CAP
    && maintainsClassBalance(dataset, numCurrentStudents, classesPerUc)) {
        addStudentClass(collegeClassToAdd, studentCode, dataset);
        return true;
    }
    return false;
}

bool Request::removeUc(DataSet& dataset, CollegeClass collegeClassToRemove, list<vector<string>> classesPerUc){
    int numCurrentStudents = getNumStudentsInClassAndUc(collegeClassToRemove, dataset);
    if(maintainsClassBalance(dataset, numCurrentStudents, classesPerUc)) {
        vector<CollegeClass> toRemove = find(dataset.get_students().begin(), dataset.get_students().end(), Student(studentCode, "", {}))->get_studentClasses();;
        toRemove.erase(find(toRemove.begin(), toRemove.end(), collegeClassToRemove));
        setStudentClasses(toRemove, studentCode, dataset);
        return true;
      }
     return false;
}

// void Request::addRequestToQueue(Request request){
//     this->requests.push(request);
// }

// void Request::removeRequestFromQueue(){
//     Request request = this->requests.front();
//     if(request.get_type() == CLASS){
//         if(request.get_option() == ADD){
//             //È só fazer remove
//         }
//         if(request.get_option() == REMOVE){
//             //È só fazer add
//         }
//         if(request.get_option() == SWITCH){
//             //È só fazer add e remove
//         }
//     }
//     else if(request.get_type() == UC){
//         if(request.get_option() == ADD){
//             //È só fazer remove
//         }
//         if(request.get_option() == REMOVE){
//             //È só fazer add
//         }
//         if(request.get_option() == SWITCH){
//             //È só fazer add e remove
//         }
//     }
//     this->requests.pop();
// }

OPTION Request::get_option(){
    return this->option;
}

TYPE Request::get_type(){
    return this->type;
}

string Request::get_student(){
    return this->studentCode;
}

CollegeClass Request::get_collegeClass(){
    return this->collegeClass;
}

CollegeClass Request::get_newCollegeClass(){
    return this->newCollegeClass;
}

bool Request::switchUc(DataSet& dataset, CollegeClass collegeClassToRemove, CollegeClass collegeClassToAdd, list<vector<string>> classesPerUc) {
    if(removeUc(dataset, collegeClassToRemove, classesPerUc)) {
        if(!addUc(dataset, collegeClassToAdd, classesPerUc)){
            addUc(dataset, collegeClassToRemove, classesPerUc);
            return false;
        }
    }
    return false;
}

bool Request::switchClass(DataSet& dataset, string classToRemove, string classToAdd, list<vector<string>> classesPerUc){
    if(removeClass(dataset, classToRemove, classesPerUc)){
        if(!addClass(dataset,classToAdd, classesPerUc)){
            addClass(dataset,classToRemove, classesPerUc);
            return false;
        }
    }
    return true;
}