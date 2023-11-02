#include "CollegeClass.h"
#include <list>
#include "Student.h"
#include "Request.h"
#include "Dataset.h"
#include "Parser.h"

#define CLASS_CAP 25


void Request::setStudent(Student student) {
    this->student = student;
}

Student Request::getStudent() {
    return this->student;
}

bool Request::maintainsClassBalance(int sizeStudentCompare) {
    string currentUc = this->collegeClass.get_ucCode();
    list<string> classes = Parser::getUcsByClasses()[currentUc];
    for(string currentClass : classes){
        int ucClassStudents =  dataset.getNumStudentsInClassAndUc(CollegeClass(currentClass,currentUc));
        if(abs(ucClassStudents - (sizeStudentCompare + 1) > 4) && this->option == ADD) return false;
        if(abs(ucClassStudents - (sizeStudentCompare - 1) > 4) && this->option == REMOVE) return false;
    }
    return true;
}

bool Request::isConflictingSchedule(Schedule studentSchedule, list<Lesson> lessonsToCompare) {
    list<Lesson> studentLessons = studentSchedule.get_scheduleLessons();
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


            if (lessonToCompare.get_LessonClass().get_ucCode() == studentLesson.get_LessonClass().get_ucCode())
                return true;
            if (hasConflictTime && hasSameWeekDay) return true;
        }
    }
    return false;
}

bool Request::addClass(DataSet &dataset, string classToAdd) {
    bool failed = false;
    list<string> classUcs = Parser::getUcsByClasses()[classToAdd];
    Student student = dataset.getStudentByNumber(this->student.get_studentCode());
    list<Lesson> oldLessons = this->student.get_studentSchedule().get_scheduleLessons();
    for(string uc : classUcs) {
        CollegeClass currentCC = CollegeClass(classToAdd,uc);
        Request request = Request(currentCC,student,CLASS,ADD,dataset);
        if (!request.addUc(dataset,currentCC)) failed = true;
    }
    if(failed) {
        dataset.setStudentSchedule(oldLessons, this->student);
    }
    return !failed;
}

bool Request::removeClass(DataSet &dataset, string classToRemove) {
    bool failed = false;
    list<string> classUcs = Parser::getUcsByClasses()[classToRemove];
    Student student = dataset.getStudentByNumber(this->student.get_studentCode());
    list<Lesson> oldLessons = this->student.get_studentSchedule().get_scheduleLessons();
    for(string uc : classUcs) {
        CollegeClass currentCC = CollegeClass(classToRemove,uc);
        Request request = Request(currentCC,student,CLASS,ADD,dataset);
        if (!request.removeUc(dataset,currentCC)) failed = true;
    }
    if(failed) {
        dataset.setStudentSchedule(oldLessons, this->student);
    }
    return !failed;
}

bool Request::addUc(DataSet& dataset,CollegeClass collegeClassToAdd) {
    list<Lesson> ccLessons = Parser::mapLessons()[collegeClassToAdd];
    int numCurrentStudents = dataset.getNumStudentsInClassAndUc(collegeClassToAdd);
    if(!isConflictingSchedule(this->student.get_studentSchedule(),ccLessons) 
    && numCurrentStudents < CLASS_CAP
    && maintainsClassBalance(numCurrentStudents)) {
        list<Lesson> newSchedule = dataset.getScheduleByStudent(this->student.get_studentCode()).get_scheduleLessons();
        for(Lesson lesson : ccLessons) newSchedule.push_back(lesson); // this has mostly size 2
        dataset.setStudentSchedule(newSchedule,this->student);
        return true;
    }
    return false;
}

bool Request::removeUc(DataSet& dataset,CollegeClass collegeClassToRemove){
    list<Lesson> ccLessons = Parser::mapLessons()[collegeClassToRemove];
    int numCurrentStudents = dataset.getNumStudentsInClassAndUc(collegeClassToRemove);
    if(maintainsClassBalance(numCurrentStudents)) {
        list<Lesson> newSchedule = dataset.getScheduleByStudent(this->student.get_studentCode()).get_scheduleLessons();
        for(Lesson lesson : ccLessons) // this has mostly size 2
            newSchedule.remove(lesson);
        dataset.setStudentSchedule(newSchedule,this->student);
        return true;
    }
    return false;
}

bool Request::switchUc(DataSet& dataset,CollegeClass collegeClassToRemove,CollegeClass collegeClassToAdd) {
    if(removeUc(dataset,collegeClassToRemove)) {
        this->student = dataset.getStudentByNumber(this->student.get_studentCode());
        if(addUc(dataset,collegeClassToAdd)) return true;
        else {
            // IF ADD FAILS, THEN THE SCHEDULE RESETS TO HOW IT WAS
            list<Lesson> ccLessons = Parser::mapLessons()[collegeClassToRemove];
            list<Lesson> newSchedule = dataset.getScheduleByStudent(this->student.get_studentCode()).get_scheduleLessons();
            for(Lesson lesson : ccLessons) newSchedule.push_back(lesson); // this has mostly size 2
            dataset.setStudentSchedule(newSchedule,this->student);
        }
    }
    return false;
}