#include <iostream>
#include <vector>

class Test {
public:
    int id;
    std::string course_name;
    std::string test_name;
    std::string time;
};

class Student {
public:
    int id;
    std::string name;
    std::string email;
    std::vector<Test> test_list;
};

class TestResult {
public:
    int student_id;
    int test_id;
    int grade;
};

std::vector<Student>student_list;
std::vector<Test>test_list;
std::vector<TestResult>result_list;
int student_counter = 1;
int test_counter = 1;

void menu();

void add_student(){
    Student student;
    int temp;
    student.id = student_counter;
    student_counter++;
    getchar();
    getline(std::cin, student.name);
    //getchar();
    getline(std::cin, student.email);
    //getchar();
    std::cout << student.email;
    student_list.push_back(student);
    menu();
}

void add_test(){
    Test test;
    test.id = test_counter;
    test_counter++;
    getchar();
    getline(std::cin, test.course_name);
    //getchar();
    getline(std::cin, test.test_name);
    //getchar();
    getline(std::cin, test.time);
    //std::cin >> test.course_name;
    //std::cin >> test.test_name;
    //std::cin >> test.time;
    test_list.push_back(test);
    menu();
}

void add_test_result(){
    TestResult result;
    getchar();
    std::cin >> result.student_id;
    std::cin >> result.test_id;
    std::cin >> result.grade;
    result_list.push_back(result);
    menu();

}

void edit_student(){
    int student_edit;
    int vector_index;

    std::cout << "Students:" << std::endl;
    for (int i = 0; i < student_list.size(); ++i) {
        std::cout << student_list[i].id << ". " << student_list[i].name << std::endl;
    }
    std::cout << std::endl;
    std::cin >> student_edit;
    for (int i = 0; i < student_list.size(); ++i) {
        if (student_list[i].id == student_edit){
            vector_index = i;
        }
    }
    getchar();
    getline(std::cin, student_list[vector_index].name);
    //getchar();
    getline(std::cin, student_list[vector_index].email);
    //std::cin >> student_list[vector_index].name;
    //std::cin >> student_list[vector_index].email;
    menu();
}

void edit_test(){
    int test_edit;
    int vector_index;

    std::cout << "Tests:" << std::endl;
    for (int i = 0; i < test_list.size(); ++i) {
        std::cout << test_list[i].id << ". " << test_list[i].course_name << ", " << test_list[i].test_name << std::endl;
    }
    std::cout << std::endl;
    std::cin >> test_edit;
    for (int i = 0; i < test_list.size(); ++i) {
        if (test_list[i].id == test_edit){
            vector_index = i;
        }
    }
    getchar();
    getline(std::cin, test_list[vector_index].course_name);
    //getchar();
    getline(std::cin, test_list[vector_index].test_name);
    //getchar();
    getline(std::cin, test_list[vector_index].time);
    //std::cin >> test_list[vector_index].course_name;
    //std::cin >> test_list[vector_index].test_name;
    //std::cin >> test_list[vector_index].time;
    menu();
}

void edit_test_result(){
    int result_edit_student;
    int result_edit_test;
    int vector_index;
    int student_checker = 0;
    int test_checker = 0;

    std::cout << "Results:" << std::endl;
    for (int i = 0; i < result_list.size(); ++i) {
        std::cout << "Student id: " << result_list[i].student_id << ", Test id: " << result_list[i].test_id << ", Grade: " << result_list[i].grade << std::endl;
    }
    std::cout << std::endl;

    std::cin >> result_edit_student;
    for (int i = 0; i < result_list.size(); ++i) {
        if (result_list[i].student_id > student_checker){
            student_checker = result_list[i].student_id;
            //menu();
        }
    }
    if (result_edit_student > student_checker){
        menu();
    }
    std::cin >> result_edit_test;
    for (int i = 0; i < result_list.size(); ++i) {
        if (result_list[i].test_id > test_checker){
            test_checker = result_list[i].test_id;
            //menu();
        }
    }
    if (result_edit_test > test_checker){
        menu();
    }



    for (int i = 0; i < result_list.size(); ++i) {
        if (result_list[i].student_id == result_edit_student && result_list[i].test_id == result_edit_test){
            vector_index = i;
        }
    }
    std::cin >> result_list[vector_index].grade;
    menu();
}

