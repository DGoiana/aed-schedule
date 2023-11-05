#ifndef AED_SCHEDULE_MENUFUNCTIONS_H
#define AED_SCHEDULE_MENUFUNCTIONS_H

#include "Schedule.h"
#include "Dataset.h"
/**
 * The menu functions class processes almost all calls made by the menu.
 */
class MenuFunctions {
public:
    static Schedule getScheduleByStudent(string studentCode, DataSet &dataset);

    static Schedule getScheduleByClass(string classCode, DataSet &dataset);

    static vector<Student> getStudentsByClassOrUc(string code, string id, DataSet &dataset);

    static vector<string> getClasses(DataSet &dataset);

    static vector<string> getUcs(DataSet &dataset);

    static int getNumStudentsInClassAndUc(CollegeClass ucClass, DataSet &dataset);

    static vector<Student> getStudentsByYear(string year, DataSet &dataset);

    static int numStudentsRegisteredInNUcs(int num, DataSet &dataset);

    static int consultClassorUcOccupation(string code, string id, DataSet &dataset);

    static int consultYearOccupation(string year, DataSet &dataset);

    static void sortStudentsByNameOrYear(vector<Student> &students, string order, string input);

    static void sortClassesByOccupation(vector<string> &codes, string order, DataSet &dataset);

    static void sortUcsByOccupation(vector<string> &codes, string order, DataSet &dataset);

    static void sortYearsByOccupation(vector<string> &years, string order, DataSet &dataset);

    static string getMostStudentsUC(DataSet &dataset);

    static void setStudentClasses(vector<CollegeClass> newClasses, Student &student);

    static void addStudentClass(CollegeClass c, Student &student);

    static Student &getStudentByNumber(string studentCode, DataSet &dataset);

    static list<Student> getStudentByName(string studentName, DataSet &dataset);

    static CollegeClass &getCollegeClassByCodes(string classCode, string ucCode, DataSet &dataset);

    static void removeStudentFromCollegeClass(Student studentToErase, DataSet &dataset, CollegeClass collegeClassToErase);

    static void addStudentInCollegeClass(Student studentToAdd, DataSet &dataset, CollegeClass collegeClassToAdd);

};
#endif