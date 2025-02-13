#include <iostream>

#include "rapidcsv/rapidcsv.h"


struct Customer{
    int id;
    std::string name;
    std::string address;
};

struct Product{
    int id;
    std::string name;
    int price;
};

struct Order{
    int id;
    int customer_id;
    int product_id;
    int amount;
};

std::vector<Product>product_list;
std::vector<Customer>customer_list;
std::vector<Order>order_list;

void set_customers()
{
    rapidcsv::Document document("customers.csv");


    std::vector<int> id = document.GetColumn<int>("id");
    std::vector<std::string> name = document.GetColumn<std::string>("name");
    std::vector<std::string> address = document.GetColumn<std::string>("address");

    for (int i = 0; i < id.size(); i++)
    {
        Customer customer;
        customer.id = id[i];
        customer.name = name[i];
        customer.address = address[i];
        customer_list.push_back(customer);
        std::cout << "Customer: " << customer.name << ", " << customer.address << std::endl;
    }
}

void set_products()
{
    rapidcsv::Document document("products.csv");


    std::vector<int> id = document.GetColumn<int>("id");
    std::vector<std::string> name = document.GetColumn<std::string>("name");
    std::vector<int> price = document.GetColumn<int>("price");

    for (int i = 0; i < id.size(); i++)
    {
        Product product;
        product.id = id[i];
        product.name = name[i];
        product.price = price[i];
        product_list.push_back(product);
        std::cout << "Product: " << product.name << ", " << product.price << std::endl;
    }
}

void set_orders()
{
    rapidcsv::Document document("orders.csv");


    std::vector<int> id = document.GetColumn<int>("id");
    std::vector<int> customer_id = document.GetColumn<int>("customerid");
    std::vector<int> product_id = document.GetColumn<int>("productid");
    std::vector<int> amount = document.GetColumn<int>("amount");

    for (int i = 0; i < id.size(); i++)
    {
        Order order;
        order.id = id[i];
        order.customer_id = customer_id[i];
        order.product_id = product_id[i];
        order.amount = amount[i];
        order_list.push_back(order);
    }
}

void total_ordered_products()
{
    for (int i = 0; i < product_list.size(); i++)
    {
        std::cout << product_list[i].name;
        int temp_amount = 0;
        for (int j = 0; j < order_list.size(); ++j)
        {
            if (order_list[j].product_id == product_list[i].id)
            {
                temp_amount += order_list[j].amount;
            }
        }
        std::cout << " amount: " << temp_amount << std::endl;
        std::cout << product_list[i].name << " gross income: " << product_list[i].price * temp_amount << std::endl;
    }
}

void customer_spending()
{
    for (int i = 0; i < customer_list.size(); ++i) {
        std::cout << customer_list[i].name;
        int money = 0;
        for (int j = 0; j < order_list.size(); ++j) {
            if (order_list[j].customer_id == customer_list[i].id)
            {
                for (int k = 0; k < product_list.size(); ++k) {
                    if (product_list[k].id == order_list[j].product_id)
                    {
                        money += product_list[k].price * order_list[j].amount;
                    }
                }
            }
        }
        std::cout << " money spent: " << money << std::endl;
    }
}

int main()
{
    set_customers();
    set_products();
    set_orders();
    total_ordered_products();
    customer_spending();






    return 0;
}
