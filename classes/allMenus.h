#ifndef AED_SCHEDULE_ALLMENUS_H
#define AED_SCHEDULE_ALLMENUS_H

#include "Schedule.h"
#include "Dataset.h"
#include "Lesson.h"
#include "Request.h"
#include "CollegeClass.h"
#include <string>
#include <stack>
#include <vector>

class AllMenus{
    private:
        DataSet dataset;
        stack<Request> globalRequests;
        stack<list<string>> previousRemoves;
    public:
        AllMenus(DataSet &dataset);
        void sortStudentVector(vector<Student>& students);
        void seeGlobalRequestsTop();
        void menu_principal();
        void menu_schedule();
        void menu_students();
        void menu_uc();
        void menu_occupations();
        void menu_requests();
        void menu_save_state();
        void undoRequest(DataSet& dataset);
        void addClassFunction(DataSet& dataset);
        void removeClassFunction(DataSet& dataset);
        void switchClassFunction(DataSet& dataset);
        void addUcFunction(DataSet& dataset);
        void removeUcFunction(DataSet& dataset);
        void switchUcFunction(DataSet& dataset);

        void showSchedule(list<Lesson> lessons);
        void showPages(vector<Student> students);
        string sortOption();
        string toTime(float number);

        bool check_classCode(string classCode);
        bool check_ucCode(string ucCode);
        bool check_studentCode(string studentCode);
        bool check_year(string year);
};

#endif 