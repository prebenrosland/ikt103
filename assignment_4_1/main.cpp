#include <iostream>

#include <sqlite3.h>
#include <SQLiteCpp/SQLiteCpp.h>

SQLite::Database database("school.sqlite", SQLite::OPEN_READWRITE);

void Read_students()
{
    int counter = 0;
    SQLite::Statement query(database, "SELECT * FROM students");
    while (query.tryExecuteStep() == SQLITE_ROW)
    {
        std::cout << "id: " << query.getColumn("id") << ", name: " << query.getColumn("name") << ", email: " << query.getColumn("email") << ", year: " << query.getColumn("year") << std::endl;
        counter++;
    }
    if (counter == 0)
    {
        std::cout << "No students found" << std::endl;
    }
}

void Get_student()
{
    int student_id;
    int counter = 0;
    std::cin >> student_id;
    SQLite::Statement query(database, "SELECT * FROM students WHERE id = ?");
    query.bind(1, student_id);
    while (query.tryExecuteStep() == SQLITE_ROW)
    {
        std::cout << "id: " << query.getColumn("id") << ", name: " << query.getColumn("name") << ", email: " << query.getColumn("email") << ", year: " << query.getColumn("year") << std::endl;
        counter++;
    }
    if (counter == 0)
    {
        std::cout << "Student not found" << std::endl;
    }
}

void Add_student()
{
    std::string name;
    std::string email;
    int year;
    getchar();
    std::getline(std::cin, name);
    std::cin >> email;
    std::cin >> year;
    SQLite::Statement query(database, "INSERT INTO students (name, email, year) VALUES (?, ?, ?)");
    query.bind(1, name);
    query.bind(2, email);
    query.bind(3, year);
    query.exec();

    SQLite::Statement query2(database, "SELECT * FROM students WHERE name=? AND email=? AND year=?");
    query2.bind(1, name);
    query2.bind(2, email);
    query2.bind(3, year);

    while (query2.tryExecuteStep() == SQLITE_ROW)
    {
        std::cout << "Added student: "<< "id: " << query2.getColumn("id") << ", name: " << query2.getColumn("name") << ", email: " << query2.getColumn("email") << ", year: " << query2.getColumn("year") << std::endl;
    }

}

void Edit_student()
{
    SQLite::Statement query1(database, "SELECT * FROM students");
    if (query1.tryExecuteStep() == SQLITE_ROW){
        int counter = 0;
        int id;
        std::string name;
        std::string email;
        int year;
        std::cin >> id;
        getchar();
        std::getline(std::cin, name);
        std::cin >> email;
        std::cin >> year;
        SQLite::Statement query(database, "UPDATE students SET name=?, email=?, year=?");
        query.bind(1, name);
        query.bind(2, email);
        query.bind(3, year);
        query.exec();
        SQLite::Statement query2(database, "SELECT * FROM students WHERE id=?");
        query2.bind(1, id);
        std::cout << "Student was edited successfully" << std::endl;

    }
    else{
        std::cout << "Student not found" << std::endl;
    }






}

void Remove_student()
{
    int student_id;
    std::cin >> student_id;
    SQLite::Statement query(database, "DELETE FROM students WHERE id=?");
    query.bind(1, student_id);
    int count = query.exec();
    if(count > 0)
    {
        std::cout << "Student was removed successfully" << std::endl;
    } else
    {
        std::cout << "Student not found" << std::endl;
    }

}

void Search()
{
    std::string student_name;
    getchar();
    std::getline(std::cin, student_name);
    SQLite::Statement query(database, "SELECT * FROM students WHERE name LIKE ?");
    query.bind(1, student_name);
    while (query.tryExecuteStep() == SQLITE_ROW)
    {
        std::cout << "id: " << query.getColumn("id") << ", name: " << query.getColumn("name") << ", email: " << query.getColumn("email") << ", year: " << query.getColumn("year") << std::endl;
    }
}

int menu()
{
    int option;
    std::cout << "Chose an option: " << std::endl;
    std::cin >> option;
    switch (option) {
        case 1:
            Read_students();
            menu();
            break;
        case 2:
            Get_student();
            menu();
            break;
        case 3:
            Add_student();
            menu();
            break;
        case 4:
            Edit_student();
            menu();
            break;
        case 5:
            Remove_student();
            break;
        case 6:
            Search();
            break;
        case 7:
            return 1;
    }
}

int main() {

    menu();
    return 0;
}
