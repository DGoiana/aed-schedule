#include "menuFunctions.h"
#include <iostream>

Schedule getScheduleByStudent(string studentCode, DataSet &dataset){
    Schedule schedule;
    for(Student s : dataset.get_students()){
        if(s.get_studentCode() == studentCode){
            for(CollegeClass c : s.get_studentClasses()){
                schedule.addLessonsFromList(c.get_collegeClassSchedule().get_scheduleLessons());
            }
        };
    }
    return schedule;
}

Schedule getScheduleByClass(string classCode, DataSet &dataset){
    Schedule schedule;
    for(CollegeClass c : dataset.get_collegeClasses()){
        if(c.get_classCode() == classCode){
            schedule.addLessonsFromList(c.get_collegeClassSchedule().get_scheduleLessons());
        }
    }
    return schedule;
}

vector<Student> getStudentsByClassOrUc(string code, string id, DataSet &dataset){
    set<Student> students;
    for(CollegeClass c : dataset.get_collegeClasses()){
        if(c.get_classCode() == code && id == "class"){
            for(Student s : c.get_registeredStudents()){
                students.insert(s);
            }
        }
        if(c.get_ucCode() == code && id == "uc"){
            for(Student s : c.get_registeredStudents()){
                students.insert(s);
            }
        }
    }
    return vector<Student>(students.begin(), students.end());
}

vector<string> getClasses(DataSet &dataset){
    vector<string> classes;
    for(CollegeClass c : dataset.get_collegeClasses()){
        if(find(classes.begin(), classes.end(), c.get_classCode()) != classes.end()) continue;
        classes.push_back(c.get_classCode());
    }
    return classes;
}

vector<string> getUcs(DataSet &dataset){
    vector<string> ucs;
    for(CollegeClass c : dataset.get_collegeClasses()){
        if(find(ucs.begin(), ucs.end(), c.get_ucCode()) != ucs.end()) continue;
        ucs.push_back(c.get_ucCode());
    }
    return ucs;
}

int getNumStudentsInClassAndUc(CollegeClass ucClass, DataSet &dataset){
    for(CollegeClass c : dataset.get_collegeClasses()){
        if(c == ucClass) return c.get_registeredStudents().size();
    }
    return 0;
}

vector<Student> getStudentsByYear(string year, DataSet &dataset){
    set<Student> students;
    for(Student s : dataset.get_students()){
        if(s.get_studentCode().substr(0,4) == year) students.insert(s);
    }
    vector<Student> result(students.begin(), students.end());
    return result;
}

int numStudentsRegisteredInNUcs(int num, DataSet &dataset){
    int count = 0;
    for(Student s : dataset.get_students()){
        if(s.get_studentClasses().size() >= num) count++;
    }
    return count;
}

int consultClassorUcOccupation(string code, string id, DataSet &dataset){
    return getStudentsByClassOrUc(code, id, dataset).size();
}

int consultYearOccupation(string year, DataSet &dataset){
    return getStudentsByYear(year, dataset).size();
}

void sortStudentsByNameOrYear(vector<Student> &students, string order, string input){
    if(input == "name"){
        if(order == "ascending") sort(students.begin(), students.end(), [](Student s1, Student s2){
            return s1.get_studentName() < s2.get_studentName();
        });
        else sort(students.begin(), students.end(), [](Student s1, Student s2){
            return s1.get_studentName() > s2.get_studentName();
        });
    }
    else{
        if(order == "ascending") sort(students.begin(), students.end(), [](Student s1, Student s2){
            return s1.get_studentCode() < s2.get_studentCode();
        });
        else sort(students.begin(), students.end(), [](Student s1, Student s2){
            return s1.get_studentCode() > s2.get_studentCode();
        });
    }
}

void sortClassesByOccupation(vector<string> &codes, string order, DataSet &dataset){
    if(order == "ascending") sort(codes.begin(), codes.end(), [&dataset](string code1, string code2){
        return consultClassorUcOccupation(code1, "class", dataset) < consultClassorUcOccupation(code2, "class", dataset);
    });
    else sort(codes.begin(), codes.end(), [&dataset](string code1, string code2){
        return consultClassorUcOccupation(code1, "class", dataset) > consultClassorUcOccupation(code2, "class", dataset);
    });
}

void sortUcsByOccupation(vector<string> &codes, string order, DataSet &dataset){
    if(order == "ascending") sort(codes.begin(), codes.end(), [&dataset](string code1, string code2){
        return consultClassorUcOccupation(code1, "uc", dataset) < consultClassorUcOccupation(code2, "uc", dataset);
    });
    else sort(codes.begin(), codes.end(), [&dataset](string code1, string code2){
        return consultClassorUcOccupation(code1, "uc", dataset) > consultClassorUcOccupation(code2, "uc", dataset);
    });
}

void sortYearsByOccupation(vector<string> &years, string order, DataSet &dataset){
    if(order == "ascending") sort(years.begin(), years.end(), [&dataset](string year1, string year2){
        return consultYearOccupation(year1, dataset) < consultYearOccupation(year2, dataset);
    });
    else sort(years.begin(), years.end(), [&dataset](string year1, string year2){
        return consultYearOccupation(year1, dataset) > consultYearOccupation(year2, dataset);
    });
}

string getMostStudentsUC(DataSet &dataset){
    string result;
    int num = 0;
    for(string uc: getUcs(dataset)){
        if(consultClassorUcOccupation(uc, "uc", dataset) > num){
            result = uc;
            num = consultClassorUcOccupation(uc, "uc", dataset);
        }
    }
    return result;
}

void setStudentClasses(vector<CollegeClass> newClasses, string studentCode, DataSet &dataset) {
    auto it = find(dataset.get_students().begin(), dataset.get_students().end(), Student(studentCode, "", {}));
    it->set_studentClasses(newClasses);
}

void addStudentClass(CollegeClass c, string studentCode, DataSet &dataset){
   auto it = find(dataset.get_students().begin(), dataset.get_students().end(), Student(studentCode, "", {}));
   it->add_studentClass(c);
}

// Student getStudentByNumber(string studentCode, DataSet &dataset){
//     for(Student s : dataset.get_students()){
//         if(s.get_studentCode() == studentCode) return s;
//     }
// }

list<Student> getStudentByName(string studentName, DataSet &dataset)
{
    list<Student> sameNameStudents;
    for(Student student : dataset.get_students()){
        if(student.get_studentName() == studentName)
            sameNameStudents.push_back(student);
    }
    return sameNameStudents;
}