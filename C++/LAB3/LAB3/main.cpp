#include <iostream>
#include <vector>
#include <string>

#include "ClassGrapgNode.h"
#include "bool:intMethods.h"
#include "voidMethods.h"

using namespace std;

int main()
{
    Graph<int> numbers;
    numbers.addNode(10);
    numbers.addNode(20);
    numbers.addNode(30);
    numbers.addNode(40);
    numbers.addNode(50);
    numbers.connectNode(10, vector<int> {20, 30, 50});
    numbers.connectNode(20, vector<int> {30});
    numbers.connectNode(30, vector<int> {40});
    numbers.connectNode(40, vector<int> {50});
    numbers.connectNode(40, vector<int> {50});
    numbers.connectNode(30, vector<int> {20});
    numbers.showTable();
    numbers.showMatrixAdjacency();
    numbers.EulerLoop();
}

