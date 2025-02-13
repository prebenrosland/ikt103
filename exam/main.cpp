#include <iostream>
#include <fstream>
#include <sqlite3.h>
#include <SQLiteCpp/SQLiteCpp.h>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/reader.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"


void read_json(SQLite::Database &database){
    FILE* file = fopen("car_rental.json", "r");
    char read_buffer[65536];

    rapidjson::FileReadStream reader(file, read_buffer, sizeof(read_buffer));

    rapidjson::Document document;
    document.ParseStream(reader);

    fclose(file);

    for (int i = 0; i < document["cars"].Size(); ++i) {
        SQLite::Statement query(database, "INSERT INTO cars"
                                          "(reg_number, brand, model, year, completed_rentals) VALUES (?, ?, ?, ?, ?)");
        query.bind(1, document["cars"][i]["reg_number"].GetString());
        query.bind(2, document["cars"][i]["brand"].GetString());
        query.bind(3, document["cars"][i]["model"].GetString());
        query.bind(4, document["cars"][i]["year"].GetInt());
        query.bind(5, document["cars"][i]["completed_rentals"].GetInt());
        query.exec();
    }

    for (int i = 0; i < document["customers"].Size(); ++i) {
        SQLite::Statement query(database, "INSERT INTO customers"
                                          "(name, phone_number, address) VALUES (?, ?, ?)");
        query.bind(1, document["customers"][i]["name"].GetString());
        query.bind(2, document["customers"][i]["phone_number"].GetString());
        query.bind(3, document["customers"][i]["address"].GetString());
        query.exec();
    }
}

void write_json(SQLite::Database &database)
{
    rapidjson::Document document;
    document.SetObject();

    rapidjson::Value array_cars(rapidjson::kArrayType);
    rapidjson::Value array_customers(rapidjson::kArrayType);

    FILE* file = fopen("car_rental.json","wb");
    char writeBuffer[65536];

    SQLite::Statement query(database, "SELECT * FROM cars");

    while (query.tryExecuteStep() == SQLITE_ROW) {
        rapidjson::Value val(rapidjson::kObjectType);
        rapidjson::Value attribute_reg_number(rapidjson::kStringType);
        rapidjson::Value attribute_brand(rapidjson::kStringType);
        rapidjson::Value attribute_model(rapidjson::kStringType);
        rapidjson::Value attribute_year(rapidjson::kNumberType);
        rapidjson::Value attribute_renter_id(rapidjson::kNumberType);
        rapidjson::Value attribute_completed_rentals(rapidjson::kNumberType);

        std::string text = query.getColumn("reg_number").getText();
        attribute_reg_number.SetString(text.c_str(), document.GetAllocator());

        text = query.getColumn("brand").getText();
        attribute_brand.SetString(text.c_str(), document.GetAllocator());

        text = query.getColumn("model").getText();
        attribute_model.SetString(text.c_str(), document.GetAllocator());

        int num = query.getColumn("year").getInt();
        attribute_year.SetInt(num);

        num = query.getColumn("current_renter_id").getInt();
        attribute_renter_id.SetInt(num);

        num = query.getColumn("completed_rentals").getInt();
        attribute_completed_rentals.SetInt(num);


        val.AddMember("reg_number", attribute_reg_number, document.GetAllocator());
        val.AddMember("brand", attribute_brand, document.GetAllocator());
        val.AddMember("model", attribute_model, document.GetAllocator());
        val.AddMember("year", attribute_year, document.GetAllocator());
        val.AddMember("current_renter_id", attribute_renter_id, document.GetAllocator());
        val.AddMember("completed_rentals", attribute_completed_rentals, document.GetAllocator());
        array_cars.PushBack(val, document.GetAllocator());
    }


    document.AddMember("cars", array_cars, document.GetAllocator());

    SQLite::Statement query2(database, "SELECT * FROM customers");

    while (query2.tryExecuteStep() == SQLITE_ROW) {
        rapidjson::Value val(rapidjson::kObjectType);
        rapidjson::Value attribute_name(rapidjson::kStringType);
        rapidjson::Value attribute_phone_number(rapidjson::kStringType);
        rapidjson::Value attribute_address(rapidjson::kStringType);

        std::string text = query2.getColumn("name").getText();
        attribute_name.SetString(text.c_str(), document.GetAllocator());

        text = query2.getColumn("phone_number").getText();
        attribute_phone_number.SetString(text.c_str(), document.GetAllocator());

        text = query2.getColumn("address").getText();
        attribute_address.SetString(text.c_str(), document.GetAllocator());



        val.AddMember("name", attribute_name, document.GetAllocator());
        val.AddMember("phone_number", attribute_phone_number, document.GetAllocator());
        val.AddMember("address", attribute_address, document.GetAllocator());
        array_customers.PushBack(val, document.GetAllocator());
    }

    document.AddMember("customers", array_customers, document.GetAllocator());
    rapidjson::FileWriteStream write_stream(file, writeBuffer,
                       sizeof(writeBuffer));
    rapidjson::Writer<rapidjson::FileWriteStream> writer(write_stream);
    document.Accept(writer);
    fclose(file);
}

