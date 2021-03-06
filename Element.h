#pragma once

template<typename T>
class Element
{
private:
    T value;
public:
    Element<T>* prev;
    Element<T>* next;

    Element(T value, Element* prev = nullptr, Element* next = nullptr): value(value), prev(prev), next(next){}

    T& getValue()
    {
        return value;
    }
};
