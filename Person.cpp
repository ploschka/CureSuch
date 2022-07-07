#include "Person.h"

Person::Person(std::string name, std::string number, size_t price, std::string address):
    name(name), number(number), price(price), address(address){}

bool Person::operator==(Person other) const
{
    return (this->name == other.name && this->number == other.number && this->price == other.price && this->address == other.address);
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

size_t to_number(Person p)
{
    size_t result = 0;
    std::string combined = p.name + p.number + p.address;
    size_t j = 1;
    for(auto i: combined)
    {
        result += i * j;
        j++;
    }
    result += p.price * j;
    return result;
}
