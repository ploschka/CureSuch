#pragma once
#include "List.h"
#include <iostream>

template<typename T>
class Tree;

template<typename T>
class Node
{
private:
    void print(std::ostream& os, int level)
    {
        if(!(this->right->isNull()))
        {
            this->right->print(os, level + 1);
        }

        for(int i = 0; i < level; i++)
        {
            os << "\t";
        }

        os << ((color == 0)? ("B: "): ("R: "));
        list.print(os);
        os << std::endl;

        if(!(this->left->isNull()))
        {
            this->left->print(os, level + 1);
        }
    }
    int erase()
    {
        if(!(this->left->isNull()))
        {
            this->left->erase();
            Node* tmp = this->left;
            this->left = this->left->left;
            delete tmp;
        }
        if(!(this->right->isNull()))
        {
            this->right->erase();
            Node* tmp = this->right;
            this->right = this->right->right;
            delete tmp;
        }
        return 0;
    }

    void pryam()
    {
        std::cout << getValue() << " ";

        if (!(left->isNull()))
        {
            left->pryam();
        }

        if (!(right->isNull()))
        {
            right->pryam();
        }
    }
    void obrat()
    {
        if (!(left->isNull()))
        {
            left->obrat();
        }

        if (!(right->isNull()))
        {
            right->obrat();
        }

        std::cout << getValue() << " ";
    }
    void symmlp()
    {
        if (!(left->isNull()))
        {
            left->symmlp();
        }

        std::cout << getValue() << " ";

        if (!(right->isNull()))
        {
            right->symmlp();
        }
    }
    void symmpl()
    {
        if (!(right->isNull()))
        {
            right->symmpl();
        }

        std::cout << getValue() << " ";

        if (!(left->isNull()))
        {
            left->symmpl();
        }
    }

    List<T> list;
    Node<T>* left;
    Node<T>* right;
    Node<T>* parent;
	bool color;
public:
    Node<T>(T value, Node<T>* parent, Node<T>* left, Node<T>* right):
        left(left), right(right), parent(parent), color(1)
    {
        list = List(value);
    }
    Node<T>():left(this), right(this), parent(nullptr), color(0)
    {
        list = List<T>();
    }
    ~Node<T>()
    {
        list.erase();
        list.~List();
    }
    T& getValue()
    {
        if (!(this -> isNull()))
            return list[1];
        else
            throw std::runtime_error("Null node");
    }
    bool isNull()
    {
        return (this->list.isEmpty());
    }

    friend class Tree<T>;
};
