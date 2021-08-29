#include "AVLtree.h"

void inOrder(Node<Course>* node, Class* maxArray, int maxIndex, int* index)
{
    if (node == NULL)
    {
        return;
    }
    inOrder(node->left, maxArray, maxIndex, index);

    for (int i = 0; i < node->data.getNumOfClasses(); i++)
    {
        Class temp = node->data.getClass(i);
        if (temp.getTime() == 0 && maxIndex > *index)
        {
            maxArray[*index] = Class(temp);
            (*index)++;
        }
        if (maxIndex <= *index)
        {
            return;
        }
    }

    inOrder(node->right, maxArray, maxIndex, index);
}

void searchByMin(Node<Course>* node, Class* maxArray, int maxIndex, int* index)
{
    for (int i = 0; i < node->data.getNumOfClasses(); i++)
    {
        Class temp = node->data.getClass(i);
        if (temp.getTime() == 0 && maxIndex > *index)
        {
            maxArray[*index] = Class(temp);
            (*index)++;
        }
        if (maxIndex <= *index)
        {
            return;
        }
    }

    if (node->right)
    {
        inOrder(node->right, maxArray, maxIndex, index);
    }

    if (node->parent)
    {
        searchByMin(node->parent, maxArray, maxIndex, index);
    }
}