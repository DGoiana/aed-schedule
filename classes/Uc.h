#include <string>
#include <list>

using namespace std;

class Uc{
    private:
        string ucCode;
         // if parsing through all students classes takes too long, create a list of students
    public:
        Uc();
        Uc(string ucCode);
        string get_ucCode() const;
        void set_ucCode(const string& new_ucCode);
};