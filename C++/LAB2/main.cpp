#include <iostream>
#include <limits.h>
#include <cassert>
#include <cmath>
#include <list>

#include "ClassTree.h"
#include "methods.h"
#include "tasks.h"
#include "voidmethods.h"

using namespace std;

int main()
{
    BinaryTree<int> *Numbers = new BinaryTree<int>;
    for (int i = 0; i < 20; i++) Numbers->push(rand() % 198 - 99);
    Numbers->delel(-40);
    Numbers->showTree();
    Numbers->average();
    Numbers->showTree();
}
