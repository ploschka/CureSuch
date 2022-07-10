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
    List(T value)
    {
        head = new Element(value);
        tail = head;
    }
    List()
    {
        head = nullptr;
        tail = nullptr;
    }
    bool isEmpty()
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
        else
        {
            std::cout << "List is empty\n";
        }
    }
    int length()
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
    void print(std::ostream& os)
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
            os << "List is empty\n";
        }
    }
    void add(T value)
    {
        if (!(isEmpty()))
        {
            if (value < head->getValue())
            {
                Element<T>* newby = new Element<T>(value, nullptr, head);
                head->prev = newby;
                head = newby;
            }
            else if (value >= tail->getValue())
            {
                Element<T>* newby = new Element<T>(value, tail);
                tail->next = newby;
                tail = newby;
            }
            else
            {
                Element<T>* tmp = head;
                while (value > tmp->getValue())
                {
                    tmp = tmp->next;
                }
                Element<T>* newby = new Element<T>(value, tmp->prev, tmp);
                tmp->prev = newby;
                newby->prev->next = newby;
            }
        }
        else
        {
            head = new Element<T>(value);
            tail = head;
        }
    }
    void delEnd()
    {
        if (!(isEmpty()))
        {
            tail = tail->prev;
            delete tail->next;
            tail->next = nullptr;
        }
        else
        {
            std::cout << "������ ����\n";
        }
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
    Element<T>* index(size_t ind)
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
