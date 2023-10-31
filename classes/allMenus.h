#ifndef AED_SCHEDULE_ALLMENUS_H
#define AED_SCHEDULE_ALLMENUS_H

#include "Schedule.h"
#include "Dataset.h"
#include "Lesson.h"
#include "CollegeClass.h"
#include <string>
#include <vector>

class AllMenus{
    public:
        AllMenus();
        vector<string> showSortOptions();
        void menu_principal();
        void menu_schedule();
        void menu_students();
        void menu_uc();
        void menu_occupations();
        void menu_requests();
        void draw_rectangle(int width, int height, const std::vector<std::string>& text);
};

#endif 