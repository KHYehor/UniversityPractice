#ifndef bool_intMethods_h
#define bool_intMethods_h

#include <iostream>
#include <vector>
#include "ClassGrapgNode.h"

template<typename T>
int Graph<T>::getSize() { return Size; }

template<typename T>
int Graph<T>::getCountOfRibs()
{
    vector<vector<int> *> * matrix = buildMatrixAdjacency();
    int ribs = 0;
    for (auto i = matrix->begin(); i != matrix->end(); i++) for (auto j = (*i)->begin(); j != (*i)->end(); j++) if (*j == 1) ribs++;
    return (ribs / 2 + 1);
}

template<typename T>
int Graph<T>::getStartIndex()
{
    int counter = 0;
    int index = 0;
    vector<vector<int> *> * matrix = buildMatrixAdjacency();
    for (auto i = matrix->begin(); i != matrix->end(); i++)
    {
        int power = 0;
        for(auto j = (*i)->begin(); j != (*i)->end(); j++) if (*j == 1) power++;
        counter++;
        if (power % 2 == 1) index = counter;
    }
    if (index == 0) return index;
    else return (index - 1);
}

template<typename T>
Node<T> * Graph<T>::findNode(T el)
{
    for (auto i = LIST.begin(); i != LIST.end(); i++) if ((*i)->data == el) return *i;
    return new Node<T>;
}

template<typename T>
vector<vector<int> *> * Graph<T>::buildMatrixAdjacency()
{
    vector<vector<int> *> * matrixAdjacency = new vector<vector<int> *>;
    for (auto i = LIST.begin(); i != LIST.end(); i++)
    {
        vector<int> *adjacency = new vector<int>;
        for (auto j = LIST.begin(); j != LIST.end(); j++)
        {
            if (hasElInvector( (*i)->data, (*j)->neighbours) ) adjacency->push_back(1);
            else adjacency->push_back(0);
        }
        matrixAdjacency->push_back(adjacency);
    }
    return matrixAdjacency;
}

template<typename T>
vector<T> * Graph<T>::getVectorData()
{
    vector<T> * data = new vector<T>;
    for (auto i = LIST.begin(); i != LIST.end(); i++) data->push_back((*i)->data);
    return data;
}

template<typename T>
bool Graph<T>::hasNeighboursList(vector<T> neighbours)
{
    int i = 0;
    for (auto j = neighbours.begin(); j != neighbours.end(); j++) if (!hasDataInList(*j)) i++;
    if (i == neighbours.size()) return true;
    else return false;
}

template<typename T>
bool Graph<T>::hasDataInList(T el)
{
    for (auto i = LIST.begin(); i != LIST.end(); i++) if ((*i)->data == el) return true;
    return false;
}

template<typename T>
bool Graph<T>::hasElInvector(T el, list<Node<T>*> neighbours)
{
    for (auto i = neighbours.begin(); i != neighbours.end(); i++) if ((*i)->data == el) return true;
    return false;
}

template<typename T>
bool Graph<T>::hasInVector(vector<T> *arr, vector<vector<T> *> * check)
{
    for (auto i = check->begin(); i != check->end(); i++) if ((*arr)[0] == (*(*i))[0] && (*arr)[1] == (*(*i))[1]) return true;
    return false;
}

template<typename T>
bool Graph<T>::hasSeparates()
{
    for (auto i = LIST.begin(); i != LIST.end(); i++) if ((*i)->neighbours.size() == 0) return true;
    return false;
}

template<typename T>
bool Graph<T>::hasItRibs(T prevdata, Node<T> * node, vector<vector<T> *> * check)
{
    vector<T> * rib = nullptr;
    vector<T> * tmp = nullptr;
    if (prevdata > node->data) tmp = new vector<T> {node->data, prevdata};
    else tmp = new vector<T> {prevdata, node->data};
    check->push_back(tmp);
    for (auto i = node->neighbours.begin(); i != node->neighbours.end(); i++)
    {
        if (node->data > (*i)->data) rib = new vector<T> {(*i)->data, node->data};
        else rib = new vector<T> {node->data, (*i)->data};
        if (!hasInVector(rib, check))
        {
            check->pop_back();
            return true;
        }
    }
    check->pop_back();
    return false;
}

template<typename T>
bool Graph<T>::unicalNeighbours(T el, vector<T> *neighbours)
{
    for (int i = 0; i < neighbours->size(); i++)
    {
        for (int j = 0; j < neighbours->size(); j++) if ((*neighbours)[i] == (*neighbours)[j] && i != j) return false;
    }
    Node<T> *node = findNode(el);
    for (auto i = node->neighbours.begin(); i != node->neighbours.end(); i++)
    {
        for (auto j = neighbours->begin(); j != neighbours->end(); j++)
        {
            if ((*i)->data == (*j)) return false;
        }
    }
    return true;
}

#endif

