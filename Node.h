#pragma once
#include "List.h"
#include <iostream>
#include <vector>

template<typename T1, typename T2>
class Tree;

template<typename T1, typename T2>
class Node
{
private:
    void print(std::ostream& os, int level) const
    {
        if(!(this->right->isNull()))
        {
            this->right->print(os, level + 1);
        }

        for(int i = 0; i < level; i++)
        {
            os << "\t";
        }

        os << ((!color)? ("B: "): ("R: ")) << key << ": ";
        list->print(os);
        os << std::endl;

        if(!(this->left->isNull()))
        {
            this->left->print(os, level + 1);
        }
    }
    void erase()
    {
        if(!(this->left->isNull()))
        {
            this->left->erase();
            Node<T1, T2>* tmp = this->left;
            this->left = this->left->left;
            delete tmp;
        }
        if(!(this->right->isNull()))
        {
            this->right->erase();
            Node<T1, T2>* tmp = this->right;
            this->right = this->right->right;
            delete tmp;
        }
    }
    void giveList(std::vector<List<T2>*>* vec) const
    {
        vec->push_back(this->getValue());
        if(!this->left->isNull())
        {
            this->left->giveList(vec);
        }
        if(!this->right->isNull())
        {
            this->right->giveList(vec);
        }
    }

    T1 key;
    List<T2>* list;
    Node<T1, T2>* left;
    Node<T1, T2>* right;
    Node<T1, T2>* parent;
	bool color;
public:
    Node<T1, T2>(T1 key, T2 value, Node<T1, T2>* parent, Node<T1, T2>* left, Node<T1, T2>* right):
        key(key), left(left), right(right), parent(parent), color(1)
    {
        list = new List<T2>();
        list->addEnd(value);
    }
    Node<T1, T2>():left(this), right(this), parent(nullptr), color(0)
    {
        list = new List<T2>();
    }
    ~Node<T1, T2>()
    {
        list->erase();
        delete list;
    }
    const T1& getKey() const
    {
        return this->key;
    }
    List<T2>* getValue() const
    {
        return list;
    }
    bool isNull() const
    {
        return (this->list->isEmpty());
    }

    friend class Tree<T1, T2>;
};
