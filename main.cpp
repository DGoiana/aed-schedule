#include <stdlib.h>
#include "classes/allMenus.h"
#include "classes/Parser.h"
#include "classes/Dataset.h"
#include "classes/Request.h"
#include <iostream>

using namespace std;

void testAddClassFunction(DataSet& dataset) {
    Parser parser;
    string classToAdd;
    cout << "Class to Add: "; 
    cin >> classToAdd;
    CollegeClass classUcExample = CollegeClass(classToAdd,"*");
    Student testStudent = dataset.getStudentByNumber("202025232");
    Request firstRequest = Request(classUcExample,testStudent,CLASS,ADD,dataset);
    //int numStudentsClass = dataset.maxStudentUcInClass(classToAdd);
    //cout << firstRequest.maintainsClassBalance(classToAdd,numStudentsClass) << '\n';
    if(firstRequest.handleRequest()){
        parser.printLessons(dataset.getStudentByNumber("202025232").get_studentSchedule().get_scheduleLessons());
        return;
    }
    cout << "failed" << '\n';
}

void testRemoveClassFunction(DataSet& dataset) {
    Parser parser;
    string classToRemove = "2LEIC15";
    CollegeClass classUcExample = CollegeClass(classToRemove,"*");
    Student testStudent = dataset.getStudentByNumber("202024637");
    Request secondRequest = Request(classUcExample,testStudent,CLASS,REMOVE,dataset);
    parser.printLessons(testStudent.get_studentSchedule().get_scheduleLessons());
    if(secondRequest.handleRequest());
    cout << "REMOVED, RESULT: " << '\n';
    //parser.printLessons(testStudent.get_studentSchedule().get_scheduleLessons());
    parser.printLessons(dataset.getStudentByNumber("202024637").get_studentSchedule().get_scheduleLessons());
}

void testSwitchClassFunction(DataSet& dataset) {
    Parser parser;
    string classToRemove = "2LEIC15";
    string classToAdd = "2LEIC05";
    CollegeClass classUcRemoveExample = CollegeClass(classToRemove,"*");
    CollegeClass classUcAddExample = CollegeClass(classToAdd,"*");
    Student testStudent = dataset.getStudentByNumber("202054727");
    Request removeRequest = Request(classUcRemoveExample,testStudent,CLASS,REMOVE,dataset);
    Request addRequest = Request(classUcAddExample,testStudent,CLASS,ADD,dataset);
    parser.printLessons(dataset.getStudentByNumber("202054727").get_studentSchedule().get_scheduleLessons());
    if(removeRequest.handleRequest()){
        parser.printLessons(dataset.getStudentByNumber("202054727").get_studentSchedule().get_scheduleLessons());
    }
    if(addRequest.handleRequest()){
        parser.printLessons(dataset.getStudentByNumber("202054727").get_studentSchedule().get_scheduleLessons());
    }
    return;
}


int main(){
    DataSet dataset;
    //testAddClassFunction(dataset);
    //testRemoveClassFunction(dataset);
    testSwitchClassFunction(dataset);
    //AllMenus();
    /*    
    DataSet dataset;
    map<string,list<string>> test = Parser::getUcsByClasses();
    for(auto i : test) {
        int eachClass = 0;
        cout << i.first << '\n';
        for(string s : i.second){
            int ucClassStudents =  dataset.getNumStudentsInClassAndUc(CollegeClass(i.first,s));
            cout << s << " " << ucClassStudents << '\n';
            eachClass += ucClassStudents;
            //for(Student student : ucClassStudents) cout << "    " << student.get_studentName() << " " << student.get_studentCode() << '\n';
        } 
        cout << "Total number of students in this class: " << eachClass << '\n';
    }

    Parser parser;
    DataSet dataset;
    string classToAdd = "2LEIC09";
    string UcToAdd = "L.EIC011";
    string classToRemove = "1LEIC08";
    string UcToRemove = "L.EIC004";
    string studentCode = "202031607";
    Student testStudent = dataset.getStudentByNumber(studentCode);

    CollegeClass class1 = CollegeClass(classToAdd,UcToAdd);
    CollegeClass class2 = CollegeClass(classToRemove,UcToRemove); 
    Request switchRequest = Request(class1,class2,testStudent,UC,REMOVE,dataset);

    parser.printLessons(dataset.getScheduleByStudent(studentCode).get_scheduleLessons());
    switchRequest.switchUc(dataset,class2,class1);
    cout << '\n';
    parser.printLessons(dataset.getScheduleByStudent(studentCode).get_scheduleLessons());

    */
    /*
    Request secondRequest = Request(classUcExample,testStudent,UC,ADD);
    parser.printLessons(dataset.getScheduleByStudent("202025232").get_scheduleLessons());
    secondRequest.addUc(dataset,classUcExample);
    parser.printLessons(dataset.getScheduleByStudent("202025232").get_scheduleLessons());
    
    
    cout << '\n';
    parser.printLessons(dataset.getScheduleByStudent("202025232").get_scheduleLessons());  
    string ucToRemove = "L.EIC002";   
    CollegeClass classUcExample2 = CollegeClass(classToAdd,ucToRemove);
    Request thirdRequest = Request(classUcExample2,testStudent,UC,REMOVE);
    thirdRequest.removeUc(dataset,classUcExample2);
    cout << '\n';
    parser.printLessons(dataset.getScheduleByStudent("202025232").get_scheduleLessons());
    
    Parser parser;
    DataSet dataset;
    string classToAdd = "2LEIC05";

    map<string,list<string>> ucsByClasses = Parser::getUcsByClasses();
    list<string> ucsByClass = ucsByClasses[classToAdd];
    int max = 0;
    for(string uc : ucsByClass) {
        int ucClassStudents =  dataset.getNumStudentsInClassAndUc(CollegeClass(classToAdd,uc));
        cout << uc << " " << ucClassStudents << '\n';
        if(ucClassStudents > max) max = ucClassStudents;
    }
    cout << max << '\n';
    return 0;
    */
}