void add_car(SQLite::Database &database)
{
    std::string reg_num;
    std::string brand;
    std::string model;
    int year;

    std::cout << "Enter registration number" << std::endl;
    std::getline(std::cin, reg_num);
    std::cout << "Enter brand name" << std::endl;
    std::getline(std::cin, brand);
    std::cout << "Enter model name" << std::endl;
    std::getline(std::cin, model);
    std::cout << "Enter year" << std::endl;
    std::cin >> year;
    getchar();

    SQLite::Statement query(database, "INSERT INTO cars (reg_number, brand, model, year, completed_rentals) VALUES (?, ?, ?, ?, 0)");
    query.bind(1, reg_num);
    query.bind(2, brand);
    query.bind(3, model);
    query.bind(4, year);
    query.exec();
}

void edit_car(SQLite::Database &database)
{
    SQLite::Statement query(database, "SELECT * FROM cars");
    std::cout << "Enter the registration number of the car you want to edit" << std::endl;
    while (query.tryExecuteStep() == SQLITE_ROW)
    {
        std::cout << "Registration number: " << query.getColumn("reg_number") << ", brand: " <<
                  query.getColumn("brand") << ", model: " << query.getColumn("model") <<
                  ", year: " << query.getColumn("year") << std::endl;
    }

    std::string reg_num;
    std::string brand;
    std::string model;
    int year;

    std::cout << "Enter registration number" << std::endl;
    std::getline(std::cin, reg_num);
    std::cout << "Enter brand name" << std::endl;
    std::getline(std::cin, brand);
    std::cout << "Enter model name" << std::endl;
    std::getline(std::cin, model);
    std::cout << "Enter year" << std::endl;
    std::cin >> year;
    getchar();

    SQLite::Statement query2(database, "UPDATE cars SET brand = ?, model = ?, year = ? WHERE reg_number = ?");
    query2.bind(1, brand);
    query2.bind(2, model);
    query2.bind(3, year);
    query2.bind(4, reg_num);
    query2.exec();
}

void remove_car(SQLite::Database &database)
{
    SQLite::Statement query(database, "SELECT * FROM cars");
    std::cout << "Enter the registration number of the car you want to delete" << std::endl;
    while (query.tryExecuteStep() == SQLITE_ROW)
    {
        std::cout << "Registration number: " << query.getColumn("reg_number") << ", brand: " <<
                  query.getColumn("brand") << ", model: " << query.getColumn("model") <<
                  ", year: " << query.getColumn("year") << std::endl;
    }

    std::string reg_num;
    std::getline(std::cin, reg_num);

    SQLite::Statement query2(database, "DELETE FROM cars WHERE reg_number = ?");
    query2.bind(1, reg_num);
    query2.exec();
}

void add_customer(SQLite::Database &database)
{
    std::string name;
    std::string phone_number;
    std::string address;

    std::cout << "Enter customer name" << std::endl;
    std::getline(std::cin, name);
    std::cout << "Enter customer phone number" << std::endl;
    std::getline(std::cin, phone_number);
    std::cout << "Enter customer address" << std::endl;
    std::getline(std::cin, address);

    SQLite::Statement query(database, "INSERT INTO customers (name, phone_number, address) VALUES (?, ?, ?)");
    query.bind(1, name);
    query.bind(2, phone_number);
    query.bind(3, address);
    query.exec();
}

