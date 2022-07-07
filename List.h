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
    void print()
    {
        if (!(isEmpty()))
        {
            Element<T>* tmp = head;
            int len = length();
            for(int i = 1; i <= len; i++)
            {
                std::cout << tmp->getValue() << " ";
                tmp = tmp->next;
            }
            std::cout << std::endl;
        }
        else
        {
            std::cout << "List is empty\n";
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
    T& operator[](int index)
    {
        if ((index <= length()) && (index > 0))
        {
            Element<T>* tmp = head;
            for (int i = 1; i < index; i++)
            {
                tmp = tmp->next;
            }
            return tmp->getValue();
        }
        else
        {
            exit(-1);
        }
    }
};
