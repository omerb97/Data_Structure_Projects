#ifndef AVLRANKTREE_H
#define AVLRANKTREE_H


#include <iostream>
#include "Course.h"
#include "Exceptions.h"

template<class T>
struct Node
{
    T data;
    Node *left;
    Node *right;
    Node *parent;
    int balance_factor;
    int real_rank;
    int right_rank;

    Node() {};

    Node(T data, Node *left, Node *right, Node *parent, int balance_factor, int real_rank, int rank_right);

    ~Node();
};

template<class T>
Node<T>::Node(T data, Node *left, Node *right, Node *parent, int balance_factor, int real_rank, int rank_right) : data(
        data)
{
    this->left = left;
    this->right = right;
    this->parent = parent;
    this->balance_factor = balance_factor;
    this->real_rank = real_rank;
    this->right_rank = rank_right;
}

template<class T>
Node<T>::~Node()
{
    if (left)
    {
        delete left;
    }

    if (right)
    {
        delete right;
    }
}

template<class T>
class AVLRankTree
{
private:
    Node<T> *root;

    Node<T> *searchHelper(Node<T> *node, T data);

    Node<T> *deleteNodeHelper(Node<T> *node, T data);

    void rebalanceAfterInsert(Node<T> *node);

    Node<T> *rebalanceAfterDelete(Node<T> *node);

    void balanceTree(Node<T> *node);

    Node<T> *updateBalance(Node<T> *node);

    Node<T> *leftRotate(Node<T> *node);

    Node<T> *rightRotate(Node<T> *node);

    void clearHelper(Node<T> *node);

    int getBalanceFactor(Node<T> *node);

    int getHeight(Node<T> *node);

    int max(int x, int y);

    Node<T> *minimumNode(Node<T> *node);

    Node<T> *FindIthHelper(Node<T> *node, int i);

public:
    AVLRankTree(); //c'tor
    AVLRankTree(const AVLRankTree &node); //copy c'tor
    ~AVLRankTree(); //d'tor

    void insert(T insertData);

    Node<T> *deleteNode(T data);

    Node<T> *search(T wantedData);

    T *GetData(Node<T> *node);

    T findIthMax(int i, int total);
};

template<class T>
AVLRankTree<T>::AVLRankTree()
{
    root = nullptr;
}

template<class T>
AVLRankTree<T>::AVLRankTree(const AVLRankTree &node) : root(node.root)
{

}

template<class T>
AVLRankTree<T>::~AVLRankTree()
{
    clearHelper(root);
}

template<class T>
void AVLRankTree<T>::balanceTree(Node<T> *node)
{
    if (node->balance_factor < -1 || node->balance_factor > 1)
    {
        rebalanceAfterInsert(node);
        return;
    }
    else
    {
        node->right_rank = 1;
        node->real_rank = 1;
        if (node->left)
        {
            node->real_rank += node->left->real_rank;
        }

        if (node->right)
        {
            node->real_rank += node->right->real_rank;
            node->right_rank += node->right->real_rank;
        }
    }

    if (node->parent != nullptr)
    {
        if (node == node->parent->left)
        {
            node->parent->balance_factor += 1;
        }

        if (node == node->parent->right)
        {
            node->parent->balance_factor -= 1;
        }

        if (node->parent->balance_factor != 0)
        {
            balanceTree(node->parent);
        }
    }
}

template<class T>
void AVLRankTree<T>::insert(T insertData)
{
    Node<T> *node = new Node<T>(insertData, nullptr, nullptr, nullptr, 0, 1, 1);
    Node<T> *y = nullptr;
    Node<T> *x = this->root;

    while (x != nullptr)
    {
        y = x;
        y->real_rank = y->real_rank + 1;
        if (node->data < x->data)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
            y->right_rank = y->right_rank + 1;
        }
    }

    // y is parent of x
    node->parent = y;
    if (y == nullptr)
    {
        root = node;
    }
    else if (node->data < y->data)
    {
        y->left = node;
    }
    else
    {
        y->right = node;
    }

    balanceTree(node);
}

