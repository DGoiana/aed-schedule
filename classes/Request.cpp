#include "CollegeClass.h"
#include <list>
#include "Student.h"
#include "Request.h"
#include "Dataset.h"

#define CLASS_CAP 30

bool Request::handleRequest() {
    switch (this->option)
    {
    case ADD:
        if(this->type == UC) addUc(this->collegeClass);
        else addClass(this->collegeClass);
        break;
    case REMOVE:
        if(this->type == UC) removeUc(this->collegeClass);
        else removeClass(this->collegeClass);
        break;
    case SWITCH:
        if(this->type == UC) switchUc(this->collegeClass,this->newCollegeClass);
        else switchClass(this->collegeClass,this->newCollegeClass);
        break;
    default:
        return false;
    }
    return true;
}

bool Request::addClass(CollegeClass classToAdd) {
    DataSet dataset; // THIS IS DUMB
    list<Lesson> classLessons = dataset.getScheduleByClass(classToAdd).get_scheduleLessons();
    int numStudents = dataset.consultClassOccupation(classToAdd);
    if(!isConflictingClass && maintainsClassBalance() && numStudents < CLASS_CAP) {
        this->student.set_studentSchedule(classLessons);
        return true;
    }
    return false;
}

bool Request::removeClass(CollegeClass classToRemove) {
    DataSet dataset;  // THIS IS DUMB
    list<Lesson> studentLessons = this->student.get_studentSchedule().get_scheduleLessons();
    if(maintainsClassBalance()){
        for(auto lessonIt = studentLessons.begin(); lessonIt != studentLessons.end();lessonIt++) {
            if(lessonIt->get_LessonClass().get_classCode() == classToRemove.get_classCode()){ // HAS TO BE CHANGED
                studentLessons.erase(lessonIt);
            }
        }
        return true;
    }
    return false;
}

bool Request::switchClass(CollegeClass classToRemove, CollegeClass classToAdd) {
    // DOESN'T HAVE CASES THAT DO NOT WORK???
    bool checkRemove = removeClass(classToRemove);
    bool checkAdd = addClass(classToAdd);
    return checkRemove && checkAdd;
}

bool Request::maintainsClassBalance() {
    DataSet dataset; // THIS IS DUMB
    vector<int> numStudentsClasses; //TODO: GET ACCESS TO ALL CLASSES
    int numStudents = dataset.getStudentsByClass(this->collegeClass).size();
    numStudents = this->option == ADD ? numStudents + 1 : numStudents - 1; // PLUS OR MINUS THE STUDENT
    for(int i = 0; i < numStudentsClasses.size();i++) {
        if(abs(numStudentsClasses[i]-numStudents) < 4) {
            return false;
        }
    }
    return true;
}

bool Request::isConflictingClass() {
    DataSet dataset; // THIS IS DUMB
    list<Lesson> studentLessons = this->student.get_studentSchedule().get_scheduleLessons();
    list<Lesson> classLessons = dataset.getScheduleByClass(this->collegeClass).get_scheduleLessons();
    for(Lesson classLesson: classLessons){
        if(isConflictingLesson(studentLessons,classLesson)){
            return true;
        }
    }
    return false;
}

// TO BE CHANGED
bool Request::isConflictingLesson(list<Lesson> studentLessons, Lesson lessonToCompare) {
    for(Lesson studentLesson : studentLessons){
        double studentStartTime = studentLesson.get_LessonStartHour();
        double studentFinishTime = studentStartTime + studentLesson.get_LessonDuration();
        double lessonToCompareStartTime = lessonToCompare.get_LessonStartHour(); 
        double lessonToCompareFinishTime = lessonToCompareStartTime + lessonToCompare.get_LessonDuration();

        bool hasSameWeekDay = lessonToCompare.get_LessonWeekday() == studentLesson.get_LessonWeekday();
        bool hasConflictTime =  (lessonToCompareStartTime > studentStartTime && lessonToCompareStartTime < studentFinishTime) 
                            || (lessonToCompareFinishTime > studentStartTime && lessonToCompareFinishTime < studentFinishTime)
                            || (lessonToCompareStartTime < studentStartTime && lessonToCompareFinishTime > studentFinishTime);
        bool alreadyOnUc = lessonToCompare.get_LessonUc().get_ucCode() == studentLesson.get_LessonUc().get_ucCode();
        if (hasConflictTime || hasSameWeekDay || alreadyOnUc)
            return true;
    }
    return false;
}

// TODO
bool Request::addUc(CollegeClass ucToAdd) {
    int enrolledUcs; //TODO: GET STUDENT NUM UC
    list<Lesson> currentUcLessons; //TODO: LESSONS OF A GIVEN UC
    bool hasVacancy = getVacancies(currentUcLessons).size() > 0;
    // TODO: GET USERS CHOICE OF THE LESSONS TO ADD
    list<Lesson> lessonsToAdd; // = getClassChoice(vacancies);
    if(enrolledUcs <= 7 && hasVacancy){
        list<Lesson> studentCurrentLessons = this->student.get_studentSchedule().get_scheduleLessons();
        for(Lesson lesson : lessonsToAdd)
            studentCurrentLessons.push_back(lesson);
        this->student.set_studentSchedule(Schedule(studentCurrentLessons));
    }
    return false;
}

// TODO
bool Request::removeUc(CollegeClass ucToRemove){

}

bool Request::switchUc(CollegeClass ucToRemove,CollegeClass ucToAdd) {
    // DOESN'T HAVE CASES THAT DO NOT WORK???
    bool checkRemove = removeUc(ucToRemove);
    bool checkAdd = addUc(ucToAdd);
    return checkRemove && checkAdd;
}

list<Lesson> Request::getVacancies(list<Lesson> currentUcLessons) {
    DataSet dataset; // THIS IS DUMB
    list<Lesson> vacancies;
    for(Lesson lesson : currentUcLessons){
        int numStudents = dataset.consultClassOccupation(lesson.get_LessonClass());
        list<Lesson> studentLessons = this->student.get_studentSchedule().get_scheduleLessons();
        if(numStudents < CLASS_CAP && !isConflictingLesson(studentLessons,lesson)){
            vacancies.push_back(lesson);
        }
    }
    return vacancies;
}