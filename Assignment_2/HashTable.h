#ifndef WET1_HASHTABLE_H
#define WET1_HASHTABLE_H

#include "ListNode.h"
#include "List.h"

#define STARTING_SIZE 10
#define FILL_RATIO 9
#define DOWN_RATIO 3

template<class T>
class HashTable
{
private:
    List<T> **table;
    int arraySize;
    int filledNum;

    int HashFunction(int input) const;

    void CheckandReorganize(int resizeFactor);

public:
    explicit HashTable(int starting_size = STARTING_SIZE);

    ~HashTable();

    void Insert(T *data);

    void Remove(T *data);

    ListNode<T> *Search(T *data) const;
};


template<class T>
HashTable<T>::HashTable(int starting_size) : arraySize(starting_size), filledNum(0)
{
    table = new List<T> *[arraySize]();

    for (int i = 0; i < arraySize; i++)
    {
        table[i] = new List<T>();
    }
}


template<class T>
HashTable<T>::~HashTable()
{
    for (int i = 0; i < arraySize; i++)
    {
        delete table[i];
    }

    delete[] table;
}

template<class T>
int HashTable<T>::HashFunction(int input) const
{
    return (input % this->arraySize);
}

template<class T>
void HashTable<T>::CheckandReorganize(int resizeFactor)
{

    int oldSize = this->arraySize;
    List<T> **newTable = new List<T> *[resizeFactor]();
    this->arraySize = resizeFactor;
    for (int i = 0; i < arraySize; i++)
    {
        newTable[i] = new List<T>();
    }
    for (int i = 0; i < oldSize; i++)
    {
        ListNode<T> *temp = this->table[i]->GetHead();
        while (temp)
        {
            int newHash = HashFunction(temp->GetData()->GetHash());
            T *newData(temp->GetData());
            newTable[newHash]->Insert(newData);
            temp = temp->GetNext();
        }
    }

    for (int i = 0; i < oldSize; i++)
    {
        delete table[i];
    }

    delete[] table;

    this->table = newTable;

}

template<class T>
void HashTable<T>::Insert(T *data)
{
    int hashFuncInput = data->GetHash();
    int hashNum = HashFunction(hashFuncInput);
    List<T> *temp = this->table[hashNum];
    temp->Insert(data);
    this->filledNum++;
    if (filledNum > arraySize * FILL_RATIO)
    {
        CheckandReorganize(this->arraySize*2);
    }
}

template<class T>
void HashTable<T>::Remove(T *data)
{
    int hashFuncInput = data->GetHash();
    int hashNum = HashFunction(hashFuncInput);
    List<T> *temp = this->table[hashNum];
    temp->Remove(data);
    this->filledNum--;
    if (filledNum < arraySize * DOWN_RATIO && filledNum > STARTING_SIZE)
    {
        CheckandReorganize(this->arraySize/2);
    }
}

template<class T>
ListNode<T> *HashTable<T>::Search(T *data) const
{
    int hashFuncInput = data->GetHash();
    int hashNum = HashFunction(hashFuncInput);
    List<T> *temp = this->table[hashNum];
    ListNode<T> *wantedNode = temp->Search(data);
    return wantedNode;
}


#endif
