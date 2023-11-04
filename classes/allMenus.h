#ifndef AED_SCHEDULE_ALLMENUS_H
#define AED_SCHEDULE_ALLMENUS_H

#include "Schedule.h"
#include "Dataset.h"
#include "Lesson.h"
#include "CollegeClass.h"
#include <string>
#include <vector>

class AllMenus{
    private:
        DataSet dataset;
    public:
        AllMenus(DataSet &dataset, list<vector<string>> classesPerUc);
        void sortStudentVector(vector<Student>& students);
        void menu_principal(list<vector<string>> classesPerUc);
        void menu_schedule();
        void menu_students();
        void menu_uc();
        void menu_occupations();
        void menu_requests(list<vector<string>> classesPerUc);
        void addClassFunction(list<vector<string>> classesPerUc);
        void removeClassFunction(list<vector<string>> classesPerUc);
        void switchClassFunction(list<vector<string>> classesPerUc);
        void addUcFunction(list<vector<string>> classesPerUc);
        void removeUcFunction(list<vector<string>> classesPerUc);
        void switchUcFunction(list<vector<string>> classesPerUc);

        void showSchedule(vector<Lesson> lessons);
        void showPages(vector<Student> students);
        string sortOption();
        string toTime(float number);
};

#endif 