#ifndef AED_SCHEDULE_MENUFUNCTIONS_H
#define AED_SCHEDULE_MENUFUNCTIONS_H

#include "Schedule.h"
#include "Dataset.h"


Schedule getScheduleByStudent(string studentCode, DataSet &dataset);

Schedule getScheduleByClass(string classCode, DataSet &dataset);

vector<Student> getStudentsByClassOrUc(string code, string id, DataSet &dataset);

vector<string> getClasses(DataSet &dataset);

vector<string> getUcs(DataSet &dataset);

int getNumStudentsInClassAndUc(CollegeClass ucClass, DataSet &dataset);

vector<Student> getStudentsByYear(string year, DataSet &dataset);

int numStudentsRegisteredInNUcs(int num, DataSet &dataset);

int consultClassorUcOccupation(string code, string id, DataSet &dataset);

int consultYearOccupation(string year, DataSet &dataset);

void sortStudentsByNameOrYear(vector<Student> &students, string order, string input);

void sortClassesByOccupation(vector<string> &codes, string order, DataSet &dataset);

void sortUcsByOccupation(vector<string> &codes, string order, DataSet &dataset);

void sortYearsByOccupation(vector<string> &years, string order, DataSet &dataset);

string getMostStudentsUC(DataSet &dataset);

void setStudentClasses(vector<CollegeClass> newClasses, Student& student);

void addStudentClass(CollegeClass c, Student& student);

Student& getStudentByNumber(string studentCode, DataSet &dataset);

list<Student> getStudentByName(string studentName, DataSet &dataset);

CollegeClass& getCollegeClassByCodes(string classCode, string ucCode, DataSet &dataset);

void removeStudentFromCollegeClass(Student studentToErase, DataSet &dataset, CollegeClass collegeClassToErase);
void addStudentInCollegeClass(Student studentToAdd, DataSet &dataset, CollegeClass collegeClassToAdd);

#endif