#pragma once

#include <string>


class Person
{
private:
    std::string name;
    std::string number;
    size_t price;
    std::string address;
public:
    Person(std::string name, std::string number, size_t price, std::string address);
    Person() = default;
    ~Person() = default;

    bool operator==(const Person& other) const;
    bool operator!=(const Person& other) const;

    std::string getName() const;
    std::string getNumber() const;
    size_t getPrice() const;
    std::string getAddress() const;
};

size_t per_to_number(const Person& p);
std::string per_to_string(const Person& p);
