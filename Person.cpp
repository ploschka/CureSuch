#include "Person.h"

Person::Person(std::string name, std::string number, size_t price, std::string address):
    name(name), number(number), price(price), address(address){}

bool Person::operator==(const Person& other) const
{
    return this->number == other.number;
}

bool Person::operator!=(const Person& other) const
{
    return !(*this == other);
}

std::string Person::getName() const
{
    return name;
}
std::string Person::getNumber() const
{
    return number;
}
size_t Person::getPrice() const
{
    return price;
}
std::string Person::getAddress() const
{
    return address;
}

std::string per_to_string(const Person& p)
{
    return (p.getName() + ' ' + p.getNumber() + ' ' + std::to_string(p.getPrice()) + ' ' + p.getAddress());
}

std::ostream& operator<<(std::ostream& os, const Person& p)
{
    os << per_to_string(p);
    return os;
}
