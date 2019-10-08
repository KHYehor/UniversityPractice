#ifndef ClassTree_h
#define ClassTree_h

template<typename T>
struct Node
{
    T data;
    int depth;
    Node *pleft;
    Node *pright;
    Node *parent;
};

template<typename T>
class BinaryTree
{
private:
    Node<T> *root;
    int Depth;
    int Size;
    
    void fixdepth(Node<T> *node);
    void fixmaxdepth();
    void delhelper(Node<T> *node, T el);
    void showdepth(int depth);
    void clearhelper(Node<T> *node);
    void fixmaxdepthhelper(Node<T> *node, int *checkdepth);
    void depthhelper(Node<T> *node, const int depth);
public:
    BinaryTree();
    
    void push(T el);
    
    void delel(T el);
    
    void showTree();
        
    void clear();
    
    void average();
    bool find(T el);
    
    int min();
    int max();
    
    int getSize();
    int getMaxDepth();
};

#endif
