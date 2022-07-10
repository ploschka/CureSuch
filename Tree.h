#pragma once
#include "Node.h"
#include <iostream>

template<typename T1, typename T2>
class Tree
{
private:
    Node<T1, T2>* root;
    Node<T1, T2>* null;
    Node<T1, T2>* traverse(Node<T1, T2>* node, const T1& key)
    {
        if ((node->getKey() == key) ||
            ((node->getKey() < key) && (node->right == null)) ||
            ((key < node->getKey()) && (node->left == null)))
        {
            return node;
        }
        else if (node->getKey() < key)
        {
            return traverse(node->right, key);
        }
        else if (node->getKey() > key)
        {
            return traverse(node->left, key);
        }
        else
        {
            throw std::runtime_error("WTF?");
            return nullptr;
        }
    }
    void rRotation(Node<T1, T2>* node)
    {
        Node<T1, T2>* other = node->left;
        node->left = other->right;
        if (!(other->right->isNull()))
        {
            other->right->parent = node;
        }
        other->parent = node->parent;
        if (node->parent->isNull())
        {
            root = other;
        }
        else if (node == node->parent->right)
        {
            node->parent->right = other;
        }
        else
        {
            node->parent->left = other;
        }
        other->right = node;
        node->parent = other;
    }
    void lRotation(Node<T1, T2>* node)
    {
        Node<T1, T2>* other = node->right;
        node->right = other->left;
        if (!(other->left->isNull()))
        {
            other->left->parent = node;
        }
        other->parent = node->parent;
        if (node->parent->isNull())
        {
            root = other;
        }
        else if (node == node->parent->left)
        {
            node->parent->left = other;
        }
        else
        {
            node->parent->right = other;
        }
        other->left = node;
        node->parent = other;
    }
    void insertFixup(Node<T1, T2>* node)
    {
        while(node->parent->color == 1)
        {
            if((node->parent == node->parent->parent->left) && (node->parent->parent != null))
            {
                Node<T1, T2>* uncle = node->parent->parent->right;
                if(uncle->color == 1)
                {
                    node->parent->color = 0;
                    uncle->color = 0;
                    node->parent->parent->color = 1;
                    node = node->parent->parent;
                }
                else
                {
                    if(node == node->parent->right)
                    {
                        node = node->parent;
                        lRotation(node);
                    }
                    node->parent->color = 0;
                    node->parent->parent->color = 1;
                    rRotation(node->parent->parent);
                }
            }
            else if((node->parent == node->parent->parent->right) && (node->parent->parent != null))
            {
                Node<T1, T2>* uncle = node->parent->parent->left;
                if(uncle->color == 1)
                {
                    node->parent->color = 0;
                    uncle->color = 0;
                    node->parent->parent->color = 1;
                    node = node->parent->parent;
                }
                else
                {
                    if(node == node->parent->left)
                    {
                        node = node->parent;
                        rRotation(node);
                    }
                    node->parent->color = 0;
                    node->parent->parent->color = 1;
                    lRotation(node->parent->parent);
                }
            }
        }
        root->color = 0;
    }
    void removeFixup(Node<T1, T2>* x)
    {
        while ((x != root) && (x->color == 0))
        {
            if (x == x->parent->left)
            {
                Node<T1, T2>* w = x->parent->right;
                if (w->color == 1)
                {
                    w->color = 0;
                    x->parent->color = 1;
                    lRotation(x->parent);
                    w = x->parent->right;
                }
                if ((w->left->color == 0) && (w->right->color == 0))
                {
                    w->color = 1;
                    x = x->parent;
                }
                else
                {
                    if (w->right->color == 0)
                    {
                        w->left->color = 0;
                        w->color = 1;
                        rRotation(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = 0;
                    w->right->color = 0;
                    lRotation(x->parent);
                    x = root;
                }
            }
            else
            {
                Node<T1, T2>* w = x->parent->left;
                if (w->color == 1)
                {
                    w->color = 0;
                    x->parent->color = 1;
                    rRotation(x->parent);
                    w = x->parent->left;
                }
                if ((w->right->color == 0) && (w->left->color == 0))
                {
                    w->color = 1;
                    x = x->parent;
                }
                else
                {
                    if (w->left->color == 0)
                    {
                        w->right->color = 0;
                        w->color = 1;
                        lRotation(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = 0;
                    w->left->color = 0;
                    rRotation(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }
    void transplant(Node<T1, T2>* node, Node<T1, T2>* other)
    {
        if(node->parent == null)
        {
            root = other;
        }
        else if(node == node->parent->left)
        {
            node->parent->left = other;
        }
        else
        {
            node->parent->right = other;
        }
        other->parent = node->parent;
    }
    Node<T1, T2>* minimum(Node<T1, T2>* node)
    {
        if(node->left == null)
        {
            return node;
        }
        else
        {
            return minimum(node->left);
        }
    }
public:
    Tree()
    {
        null = new Node<T1, T2>();
        root = null;
    }
    Tree(T1 key, T2 value)
    {
        null = new Node<T1, T2>();
        root = new Node(key, value, null, null, null);
        root->color = 0;
    }

    void insert(T1 key, T2 value)
    {
        if(root != null)
        {
            Node<T1, T2>* par = traverse(root, key);
            if(key < par->getKey())
            {
                par->left = new Node(key, value, par, null, null);
                insertFixup(par->left);
            }
            else if(key > par->getKey())
            {
                par->right = new Node(key, value, par, null, null);
                insertFixup(par->right);
            }
            else
            {
                par->list->add(value);
            }
        }
        else
        {
            root = new Node(key, value, null, null, null);
            root->color = 0;
        }
    }
    void remove(T1 key, T2 value)
    {
        Node<T1, T2>* z = traverse(root, key);
        Node<T1, T2>* y = z;
        Node<T1, T2>* x;
        int nodeCol = y->color;
        if(z->left == null)
        {
            x = y->right;
            transplant(z, z->right);
        }
        else if(z->right == null)
        {
            x = z->left;
            transplant(z, z->left);
        }
        else
        {
            y = minimum(z->right);
            nodeCol = y->color;
            x = y->right;
            if(y->parent == z)
            {
                x->parent = y;
            }
            else
            {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        if(nodeCol == 0)
        {
            removeFixup(x);
        }
    }
    void print(std::ostream& os)
    {
        if (root != null)
        {
            root->print(os, 0);
        }
        else
        {
            os << "\t\tДерево пусто" << std::endl;
        }
    }
    bool find(T1 key, T2 value)
    {
        Node<T1, T2>* node = traverse(root, key);
        List<T2>* list = node->getValue();
        size_t len = list->length();

        for(size_t i = 0; i < len; i++)
        {
            if((*(list))[i] == value)
            {
                return true;
            }
        }
        return false;
    }
	
    void erase()
    {
        root->erase();
        delete root;
        root = null;
    }
};