void delete_student(){
    int student_delete;
    int vector_index;

    std::cout << "Students:" << std::endl;
    for (int i = 0; i < student_list.size(); ++i) {
        std::cout << student_list[i].id << ". " << student_list[i].name << std::endl;
    }
    std::cout << std::endl;
    std::cin >> student_delete;
    for (int i = 0; i < student_list.size(); ++i) {
        if (student_list[i].id == student_delete){
            vector_index = i;
        }
    }
    student_list.erase(student_list.begin()+vector_index);
    for (int i = 0; i < result_list.size(); ++i) {
        if (result_list[i].student_id == student_delete){
            result_list.erase(result_list.begin()+i);
        }
    }
    menu();
}

void delete_test(){
    int test_delete;
    int vector_index;

    std::cout << "Tests:" << std::endl;
    for (int i = 0; i < test_list.size(); ++i) {
        std::cout << test_list[i].id << ". " << test_list[i].course_name << ", " << test_list[i].test_name << std::endl;
    }
    std::cin >> test_delete;
    for (int i = 0; i < test_list.size(); ++i) {
        if (test_list[i].id == test_delete){
            vector_index = i;
        }
    }
    test_list.erase(test_list.begin()+vector_index);
    for (int i = 0; i < result_list.size(); ++i) {
        if (result_list[i].test_id == test_delete){
            result_list.erase(result_list.begin()+i);
        }
    }
    menu();
}

void delete_test_result(){
    int result_delete_student;
    int result_delete_test;
    int vector_index;

    std::cout << "Results:" << std::endl;
    for (int i = 0; i < result_list.size(); ++i) {
        std::cout << "Student id: " << result_list[i].student_id << ", Test id: " << result_list[i].test_id << ", Grade" << result_list[i].grade << std::endl;
    }
    std::cout << std::endl;
    std::cin >> result_delete_student;
    std::cin >> result_delete_test;

    for (int i = 0; i < result_list.size(); ++i) {
        if (result_list[i].student_id == result_delete_student && result_list[i].test_id == result_delete_test){
            vector_index = i;
        }
    }
    result_list.erase(result_list.begin()+vector_index);
    menu();
}

void print_info(){
    for (int i = 0; i < test_list.size(); ++i) {
        std::cout << "test id = " << test_list[i].id << ", course name = " << test_list[i].course_name << ", test name = " << test_list[i].test_name << ", date = " << test_list[i].time << std::endl;
    }
    for (int i = 0; i < student_list.size(); ++i) {
        std::cout << "student id = " << student_list[i].id << ", name = " << student_list[i].name << ", email = " << student_list[i].email << std::endl;
    }
    for (int i = 0; i < result_list.size(); ++i) {
        std::string course_name;
        std::string test_name;
        for (int j = 0; j < test_list.size(); ++j) {
            if (result_list[i].test_id == test_list[j].id){
                course_name = test_list[j].course_name;
                test_name = test_list[j].test_name;
            }
        }
        std::cout << "student id = " << result_list[i].student_id << ", course name = " << course_name << ", test id = " << result_list[i].test_id << ", test name = " << test_name  << ", grade = " << result_list[i].grade << std::endl;
    }
    menu();
}

void exit_program(){
    exit(0);
}

void menu_change_mode(int menu_number){

    switch (menu_number) {
        case 1: add_student();
        case 2: edit_student();
        case 3: delete_student();
        case 4: add_test();
        case 5: edit_test();
        case 6: delete_test();
        case 7: add_test_result();
        case 8: edit_test_result();
        case 9: delete_test_result();
        case 10: print_info();
        case 11: exit_program();
    }
}

void menu(){
    int menu_number;
    std::cout << std::endl;
    std::cout << "Please choose:" << std::endl;
    std::cout << "1. Add student" << std::endl;
    std::cout << "2. Edit student" << std::endl;
    std::cout << "3. Remove student" << std::endl;
    std::cout << "4. Add test" << std::endl;
    std::cout << "5. Edit test" << std::endl;
    std::cout << "6. Remove test" << std::endl;
    std::cout << "7. Add test result" << std::endl;
    std::cout << "8. Edit test result" << std::endl;
    std::cout << "9. Remove test result" << std::endl;
    std::cout << "10. Show all info" << std::endl;
    std::cout << "11. Exit" << std::endl;

    std::cin >> menu_number;
    if (menu_number < 1 || menu_number > 11){
        std::cout << "Invalid number, try again" << std::endl;
        menu();
    }
    else{
        menu_change_mode(menu_number);
    }
}



int main() {
    menu();
    return 0;
}
