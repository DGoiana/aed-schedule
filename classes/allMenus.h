#ifndef AED_SCHEDULE_ALLMENUS_H
#define AED_SCHEDULE_ALLMENUS_H

#include "Schedule.h"
#include "Dataset.h"
#include "Lesson.h"
#include "Request.h"
#include "CollegeClass.h"
#include <string>
#include <vector>
#include <stack>
/**
 * This class is responsible for all display functions, interaction with the user and making requests.
 */
class AllMenus{
    private:
        DataSet dataset;
        stack<Request> globalRequests;
    public:
        AllMenus(DataSet &dataset, list<vector<string>> classesPerUc);
        void sortStudentVector(vector<Student>& students);
        void seeGlobalRequestsTop();
        void menu_principal(list<vector<string>> classesPerUc);
        void menu_schedule();
        void menu_students();
        void menu_uc();
        void menu_occupations();
        void menu_requests(list<vector<string>> classesPerUc);
        void menu_save_state();
        void undoRequest(list<vector<string>> classesPerUc);
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

        bool check_classCode(string classCode);
        bool check_ucCode(string ucCode);
        bool check_studentCode(string studentCode);
        bool check_year(string year);
        bool check_ucInStudent(string studentCode, string code);
        bool check_classInStudent(string studentCode, string code);
};

#endif 