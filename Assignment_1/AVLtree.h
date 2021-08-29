
#ifndef AVL_AVLTREE_H
#define AVL_AVLTREE_H

#include <iostream>
#include "Course.h"

template<class T>
struct Node
{
    T data;
    Node* left;
    Node* right;
    Node* parent;
    int balance_factor;
    Node() {};
    Node(T data, Node* left, Node* right, Node* parent, int balance_factor);
    ~Node();
};

template<class T>
Node<T>::Node(T data, Node* left, Node* right, Node* parent, int balance_factor) : data(data)
{
    this->left = left;
    this->right = right;
    this->parent = parent;
    this->balance_factor = balance_factor;
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

//template<class T>
//Node<T>::Node(const Node<T> &node)
//{
//    this->data = node.data;
//    if(node.right)
//    {
//        this->right = new Node<T>(node.right);
//    }
//    else
//    {
//        this->right = nullptr;
//    }
//
//    if(node.parent)
//    {
//        this->parent = new Node<T>(node.parent);
//    }
//    else
//    {
//        this->parent = nullptr;
//    }
//
//    if(node.left)
//    {
//        this->left = new Node<T>(node.left);
//    }
//    else
//    {
//        this->left = nullptr;
//    }
//    this->balance_factor = node.balance_factor;
//}

template<class T>
class AVLtree
{
private:
    Node<T>* root;
    Node<T>* max_node;
    Node<T>* min_node;

    void createNode(Node<T>* node, T data);

    void inOrderHelper(Node<T>* node);

    void preOrderHelper(Node<T>* node);

    Node<T>* searchHelper(Node<T>* node, T data);

    Node<T>* deleteNodeHelper(Node<T>* node, T data);

    Node<T>* minimumNode(Node<T>* node);

    Node<T>* maximumNode(Node<T>* node);

    void rebalanceAfterInsert(Node<T>* node);

    Node<T>* rebalanceAfterDelete(Node<T>* node);

    void balanceTree(Node<T>* node);

    Node<T>* updateBalance(Node<T>* node);

    Node<T>* leftRotate(Node<T>* node);

    Node<T>* rightRotate(Node<T>* node);

    void clearHelper(Node<T>* node);

    int getBalanceFactor(Node<T>* node);

    int getHeight(Node<T>* node);

    int max(int x, int y);

public:
    AVLtree(); //c'tor
    AVLtree(const AVLtree& node); //copy c'tor
    ~AVLtree(); //d'tor

    void insert(T insertData);

    Node<T>* deleteNode(T data);

    Node<T>* getMax();

    Node<T>* getMin();

    void inOrder();

    void preOrder();

    Node<T>* search(T wantedData);

    T* GetData(Node<T>* node);

    void searchByMax(Node<T>* node, T* maxArray, int maxIndex, int* index);

    void reverseInOrder(Node<T>* node, T* maxArray, int maxIndex, int* index);

    friend void inOrder(Node<Course>* node, Class* maxArray, int maxIndex, int* index);

    friend void searchByMin(Node<Course>* node, Class* maxArray, int maxIndex, int* index);
};

void inOrder(Node<Course>* node, Class* maxArray, int maxIndex, int* index);

void searchByMin(Node<Course>* node, Class* maxArray, int maxIndex, int* index);

template<class T>
AVLtree<T>::AVLtree()
{
    root = nullptr;
}


template<class T>
AVLtree<T>::AVLtree(const AVLtree& node) : root(node.root)
{

}

template<class T>
AVLtree<T>::~AVLtree()
{
    clearHelper(root);
}

template<class T>
void AVLtree<T>::balanceTree(Node<T>* node)
{
    if (node->balance_factor < -1 || node->balance_factor > 1)
    {
        rebalanceAfterInsert(node);
        return;
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
void AVLtree<T>::insert(T insertData)
{
    Node<T>* node = new Node<T>(insertData, nullptr, nullptr, nullptr, 0);
    Node<T>* y = nullptr;
    Node<T>* x = this->root;

    while (x != nullptr)
    {
        y = x;
        if (node->data < x->data)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
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

    if (!max_node)
    {
        max_node = node;
        min_node = node;
    }
    else if (max_node && max_node->data < insertData)
    {
        max_node = node;
    }
    else if (min_node && min_node->data > insertData)
    {
        min_node = node;
    }

    balanceTree(node);
}

template<class T>
void AVLtree<T>::inOrder()
{
    inOrderHelper(root);
}

template<class T>
void AVLtree<T>::createNode(Node<T>* node, T data)
{
    node->data = data;
    node->parent = nullptr;
    node->left = nullptr;
    node->right = nullptr;
    node->balance_factor = 0;
}

template<class T>
void AVLtree<T>::inOrderHelper(Node<T>* node)
{
    if (node == NULL)
    {
        return;
    }
    inOrderHelper(node->left);
    std::cout << node->data << " ";
    inOrderHelper(node->right);
}

template<class T>
Node<T>* AVLtree<T>::leftRotate(Node<T>* node)
{
    Node<T>* temp = node->right;
    if(temp)
    {
        node->right = temp->left;
    }

    if (temp && temp->left != nullptr)
    {
        temp->left->parent = node;
    }
    if(temp)
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
    else if(node->parent)
    {
        node->parent->right = temp;
    }
    if(temp)
    {
        temp->left = node;
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
Node<T>* AVLtree<T>::rightRotate(Node<T>* node)
{
    Node<T>* temp = node->left;
    node->left = temp->right;

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
void AVLtree<T>::rebalanceAfterInsert(Node<T>* node)
{
    if (node->balance_factor > 0)
    {
//        if (node->right && node->right->balance_factor < 0)
//        {
//            rightRotate(node->right);
//            leftRotate(node);
//        }
//        else
//        {
//            leftRotate(node);
//        }
            if(node->left->balance_factor >= 0)
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
//        if (node->left && node->left->balance_factor > 0)
//        {
//            leftRotate(node->left);
//            rightRotate(node);
//        }
//        else
//        {
//            rightRotate(node);
//        }
        if(node->right->balance_factor <= 0)
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
Node<T>* AVLtree<T>::search(T wantedData)
{
    T temp(wantedData);
    return searchHelper(root, temp);
}

template<class T>
Node<T>* AVLtree<T>::searchHelper(Node<T>* node, T data)
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
Node<T>* AVLtree<T>::deleteNodeHelper(Node<T>* node, T data)
{
    if (node == nullptr)
    {
        return node;
    }
    else if (data < node->data)
    {
        node->left = deleteNodeHelper(node->left, data);
    }
    else if (data > node->data)
    {
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
            else if(node->parent && node->parent->left && node->parent->left->data == node->data)
            {
                node->parent->left = nullptr;
            }
            else if(!node->parent)
            {
                root = nullptr;
            }
            delete node;
            node = nullptr;
        }

        //node has only one son
        else if (node->left == nullptr)
        {
            Node<T>* temp = node;
            node = node->right;
            node->parent = temp->parent;
            temp->right = nullptr;

            if (node->parent && node->parent->right == temp)
            {
                node->parent->right = node;
            }
            else if(node->parent)
            {
                node->parent->left = node;
            }
            else if(temp->data == root->data)
            {
                root = node;
            }

            delete temp;
        }
        else if (node->right == nullptr)
        {
            Node<T>* temp = node;
            node = node->left;
            node->parent = temp->parent;
            temp->left = nullptr;

            if (node->parent && node->parent->right == temp)
            {
                node->parent->right = node;
            }
            else if(node->parent)
            {
                node->parent->left = node;
            }
            else if(temp->data == root->data)
            {
                root = node;
            }

            delete temp;
        }

        //node has two sons
        else
        {
            Node<T>* temp = minimumNode(node->right);
            node->data = temp->data;
            node->right = deleteNodeHelper(node->right, temp->data);
        }
    }

    return updateBalance(node);

   // return node;
}

template<class T>
Node<T>* AVLtree<T>::deleteNode(T data)
{
    Node<T>* deletedNode;
    if (max_node->data == data && !(min_node->data == data))
    {
        deletedNode = deleteNodeHelper(root, data);
        max_node = maximumNode(root);
    }
    else if (min_node->data == data && !(max_node->data == data))
    {
        deletedNode = deleteNodeHelper(root, data);
        min_node = minimumNode(root);
    }
    else if(min_node->data == data && max_node->data == data)
    {
        deletedNode = deleteNodeHelper(root, data);
        min_node = minimumNode(root);
        max_node = maximumNode(root);
    }
    else if(!(max_node->data == data) && !(min_node->data == data))
    {
        deletedNode = deleteNodeHelper(root, data);
        min_node = minimumNode(root);
        max_node = maximumNode(root);
    }

    return deletedNode;
}

template<class T>
Node<T>* AVLtree<T>::minimumNode(Node<T>* node)
{
    Node<T>* current = node;
    while (current && current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}

template<class T>
Node<T>* AVLtree<T>::maximumNode(Node<T>* node)
{
    Node<T>* current = node;
    while (current && current->right != nullptr)
    {
        current = current->right;
    }
    return current;
}

template<class T>
void AVLtree<T>::clearHelper(Node<T>* node)
{
    if (node != NULL)
    {
        //clearHelper(node->left);   // Recursively clear the left sub-tree
        //clearHelper(node->right);   // Recursively clear the right sub-tree
        delete node;         // Delete this node
    }
}

template<class T>
int AVLtree<T>::max(int x, int y)
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
int AVLtree<T>::getHeight(Node<T>* node)
{
    if (!node)
    {
        return -1;
    }
    return max(getHeight(node->left), getHeight(node->right)) + 1;

}

template<class T>
int AVLtree<T>::getBalanceFactor(Node<T>* node)
{
    return getHeight(node->left) - getHeight(node->right);
}

template<class T>
void AVLtree<T>::preOrderHelper(Node<T>* node)
{
    if (node == NULL)
    {
        return;
    }
    std::cout << node->data << " ";
    preOrderHelper(node->left);
    preOrderHelper(node->right);
}

template<class T>
void AVLtree<T>::preOrder()
{
    preOrderHelper(root);
}

template<class T>
Node<T>* AVLtree<T>::updateBalance(Node<T>* node)
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
    return node;
    //updateBalance(node->parent);
}

template<class T>
Node<T>* AVLtree<T>::rebalanceAfterDelete(Node<T>* node)
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
T* AVLtree<T>::GetData(Node<T>* node)
{
    return node->data;
}

template<class T>
void AVLtree<T>::reverseInOrder(Node<T>* node, T* maxArray, int maxIndex, int* index)
{
    if (node == NULL || maxIndex <= *index)
    {
        return;
    }
    reverseInOrder(node->right, maxArray, maxIndex, index);
    if (maxIndex > *index)
    {
        maxArray[*index] = node->data;
        (*index)++;
    }
    else
    {
        return;
    }
    reverseInOrder(node->left, maxArray, maxIndex, index);
}

template<class T>
void AVLtree<T>::searchByMax(Node<T>* node, T* maxArray, int maxIndex, int* index)
{
    if (maxIndex > *index)
    {
        maxArray[*index] = node->data;
        (*index)++;
    }
    else
    {
        return;
    }

    if (node->left)
    {
        reverseInOrder(node->left, maxArray, maxIndex, index);
    }

    if (node->parent)
    {
        searchByMax(node->parent, maxArray, maxIndex, index);
    }
}


template<class T>
Node<T>* AVLtree<T>::getMax()
{
    if (max_node)
    {
        return max_node;
    }
    return nullptr;
}

template<class T>
Node<T>* AVLtree<T>::getMin()
{
    if (min_node)
    {
        return min_node;
    }
    return nullptr;
}

#endif
