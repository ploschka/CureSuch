#pragma once
#include "Element.h"
#include <iostream>

template<typename T>
class List
{
private:
    Element<T>* head;
    Element<T>* tail;
public:
    List()
    {
        head = nullptr;
        tail = nullptr;
    }
    bool isEmpty() const
    {
        return ((head == nullptr) && (tail == nullptr));
    }
    void erase()
    {
        if (!(isEmpty()))
        {
            Element<T>* tmp = head;
            head = nullptr;
            tail = nullptr;
            while (tmp->next != nullptr)
            {
                tmp = tmp->next;
                delete tmp->prev;
            }
            delete tmp;
        }
    }
    int length() const
    {
        int count = 0;
        Element<T>* tmp = head;
        while (tmp != nullptr)
        {
            count++;
            tmp = tmp->next;
        }
        return count;
    }
    void print(std::ostream& os) const
    {
        if (!(isEmpty()))
        {
            Element<T>* tmp = head;
            int len = length();
            while(tmp)
            {
#ifdef TYPE2POINTER
                    os << *(tmp->getValue());
#else
                    os << tmp->getValue();
#endif
                tmp = tmp->next;
                os << " --> ";
            }
            os << std::endl;
        }
        else
        {
            os << "Список пуст\n";
        }
    }
    void addEnd(const T& value)
    {
        auto newby = new Element<T>(value, tail, nullptr);
        if(tail)
        {
            tail->next = newby;
        }
        tail = newby;
        if(!head)
            head = newby;
    }
    void remove(const T& value)
    {
        Element<T>* curr = head;
        while(curr->getValue() != value)
        {
            curr = curr->next;
        }
        if(curr->next)
        {
            curr->next->prev = curr->prev;
        }
        if(curr->prev)
        {
            curr->prev->next = curr->next;
        }
        if(head == curr)
        {
            head = curr->next;
        }
        if(tail == curr)
        {
            tail = curr->prev;
        }
        delete curr;
    }
    Element<T>* operator[](size_t index)
    {
        if (index >= 0)
        {
            Element<T>* tmp = head;
            size_t count = 0;
            for (int i = 0; i < index; i++)
            while(tmp && count < index)
            {
                tmp = tmp->next;
            }
            return tmp;
        }
        else
        {
            exit(-1);
        }
    }
    Element<T>* index(size_t ind) const
    {
        if (ind >= 0)
        {
            Element<T>* tmp = head;
            size_t count = 0;
            for (int i = 0; i < ind; i++)
            while(tmp && count < ind)
            {
                tmp = tmp->next;
            }
            return tmp;
        }
        else
        {
            exit(-1);
        }
    }
};