void edit_customer(SQLite::Database &database)
{
    SQLite::Statement query(database, "SELECT * FROM customers");
    std::cout << "Enter the ID of the customer you want to edit" << std::endl;
    while (query.tryExecuteStep() == SQLITE_ROW)
    {
        std::cout << "ID: " << query.getColumn("id") << ", name: " <<
        query.getColumn("name") << ", phone number: " << query.getColumn("phone_number") <<
        ", address: " << query.getColumn("address") << std::endl;
    }

    int customer_id;
    std::cin >> customer_id;
    getchar();
    std::string name;
    std::string phone_number;
    std::string address;

    std::cout << "Enter customer name" << std::endl;
    std::getline(std::cin, name);
    std::cout << "Enter customer phone number" << std::endl;
    std::getline(std::cin, phone_number);
    std::cout << "Enter customer address" << std::endl;
    std::getline(std::cin, address);

    SQLite::Statement query2(database, "UPDATE customers SET name = ?, phone_number = ?, address = ? WHERE id = ?");
    query2.bind(1, name);
    query2.bind(2, phone_number);
    query2.bind(3, address);
    query2.bind(4, customer_id);
    query2.exec();
}

void remove_customer(SQLite::Database &database)
{
    SQLite::Statement query(database, "SELECT * FROM customers");
    std::cout << "Enter the ID of the customer you want to delete" << std::endl;
    while (query.tryExecuteStep() == SQLITE_ROW)
    {
        std::cout << "ID: " << query.getColumn("id") << ", name: " <<
                  query.getColumn("name") << ", phone number: " << query.getColumn("phone_number") <<
                  ", address: " << query.getColumn("address") << std::endl;
    }

    std::string customer_id;
    std::getline(std::cin, customer_id);

    SQLite::Statement query2(database, "DELETE FROM customers WHERE id = ?");
    query2.bind(1, customer_id);
    query2.exec();
}

void assign_car_to_customer(SQLite::Database &database)
{
    int customer_selection_option;
    int car_selection_option;

    std::cout << "Enter 1 to list all customers, Enter 2 to search for customer by name" << std::endl;
    std::cin >> customer_selection_option;
    getchar();
    switch (customer_selection_option) {
        case 1:
        {
            SQLite::Statement query(database, "SELECT * FROM customers");
            std::cout << "Enter the ID of the customer you want to assign a car to" << std::endl;
            while (query.tryExecuteStep() == SQLITE_ROW)
            {
                std::cout << "ID: " << query.getColumn("id") << ", name: " <<
                          query.getColumn("name") << ", phone number: " << query.getColumn("phone_number") <<
                          ", address: " << query.getColumn("address") << std::endl;
            }
            break;
        }
        case 2:
        {
            std::string search;
            std::cout << "Search: ";
            std::getline(std::cin, search);
            SQLite::Statement query(database, "SELECT * FROM customers WHERE name LIKE ?");
            query.bind(1, search);
            std::cout << "Enter the ID of the customer you want to assign a car to" << std::endl;
            while (query.tryExecuteStep() == SQLITE_ROW)
            {
                std::cout << "ID: " << query.getColumn("id") << ", name: " <<
                          query.getColumn("name") << ", phone number: " << query.getColumn("phone_number") <<
                          ", address: " << query.getColumn("address") << std::endl;
            }
            break;
        }
    }

    std::string customer_name;
    int customer_id;
    std::cin >> customer_id;
    getchar();

    std::cout << "Enter 1 to list all cars, Enter 2 to search for car by brand" << std::endl;
    std::cin >> car_selection_option;
    getchar();

    switch (car_selection_option) {
        case 1:
        {
            SQLite::Statement query2(database, "SELECT name FROM customers WHERE id = ?");
            query2.bind(1, customer_id);

            while (query2.tryExecuteStep() == SQLITE_ROW)
            {
                std::cout << "Enter the registration number of the car you want to be assigned to " << query2.getColumn("name")
                          << std::endl;
            }

            SQLite::Statement query3(database, "SELECT * FROM cars");
            while (query3.tryExecuteStep() == SQLITE_ROW)
            {
                std::cout << "Registration number: " << query3.getColumn("reg_number") << ", brand: " <<
                          query3.getColumn("brand") << ", model: " << query3.getColumn("model") <<
                          ", year: " << query3.getColumn("year") << std::endl;
            }
            break;
        }
        case 2:
        {
            std::string search;
            std::cout << "Search: ";
            std::getline(std::cin, search);
            SQLite::Statement query(database, "SELECT * FROM cars7"
                                              " WHERE brand LIKE ?");
            query.bind(1, search);
            std::cout << "Enter the ID of the customer you want to assign a car to" << std::endl;
            while (query.tryExecuteStep() == SQLITE_ROW)
            {
                std::cout << "Registration number: " << query.getColumn("reg_number") << ", brand: " <<
                          query.getColumn("brand") << ", model: " << query.getColumn("model") <<
                          ", year: " << query.getColumn("year") << std::endl;
            }
            break;
        }
    }

    std::string reg_number;
    std::getline(std::cin, reg_number);

    SQLite::Statement query4(database, "UPDATE cars SET current_renter_id = ? WHERE reg_number = ?");
    query4.bind(1, customer_id);
    query4.bind(2, reg_number);
    query4.exec();

}

