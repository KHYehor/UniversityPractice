#ifndef voidmethods_h
#define voidmethods_h

#include "ClassTree.h"

template<typename T>
void BinaryTree<T>::fixdepth(Node<T> *node)
{
    node->depth--;
    if (node->pleft != nullptr) fixdepth(node->pleft);
    if (node->pright != nullptr) fixdepth(node->pright);
}

template<typename T>
void BinaryTree<T>::fixmaxdepthhelper(Node<T> *node, int *checkdepth)
{
    if (*checkdepth <= node->depth) *checkdepth = node->depth;
    if (node->pleft != nullptr) fixmaxdepthhelper(node->pleft, checkdepth);
    if (node->pright != nullptr) fixmaxdepthhelper(node->pright, checkdepth);
}

template<typename T>
void BinaryTree<T>::fixmaxdepth()
{
    Node<T> *node = root;
    int *checkdepth = new int(0);
    fixmaxdepthhelper(node, checkdepth);
    if (*checkdepth < Depth) Depth--;
}



template<typename T>
void BinaryTree<T>::delhelper(Node<T> *node, T el)
{
    if (node->data != el)
    {
        if (node->pleft != nullptr) delhelper(node->pleft, el);
        if (node->pright != nullptr) delhelper(node->pright, el);
    }
    else
    {
        if (node->pleft == nullptr && node->pright == nullptr && node->parent == nullptr) root = nullptr;
        else if (node->pleft == nullptr && node->pright == nullptr)
        {
            node = node->parent;
            if (node->pleft != nullptr && node->pleft->data == el) node->pleft = nullptr;
            else node->pright = nullptr;
            fixmaxdepth();
        }
        else if (node->pleft != nullptr && node->pright == nullptr)
        {
            Node<T> *tmp = node->pleft;
            if (node->parent == nullptr)
            {
                root = node->pleft;
                root->parent = nullptr;
            } else {
                node = node->parent;
                if (node->pleft->data == el) node->pleft = tmp;
                else node->pright = tmp;
                fixdepth(tmp);
                fixmaxdepth();
            }
        }
        else if (node->pright != nullptr)
        {
            Node<T> *temp = node->pright;
            while (temp->pleft != nullptr) temp = temp->pleft;
            node->data = temp->data;
            if (node->pright == temp) node->pright = nullptr;
            else
            {
                temp = temp->parent;
                if (temp->pleft->pright == nullptr) temp->pleft = nullptr;
                else
                {
                    temp->pleft = temp->pleft->pright;
                    temp->pleft->parent = nullptr;
                    temp->pleft->parent = temp;
                    fixdepth(temp->pleft);
                }
                fixmaxdepth();
            }
        }
    }
}

template<typename T>
void BinaryTree<T>::delel(T el)
{
    Node<T> *node = root;
    if (node != nullptr && find(el)) {
        delhelper(node, el);
        Size--;
    }
    else if (!find(el)) cout << "Tree does not have this el." << endl;
    else if (node == nullptr) cout << "Tree is empty!" << endl;
}

template<typename T>
void BinaryTree<T>::push(T el)
{
    if (root == nullptr)
    {
        root = new Node<T>;
        root->data = el;
        root->depth = 0;
        root->pleft = nullptr;
        root->pright = nullptr;
        root->parent = nullptr;
        Size++;
    }
    else
    {
        Node<T> *cur = root;
        int checkdepth = 0;
        
        Node<T> *pushed = new Node<T>;
        pushed->data = el;
        pushed->pleft = nullptr;
        pushed->pright = nullptr;
        
        while (true)
        {
            if (cur->data == el)
            {
                cout << "Tree has already this " << cur->data << " el." << endl;
                break;
            }
            else if (cur->data > el && cur->pleft == nullptr)
            {
                pushed->depth = ++checkdepth;
                cur->pleft = pushed;
                cur->pleft->parent = cur;
                if (Depth < checkdepth) Depth = checkdepth;
                Size++;
                break;
            }
            else if (cur->data > el)
            {
                cur = cur->pleft;
                checkdepth++;
            }
            else if (cur->data < el && cur->pright == nullptr)
            {
                pushed->depth = ++checkdepth;
                cur->pright = pushed;
                cur->pright->parent = cur;
                if (Depth < checkdepth) Depth = checkdepth;
                Size++;
                break;
            }
            else if (cur->data < el)
            {
                cur = cur->pright;
                checkdepth++;
            }
        }
    }
}

template<typename T>
void BinaryTree<T>::depthhelper(Node<T> *node, const int depth)
{
    if (node->depth == depth) cout << node->data << " ";
    if (node->pleft != nullptr) depthhelper(node->pleft, depth);
    if (node->pright != nullptr) depthhelper(node->pright, depth);
}

template<typename T>
void BinaryTree<T>::showdepth(const int depth)
{
    Node<T> *node = root;
    if (node != nullptr) depthhelper(node, depth);
    else cout << "Tree is empty!" << endl;
    cout << "\n";
}

template<typename T>
void BinaryTree<T>::showTree()
{
    if (root == nullptr) cout << "Tree is empty!" << endl;
    else
    {
        cout << "\nTree:\n" << endl;
        for (int i = 0; i <= Depth; i++)
        {
            cout << "\nTree depth: " << i << ".\n"<<endl;
            showdepth(i);
        }
    }
    cout << "\nTree size: " << Size << "." << endl;
    cout << "Max depth: " << Depth << ".\n" << endl;
}

template<typename T>
void BinaryTree<T>::clearhelper(Node<T> *node)
{
    if (node->pleft == nullptr && node->pright ==  nullptr)
    {
        if (node->parent == nullptr) root = nullptr;
        else
        {
            int tmp = node->data;
            node = node->parent;
            if (node->pleft != nullptr && node->pleft->data == tmp) node->pleft = nullptr;
            if (node->pright != nullptr && node->pright->data == tmp) node->pright = nullptr;
            clearhelper(node);
        }
        
    }
    else
    {
        if (node->pleft != nullptr) clearhelper(node->pleft);
        if (node->pright != nullptr) clearhelper(node->pright);
    }
}

template<typename T>
void BinaryTree<T>::clear()
{
    if (root == nullptr) cout << "Tree is empty" << endl;
    else
    {
        Node<T> *node = root;
        clearhelper(node);
        Depth = 0;
        Size = 0;
    }
}

template<typename T>
void averagehelper(Node<T> *node, list<T> *list)
{
    list->push_back(node->data);
    if (node->pleft != nullptr) averagehelper(node->pleft, list);
    if (node->pright != nullptr) averagehelper(node->pright, list);
}

template<typename T>
void BinaryTree<T>::average()
{
    if (root == nullptr) cout << "Tree is empty!" << endl;
    else
    {
        Node<T> *node = root;
        list<T> *list = new std::list<T>;
        int result = 0;
        averagehelper(node, list);
        for (auto i = list->begin(); i != list->end(); i++) result += *i;
        push(result/Size);
        cout << "\naverage el: " << result/Size << ".\n" << endl;
    }

}

#endif 
