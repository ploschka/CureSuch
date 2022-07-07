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

    bool operator==(Person other) const;

    std::string getName() const;
    std::string getNumber() const;
    size_t getPrice() const;
    std::string getAddress() const;

    friend size_t to_number(Person);
};

size_t to_number(Person p);