void unassign_car(SQLite::Database &database)
{
    SQLite::Statement query(database, "SELECT * FROM cars");
    std::cout << "Enter the registration number of the cars you want to unassign" << std::endl;
    while (query.tryExecuteStep() == SQLITE_ROW)
    {
        std::cout << "Registration number: " << query.getColumn("reg_number") << ", brand: " <<
                  query.getColumn("brand") << ", model: " << query.getColumn("model") <<
                  ", year: " << query.getColumn("year") << std::endl;
    }

    std::string reg_number;
    std::getline(std::cin, reg_number);

    SQLite::Statement query2(database, "UPDATE cars SET current_renter_id = NULL, completed_rentals = + 1 WHERE reg_number = ?");
    query2.bind(1, reg_number);
    query2.exec();

}

void print_statistics(SQLite::Database &database)
{
    SQLite::Statement cars_count(database, "SELECT COUNT(*) as cars_count FROM cars");
    while (cars_count.tryExecuteStep() == SQLITE_ROW)
    {
        std::cout << "Total number of cars: " << cars_count.getColumn("cars_count") << std::endl;
    }

    SQLite::Statement customers_count(database, "SELECT COUNT(*) as customers_count FROM customers");
    while (customers_count.tryExecuteStep() == SQLITE_ROW)
    {
        std::cout << "Total number of customers: " << customers_count.getColumn("customers_count") << std::endl;
    }

    SQLite::Statement active_rentals_count(database, "SELECT COUNT(*) as active_rentals_count FROM cars WHERE current_renter_id > 0");
    while (active_rentals_count.tryExecuteStep() == SQLITE_ROW)
    {
        std::cout << "Number of active rentals: " << active_rentals_count.getColumn("active_rentals_count") << std::endl;
    }

    SQLite::Statement completed_rentals_count(database, "SELECT SUM(completed_rentals) as completed_rentals_count FROM cars");
    while (completed_rentals_count.tryExecuteStep() == SQLITE_ROW)
    {
        std::cout << "Number of completed rentals: " << completed_rentals_count.getColumn("completed_rentals_count") << std::endl;
    }
}

int menu(SQLite::Database &database)
{
    int menu_option;
    std::cout << "Select option" << std::endl;
    std::cout << "1. Add a car" << std::endl;
    std::cout << "2. Edit car information" << std::endl;
    std::cout << "3. Delete a car" << std::endl;
    std::cout << "4. Add a customer" << std::endl;
    std::cout << "5. Edit customer information" << std::endl;
    std::cout << "6. Delete customer" << std::endl;
    std::cout << "7. Assign a car to a customer" << std::endl;
    std::cout << "8. Unassign a car" << std::endl;
    std::cout << "9. Print statistics" << std::endl;
    std::cout << "10. Read from JSON" << std::endl;
    std::cout << "11. Write to JSON" << std::endl;
    std::cout << "12. Exit" << std::endl;

    std::cin >> menu_option;
    getchar();
    switch (menu_option) {
        case 1:
            add_car(database);
            break;
        case 2:
            edit_car(database);
            break;
        case 3:
            remove_car(database);
            break;
        case 4:
            add_customer(database);
            break;
        case 5:
            edit_customer(database);
            break;
        case 6:
            remove_customer(database);
            break;
        case 7:
            assign_car_to_customer(database);
            break;
        case 8:
            unassign_car(database);
            break;
        case 9:
            print_statistics(database);
            break;
        case 10:
            read_json(database);
            break;
        case 11:
            write_json(database);
            break;
        case 12:
            return 0;
    }
}

int main() {
    SQLite::Database database("car_rental.sqlite", SQLite::OPEN_READWRITE);
    while (menu(database) != 0)
    {
        continue;
    }
    return 0;
}
