#ifndef methods_h
#define methods_h

#include <iostream>
#include <limits.h>
#include <cassert>
#include <cmath>
#include <list>
#include <queue>

#include "ClassTree.h"

using namespace std;

template<typename T>
BinaryTree<T>::BinaryTree()
{
    root = nullptr;
    Depth = 0;
    Size = 0;
}

template<typename T>
bool BinaryTree<T>::find(T el)
{
    if (root == nullptr)
    {
        cout << "Tree is empty!" << endl;
        return false;
    }
    else
    {
        Node<T> *node = root;
        while (true)
        {
            if (node->data == el) return true;
            else if (node->data > el && node->pleft == nullptr) return false;
            else if (node->data < el && node->pright == nullptr) return false;
            else if (node->data > el) node = node->pleft;
            else if (node->data < el) node = node->pright;
        }
    }
}

template<typename T>
int BinaryTree<T>::min()
{
    Node<T> *node = root;
    while (true) if (node->pleft != nullptr) node = node->pleft; else break;
    return node->data;
}

template<typename T>
int BinaryTree<T>::max()
{
    Node<T> *node = root;
    while (true) if (node->pright != nullptr) node = node->pright; else break;
    return node->data;
}

template<typename T>
int BinaryTree<T>::getSize() { return Size; }

template<typename T>
int BinaryTree<T>::getMaxDepth() { return Depth; }

#endif 
