#ifndef ClassGrapgNode_h
#define ClassGrapgNode_h

#include <iostream>
#include <list>

using namespace std;

template<typename T>
struct Node
{
    T data;
    list<Node<T> *> neighbours;
};

template<typename T>
class Graph
{
private:
    int Size;
    list<Node<T> *> LIST;
    
    void buildEulerLoop();
    
    bool hasItRibs(T prevdata, Node<T> * el, vector<vector<T> *> * check);
    bool hasDataInList(T el);
    bool hasNeighboursList(vector<T> neighbours);
    bool hasElInvector(T el, list<Node<T>*> neighbours);
    bool hasInVector(vector<T> *arr, vector<vector<T> *> * check);
    
    bool unicalNeighbours(T el, vector<T> *neighbours);
    
    int getStartIndex();
    
    Node<T> * findNode(T el);
    vector<vector<int> *> * buildMatrixAdjacency();
    
public:
    Graph();
    void addNode(T el);
    void addNode(T el, vector<T> neighbours);
    
    void deleteNode(T el);
    void clear();
    
    void connectNode(T el, vector<T> neighbours);
    void showTable();
    void showMatrixAdjacency();
    void EulerLoop();
    
    void showRibs();
    
    int getSize();
    int getCountOfRibs();
    
    vector<T> * getVectorData();
    bool hasSeparates();
};

#endif
