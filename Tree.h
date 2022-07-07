#pragma once
#include "Node.h"

template<typename T>
class Tree
{
private:
    Node<T>* root;
    Node<T>* null;
    Node<T>* traverse(Node<T>* node, const T& value)
    {
        if ((node->getValue() == value) ||
            ((node->getValue() < value) && (node->right == null)) ||
            ((node->getValue() > value) && (node->left == null)))
        {
            return node;
        }
        else if (node->getValue() < value)
        {
            return traverse(node->right, value);
        }
        else if (node->getValue() > value)
        {
            return traverse(node->left, value);
        }
    }
    void rRotation(Node<T>* node)
    {
        Node<T>* other = node->left;
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
    void lRotation(Node<T>* node)
    {
        Node<T>* other = node->right;
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
    void insertFixup(Node<T>* node)
    {
        while(node->parent->color == 1)
        {
            if((node->parent == node->parent->parent->left) && (node->parent->parent != null))
            {
                Node<T>* uncle = node->parent->parent->right;
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
                Node<T>* uncle = node->parent->parent->left;
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
    void removeFixup(Node<T>* x)
    {
        while ((x != root) && (x->color == 0))
        {
            if (x == x->parent->left)
            {
                Node<T>* w = x->parent->right;
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
                Node<T>* w = x->parent->left;
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
    void transplant(Node<T>* node, Node<T>* other)
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
    Node<T>* minimum(Node<T>* node)
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
        null = new Node<T>();
        root = null;
    }
    Tree(T value)
    {
        null = new Node<T>();
        root = new Node(value, null, null, null);
        root->color = 0;
    }

    void insert(T value)
    {
        if(root != null)
        {
            Node<T>* par = traverse(root, value);
            if(value < par->getValue())
            {
                par->left = new Node(value, par, null, null);
                insertFixup(par->left);
            }
            else if(value > par->getValue())
            {
                par->right = new Node(value, par, null, null);
                insertFixup(par->right);
            }
            else
            {
                par->list.add(value);
            }
        }
        else
        {
            root = new Node(value, null, null, null);
            root->color = 0;
        }
    }
    void remove(T value)
    {
        Node<T>* z = traverse(root, value);
        Node<T>* y = z;
        Node<T>* x;
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
    void print()
    {
        if (root != null)
        {
            root->print(0);
        }
        else
        {
            std::cout << "\t\t" << "Дерево пусто" << std::endl;
        }
    }
    bool find(T value)
    {
        Node<T>* node = traverse(root, value);
        return (value == node->getValue());
    }
	
    void erase()
    {
        root->erase();
        delete root;
        root = null;
    }

    void pryam()
    {
        root->pryam();
        std::cout << std::endl;
    }
    void obrat()
    {
        root->obrat();
        std::cout << std::endl;
    }
    void symmlp()
    {
        root->symmlp();
        std::cout << std::endl;
    }
    void symmpl()
    {
        root->symmpl();
        std::cout << std::endl;
    }
};