template<class T>
Node<T> *AVLRankTree<T>::leftRotate(Node<T> *node)
{
    Node<T> *temp = node->right;
    if (temp)
    {
        node->right = temp->left;
    }

    node->real_rank = 1;
    node->right_rank = 1;

    if (node->right)
    {
        node->right_rank += node->right->real_rank;
        node->real_rank += node->right->real_rank;
    }

    if (node->left)
    {
        node->real_rank += node->left->real_rank;
    }

    if (temp && temp->left != nullptr)
    {
        temp->left->parent = node;
    }
    if (temp)
    {
        temp->parent = node->parent;
    }
    if (node && node->parent == nullptr)
    {
        this->root = temp;
    }
    else if (node->parent && node == node->parent->left)
    {
        node->parent->left = temp;
    }
    else if (node->parent)
    {
        node->parent->right = temp;
    }
    if (temp)
    {
        temp->left = node;

        temp->real_rank = 1;
        temp->right_rank = 1;

        if (temp->right)
        {
            temp->right_rank += temp->right->real_rank;
            temp->real_rank += temp->right->real_rank;
        }

        if (temp->left)
        {
            temp->real_rank += temp->left->real_rank;
        }
    }

    node->parent = temp;

    // update the balance factor
    if (temp && temp->balance_factor < 0)
    {
        node->balance_factor = node->balance_factor + 1 - temp->balance_factor;
    }
    else
    {
        node->balance_factor = node->balance_factor + 1;
    }

    if (node->balance_factor > 0)
    {
        temp->balance_factor = temp->balance_factor + 1 + node->balance_factor;
    }
    else
    {
        temp->balance_factor = temp->balance_factor + 1;
    }

    return temp;
}

template<class T>
Node<T> *AVLRankTree<T>::rightRotate(Node<T> *node)
{
    Node<T> *temp = node->left;
    node->left = temp->right;

    node->real_rank = 1;
    node->right_rank = 1;

    if (node->right)
    {
        node->right_rank += node->right->real_rank;
        node->real_rank += node->right->real_rank;
    }

    if (node->left)
    {
        node->real_rank += node->left->real_rank;
    }

    if (temp->right != nullptr)
    {
        temp->right->parent = node;
    }
    temp->parent = node->parent;
    if (node->parent == nullptr)
    {
        this->root = temp;
    }
    else if (node == node->parent->right)
    {
        node->parent->right = temp;
    }
    else
    {
        node->parent->left = temp;
    }
    temp->right = node;
    node->parent = temp;

    temp->real_rank = 1;
    temp->right_rank = 1;

    if (temp->right)
    {
        temp->right_rank += temp->right->real_rank;
        temp->real_rank += temp->right->real_rank;
    }

    if (temp->left)
    {
        temp->real_rank += temp->left->real_rank;
    }

    // update the balance factor
    if (temp->balance_factor > 0)
    {
        node->balance_factor = node->balance_factor - 1 - temp->balance_factor;
    }
    else
    {
        node->balance_factor = node->balance_factor - 1;
    }

    if (node->balance_factor < 0)
    {
        temp->balance_factor = temp->balance_factor - 1 + node->balance_factor;
    }
    else
    {
        temp->balance_factor = temp->balance_factor - 1;
    }

    return temp;
}

template<class T>
void AVLRankTree<T>::rebalanceAfterInsert(Node<T> *node)
{
    if (node->balance_factor > 0)
    {
        if (node->left->balance_factor >= 0)
        {
            rightRotate(node);
        }
        else
        {
            leftRotate(node->left);
            rightRotate(node);
        }
    }
    else if (node->balance_factor < 0)
    {
        if (node->right->balance_factor <= 0)
        {
            leftRotate(node);
        }
        else
        {
            rightRotate(node->right);
            leftRotate(node);
        }
    }
}

template<class T>
Node<T> *AVLRankTree<T>::search(T wantedData)
{
    T temp(wantedData);
    return searchHelper(root, temp);
}

template<class T>
Node<T> *AVLRankTree<T>::searchHelper(Node<T> *node, T data)
{
    if (node == nullptr || data == node->data)
    {
        return node;
    }

    if (data < node->data)
    {
        return searchHelper(node->left, data);
    }
    return searchHelper(node->right, data);
}

