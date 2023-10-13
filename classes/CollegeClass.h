#include <list>
#include <string>

using namespace std;

class CollegeClass {
    private:
        string classCode;
        // if parsing through all students classes takes too long, create a list of students
    public:
        CollegeClass();
        CollegeClass(string classCode);
        string get_classCode() const;
        void set_classCode(const string& new_classCode);
};