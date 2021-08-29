#ifndef WET1_LIST_H
#define WET1_LIST_H

#include "ListNode.h"

template<class T>
class List
{
private:
    ListNode<T> *head;
    int length;

public:
    explicit List();

    ~List();

    ListNode<T> *GetHead();

    int GetLength();

    void Insert(T *data);

    void Remove(T *data);

    ListNode<T> *Search(T *data);
};

template<class T>
List<T>::List() : head(nullptr), length(0) {}


template<class T>
ListNode<T> *List<T>::GetHead()
{
    return this->head;
}

template<class T>
int List<T>::GetLength()
{
    return this->length;
}

template<class T>
void List<T>::Insert(T *data)
{
    ListNode<T> *newNode = new ListNode<T>(data, nullptr);
    ListNode<T> *temp = this->head;
    if (temp == nullptr)
    {
        this->head = newNode;
        this->length++;
    }
    else
    {
        while (temp->GetNext())
        {
            temp = temp->GetNext();
        }
        temp->SetNext(newNode);
        this->length++;
    }

}


template<class T>
ListNode<T> *List<T>::Search(T *data)
{
    ListNode<T> *temp = this->head;
    while (temp != nullptr)
    {
        if (*(temp->GetData()) == *data)
        {
            return temp;
        }
        temp = temp->GetNext();
    }
    return nullptr;

}

template<class T>
void List<T>::Remove(T *data)
{
    if (Search(data) == nullptr)
    {
        return;
    }
    if (*this->head->GetData() == *data)//if its the first node that we are deleting
    {
        ListNode<T> *deleteNode = this->head;
        if (this->head->GetNext())
        {
            ListNode<T> *newHead = this->head->GetNext();
            this->head = newHead;
            delete deleteNode;
        }
        else
        {
            this->head = nullptr;
            delete deleteNode;
        }
    }
    else
    {
        int position = 2;
        ListNode<T> *previous = this->head;
        ListNode<T> *current = this->head->GetNext();
        while (current != nullptr && *current->GetData() != *data)
        {
            previous = current; // need to implement and operator =
            current = current->GetNext();
            position++;
        }
        previous->SetNext(current->GetNext());
        delete current;
    }
    this->length--;
}

template<class T>
List<T>::~List()
{
    ListNode<T> *currentNode = this->head;
    while (currentNode)
    {
        ListNode<T> *nextNode = currentNode->GetNext();
        delete currentNode;
        currentNode = nextNode;
    }

}

#endif
