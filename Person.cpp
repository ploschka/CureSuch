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

size_t per_to_number(const Person& p)
{
    size_t result = 0;
    std::string combined = p.getNumber();
    size_t j = 1;
    for(auto i: combined)
    {
        result += i * j;
        j++;
    }
    result += p.getPrice() * j;
    return result;
}

std::string per_to_string(const Person& p)
{
    return (p.getName() + ' ' + p.getNumber() + ' ' + std::to_string(p.getPrice()) + ' ' + p.getAddress());
}
