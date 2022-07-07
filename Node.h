#pragma once
#include "List.h"

template<typename T>
class Tree;

template<typename T>
class Node
{
private:
    void print(int level)
    {
        std::string str;
        if(!(this->right->isNull()))
        {
            this->right->print(level + 1);
        }

        for(int i = 0; i < level; i++)
        {
            std::cout << "\t";
        }

        std::cout << ((color == 0)? ("\033[100m"): ("\033[41m")) << getValue() << " " << list.length() << "\033[0m" << std::endl;

        if(!(this->left->isNull()))
        {
            this->left->print(level + 1);
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
    }
    bool isNull()
    {
        return (this->list.isEmpty());
    }

    friend class Tree<T>;
};
