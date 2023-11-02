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
        AllMenus(DataSet &dataset);
        vector<string> showSortOptions(string id);
        void menu_principal();
        void menu_schedule();
        void menu_students();
        void menu_uc();
        void menu_occupations();
        void menu_requests();
        void draw_rectangle(int width, int height, const std::vector<std::string>& text);
        void testAddClassFunction(DataSet& dataset);
        void testRemoveClassFunction(DataSet& dataset);
        void testSwitchClassFunction(DataSet& dataset);
        void testAddUcFunction(DataSet& dataset);
        void testRemoveUcFunction(DataSet& dataset);
        void testSwitchUcFunction(DataSet& dataset);
};

#endif 