template<class T>
Node<T> *AVLRankTree<T>::deleteNodeHelper(Node<T> *node, T data)
{
    if (node == nullptr)
    {
        return node;
    }
    else if (data < node->data)
    {
        node->real_rank = node->real_rank - 1;
        node->left = deleteNodeHelper(node->left, data);
    }
    else if (data > node->data)
    {
        node->right_rank = node->right_rank - 1;
        node->real_rank = node->real_rank - 1;
        node->right = deleteNodeHelper(node->right, data);
    }
    else
    {
        // the value has been found

        //node is a leaf
        if (node->left == nullptr && node->right == nullptr)
        {
            if (node->parent && node->parent->right && node->parent->right->data == node->data)
            {
                node->parent->right = nullptr;
            }
            else if (node->parent && node->parent->left && node->parent->left->data == node->data)
            {
                node->parent->left = nullptr;
            }
            else if (!node->parent)
            {
                root = nullptr;
            }
            delete node;
            node = nullptr;
        }

            //node has only one son
        else if (node->left == nullptr)
        {
            Node<T> *temp = node;
            node = node->right;
            node->parent = temp->parent;
            temp->right = nullptr;

            if (node->parent && node->parent->right == temp)
            {
                node->parent->right = node;
            }
            else if (node->parent)
            {
                node->parent->left = node;
            }
            else if (temp->data == root->data)
            {
                root = node;
            }

            delete temp;
        }
        else if (node->right == nullptr)
        {
            Node<T> *temp = node;
            node = node->left;
            node->parent = temp->parent;
            temp->left = nullptr;

            if (node->parent && node->parent->right == temp)
            {
                node->parent->right = node;
            }
            else if (node->parent)
            {
                node->parent->left = node;
            }
            else if (temp->data == root->data)
            {
                root = node;
            }

            delete temp;
        }

            //node has two sons
        else
        {
            Node<T> *temp = minimumNode(node->right);
            node->data = temp->data;
            node->right = deleteNodeHelper(node->right, temp->data);
        }
    }

    return updateBalance(node);
}

template<class T>
Node<T> *AVLRankTree<T>::deleteNode(T data)
{
    Node<T> *deletedNode;
    deletedNode = deleteNodeHelper(root, data);
    return deletedNode;
}

template<class T>
void AVLRankTree<T>::clearHelper(Node<T> *node)
{
    if (node != NULL)
    {
        delete node;         // Delete this node
    }
}

template<class T>
int AVLRankTree<T>::max(int x, int y)
{
    if (x > y)
    {
        return x;
    }
    else
    {
        return y;
    }
}

template<class T>
int AVLRankTree<T>::getHeight(Node<T> *node)
{
    if (!node)
    {
        return -1;
    }
    return max(getHeight(node->left), getHeight(node->right)) + 1;

}

template<class T>
int AVLRankTree<T>::getBalanceFactor(Node<T> *node)
{
    return getHeight(node->left) - getHeight(node->right);
}

template<class T>
Node<T> *AVLRankTree<T>::updateBalance(Node<T> *node)
{
    if (!node)
    {
        return nullptr;
    }

    node->balance_factor = getBalanceFactor(node);
    if (node->balance_factor < -1 || node->balance_factor > 1)
    {
        return rebalanceAfterDelete(node);
    }
    else
    {
        node->right_rank = 1;
        node->real_rank = 1;
        if (node->left)
        {
            node->real_rank += node->left->real_rank;
        }

        if (node->right)
        {
            node->real_rank += node->right->real_rank;
            node->right_rank += node->right->real_rank;
        }
    }
    return node;
}

template<class T>
Node<T> *AVLRankTree<T>::rebalanceAfterDelete(Node<T> *node)
{
    //LL
    if (node->balance_factor > 1 && node->left->balance_factor >= 0)
    {
        return rightRotate(node);
    }
        //LR
    else if (node->balance_factor > 1 && node->left->balance_factor < 0)
    {
        leftRotate(node->left);
        return rightRotate(node);
    }
        // Right Right Case
    else if (node->balance_factor < -1 && node->right->balance_factor <= 0)
    {
        return leftRotate(node);
    }
        // Right Left Case
    else if (node->balance_factor < -1 && node->right->balance_factor > 0)
    {
        rightRotate(node->right);
        return leftRotate(node);
    }
    return nullptr;
}

template<class T>
T *AVLRankTree<T>::GetData(Node<T> *node)
{
    return node->data;
}

template<class T>
T AVLRankTree<T>::findIthMax(int i, int total)
{
    Node<T> *current = root;
    Node<T> *result = FindIthHelper(current, i);
    if (!result)
    {
        throw TooManyClasses();
    }
    return result->data;

}

template<class T>
Node<T> *AVLRankTree<T>::minimumNode(Node<T> *node)
{
    Node<T> *current = node;
    while (current && current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}

template<class T>
Node<T> *AVLRankTree<T>::FindIthHelper(Node<T> *node, int i)
{
    if (i == node->right_rank)
    {
        return node;
    }
    else if (i > node->right_rank)
    {
        i = i - node->right_rank;
        return FindIthHelper(node->left, i);
    }
    else
    {
        return FindIthHelper(node->right, i);
    }
}

#endif //AVLRANKTREE_H
