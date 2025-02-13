#include <iostream>
#include <fstream>
#include <vector>
#include <list>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/reader.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/filereadstream.h"

#include "student.h"

using namespace rapidjson;



int main() {

    FILE* file = fopen("students.json", "r");
    char read_buffer[65536];
    StringBuffer buffer;
    FileReadStream reader(file, read_buffer, sizeof(read_buffer));

    std::vector<Student*> student_list;
    std::list<Student*> stdli;


    Document document;
    document.ParseStream(reader);

    fclose(file);

    for (int i = 0; i < document.Size(); ++i) {
        Student* newStudent = new Student;
        newStudent->id = document[i]["id"].GetInt();
        newStudent->name = document[i]["name"].GetString();
        newStudent->age = document[i]["age"].GetInt();
        newStudent->attendance = document[i]["attendance"].GetInt();
        student_list.push_back(newStudent);
        std::cout << newStudent->id << std::endl;
    }

    int youngest;
    std::string youngest_name;
    for (int i = 0; i < student_list.size(); ++i) {
        if (i == 0)
        {
            youngest = student_list[i]->age;
            youngest_name = student_list[i]->name;
        }
        else if (student_list[i]->age < youngest)
        {
            youngest = student_list[i]->age;
            youngest_name = student_list[i]->name;
        }
    }
    std::cout << "Youngest: " << youngest_name << std::endl;

    int oldest;
    std::string oldest_name;
    for (int i = 0; i < student_list.size(); ++i) {
        if (i == 0)
        {
            oldest = student_list[i]->age;
            oldest_name = student_list[i]->name;
        }
        else if (student_list[i]->age > oldest)
        {
            oldest = student_list[i]->age;
            oldest_name = student_list[i]->name;
        }
    }
    std::cout << "Oldest: " << oldest_name << std::endl;

    float average_age;
    int total_age = 0;
    for (int i = 0; i < student_list.size(); ++i) {
        total_age += student_list[i]->age;
        average_age = total_age/(i+1);
    }
    std::cout << "Average age: " << average_age << std::endl;

    for (int i = 0; i < student_list.size(); ++i) {
        if (student_list[i]->attendance < 30)
        {
            std::cout << "Bad student: " << student_list[i]->name << std::endl;
        }
    }

    Student* newStudent();


    return 0;
}
