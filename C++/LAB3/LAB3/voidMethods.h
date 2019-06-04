
#ifndef voidMethods_h
#define voidMethods_h

#include <iostream>
#include <string>
#include "ClassGrapgNode.h"

using namespace std;

template<typename T>
Graph<T>::Graph() { Size = 0; }

template<typename T>
void Graph<T>::addNode(T el)
{
    if (hasDataInList(el)) cout << "Graph has already this element." << endl;
    else
    {
        Node<T> *node = new Node<T>;
        node->data = el;
        LIST.push_back(node);
        Size++;
    }
}

template<typename T>
void Graph<T>::addNode(T el, vector<T> neighbours)
{
    if (hasDataInList(el)) cout << "Graph has already this element." << endl;
    else if (!unicalNeighbours(neighbours))
    {
        Node<T> *node = new Node<T>;
        node->data = el;
        if (hasNeighboursList(neighbours)) cout << "List does not have the same neighbours." << endl;
        else if (!hasNeighboursList(neighbours))
        {
            LIST.push_back(node);
            for (auto i = neighbours.begin(); i != neighbours.end(); i++)
            {
                Node<T> *Node = findNode(*i);
                Node->neighbours.push_back(node);
                node->neighbours.push_back(Node);
            }
            Size++;
        }
    }
}

template<typename T>
void Graph<T>::connectNode(T el, vector<T> neighbours)
{
    if (!hasDataInList(el)) cout << "Graph does not have this element." << endl;
    else if (unicalNeighbours(el, &neighbours))
    {
        if (hasNeighboursList(neighbours)) cout << "List does not have the same neighbours." << endl;
        else
        {
            Node<T> *node = findNode(el);
            for (auto i = neighbours.begin(); i != neighbours.end(); i++)
            {
                Node<T> *Node = findNode(*i);
                node->neighbours.push_back(Node);
                Node->neighbours.push_back(node);
            }
        }
    }
}

template<typename T>
void Graph<T>::showTable()
{
    if (Size == 0) cout << "Graph is clear!" << endl;
    else
    {
        for (auto i = LIST.begin(); i != LIST.end(); i++)
        {
            cout << (*i)->data << "|";
            for (auto j = (*i)->neighbours.begin(); j != (*i)->neighbours.end(); j++) cout << " " << (*j)->data;
            cout << "\n";
        }
    }
}

template<typename T>
void Graph<T>::deleteNode(T el)
{
    if (!hasDataInList(el)) cout << "Graph does not have this element." << endl;
    else
    {
        Node<T> *node = findNode(el);
        for (auto i = node->neighbours.begin(); i != node->neighbours.end(); i++) (*i)->neighbours.remove(node);
        LIST.remove(node);
        Size--;
    }
}

template<typename T>
void Graph<T>::clear()
{
    for (auto i = LIST.begin(); i != LIST.end(); i++) (*i)->neighbours.clear();
    for (auto i = LIST.begin(); i != LIST.end(); i++) delete (*i);
    Size = 0;
}

template<typename T>
void Graph<T>::showRibs()
{
    int EulerRule = 0;
    for (auto i = LIST.begin(); i != LIST.end(); i++) if ((*i)->data % 2 != 0) EulerRule++;
    if (EulerRule > 2) cout << "Euler cycle is impossible to do." << endl;
    else
    {
        vector<vector<T>> ribs;
        for (auto i = LIST.begin(); i != LIST.end(); i++)
        {
            for (auto j = (*i)->neighbours.begin(); j != (*i)->neighbours.end(); j++)
            {
                if ((*i)->data < (*j)->data) ribs.push_back(vector<T>{(*i)->data, (*j)->data});
            }
        }
        for (int i = 0; i < ribs.size(); i++) cout << "rib - " << ribs[i][0] << "<--->" << ribs[i][1] << endl;
    }
}

template<typename T>
void Graph<T>::showMatrixAdjacency()
{
    vector<vector<int> *> * matrix = buildMatrixAdjacency();
    for (auto i = matrix->begin(); i != matrix->end(); i++)
    {
        cout << "[ ";
        for (auto j = (*i)->begin(); j != (*i)->end(); j++) cout << (*j) << " ";
        cout << "]\n";
    }
}

template<typename T>
void Graph<T>::EulerLoop()
{
    int counter = 0;
    for (auto i = LIST.begin(); i != LIST.end(); i++) if ((*i)->neighbours.size() % 2 == 1) counter++;
    if (counter <= 2 && !hasSeparates() && Size != 0) buildEulerLoop();
    else cout << "Impossible to build Euler Loop." << endl;
}

template<typename T>
void Graph<T>::buildEulerLoop()
{
    Node <T> * startnode = findNode((*getVectorData())[getStartIndex()]);
    vector<vector<T> *> * check = new vector<vector<T> *>;
    vector<T> * loop = new vector<T>;
    vector<int> * rib = nullptr;
    loop->push_back(startnode->data);
    
    for (int i = 0; i < getCountOfRibs(); i++)
    {
        for (auto j = startnode->neighbours.begin(); j != startnode->neighbours.end(); j++)
        {
            
            if (startnode->data > (*j)->data) rib = new vector<T> {(*j)->data, startnode->data};
            else rib = new vector<T> {startnode->data, (*j)->data};
            
            if (!hasInVector(rib, check) && (hasItRibs(startnode->data, *j, check) || (i + 1) == getCountOfRibs()))
            {
                loop->push_back((*j)->data);
                startnode = *j;
                check->push_back(rib);
                break;
            }
        }
    }
    
    for (auto i = 0; i < loop->size(); i++)
    {
        if (i % 20 == 0 && i != 0) cout << "\n--->";
        if ((i + 1) == loop->size()) cout << (*loop)[i] << endl;
        else cout << (*loop)[i] << "--->";
    }
}

#endif
