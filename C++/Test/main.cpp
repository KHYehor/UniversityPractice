#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "/Applications/github/DSLabs-Tasks/LAB3/LAB3/ClassGrapgNode.h"
#include "/Applications/github/DSLabs-Tasks/LAB3/LAB3/bool:intMethods.h"
#include "/Applications/github/DSLabs-Tasks/LAB3/LAB3/voidMethods.h"

#include "doctest.h"

using namespace std;

TEST_CASE("Graph initialization.")
{
    Graph<int> GraphInt;
    Graph<string> GraphString;
    Graph<float> GraphFloat;
    CHECK(GraphInt.getSize() == 0);
    CHECK(GraphFloat.getSize() == 0);
    CHECK(GraphString.getSize() == 0);
}

TEST_CASE("Graph adding new el.")
{
    Graph<int> GraphInt;
    for (int i = 0; i < 100; i++) GraphInt.addNode(i * i);
    CHECK(GraphInt.getSize() == 100);
    GraphInt.addNode(40, vector<int> {10, 20, 45});
    GraphInt.addNode(200);
    GraphInt.addNode(300);
    GraphInt.addNode(500, vector<int> {200, 300});
    CHECK(GraphInt.getSize() == 103);
}

TEST_CASE("Graph connecting elements.")
{
    Graph<int> GraphInt;
    for (int i = 0; i < 49; i++) GraphInt.addNode(i);
    for (int i = 0; i < 49; i++) for (int j = 0; j < 49; j++) if (i != j) GraphInt.connectNode(i, vector<int> {j});
    GraphInt.showMatrixAdjacency();
//    GraphInt.EulerLoop();
}

TEST_CASE("Graph deleting elements.")
{
    Graph<int> GraphInt;
    GraphInt.deleteNode(100);
    for (int i = 0; i < 50; i++) GraphInt.addNode(i);
    for (int i = 0; i < 50; i++) for (int j = 0; j < 50; j++) if (i != j) GraphInt.connectNode(i, vector<int> {j});
    for (int i = 0; i < 50; i++) GraphInt.deleteNode(i);
    CHECK(GraphInt.getSize() == 0);
}

TEST_CASE("Graph getting size.")
{
    Graph<int> GraphInt;
    CHECK(GraphInt.getSize() == 0);
    for (int i = 0; i < 50; i++) GraphInt.addNode(i);
    CHECK(GraphInt.getSize() == 50);
}

TEST_CASE("Graph getting count of ribs.")
{
    Graph<int> GraphInt;
    for (int i = 0; i < 5; i++) GraphInt.addNode(i);
    for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) if (i != j) GraphInt.connectNode(i, vector<int> {j});
    CHECK(GraphInt.getCountOfRibs() == 11);
}

TEST_CASE("Graph clearing.")
{
    Graph<int> GraphInt;
    for (int i = 0; i < 5; i++) GraphInt.addNode(i);
    for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) if (i != j) GraphInt.connectNode(i, vector<int> {j});
    GraphInt.clear();
    CHECK(GraphInt.getSize() == 0);
}

TEST_CASE("Graph get vector of Data.")
{
    Graph<int> GraphInt;
    vector<int> data1 {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < 10; i++) GraphInt.addNode(i);
    vector<int> *data2 = GraphInt.getVectorData();
    for (int i = 0; i < 10; i++) CHECK((*data2)[i] == data1[i]);

}

TEST_CASE("Has Graph separates nodes.")
{
    Graph<int> GraphInt;
    for (int i = 0; i < 5; i++) GraphInt.addNode(i);
    CHECK(GraphInt.hasSeparates() == 1);
}

TEST_CASE("Graph Euler Loop Test.")
{
    Graph<int> GraphInt1;
    GraphInt1.addNode(10);
    GraphInt1.addNode(20);
    GraphInt1.addNode(30);
    GraphInt1.addNode(40);
    GraphInt1.connectNode(10, vector<int> {20, 30, 40});
    GraphInt1.connectNode(20, vector<int> {30});
    GraphInt1.connectNode(30, vector<int> {40});
    cout << "GraphInt1" << endl;
    GraphInt1.EulerLoop();

    Graph<int> GraphInt2;
    GraphInt2.EulerLoop();
    GraphInt2.addNode(1);
    GraphInt2.addNode(2);
    GraphInt2.addNode(3);
    GraphInt2.addNode(3);
    GraphInt2.addNode(4);
    GraphInt2.addNode(5);
    GraphInt2.connectNode(1, vector<int> {2, 5});
    GraphInt2.connectNode(2, vector<int> {3, 4, 5});
    GraphInt2.connectNode(3, vector<int> {4});
    cout << "GraphInt2" << endl;
    GraphInt2.EulerLoop();

    Graph<int> GraphInt3;
    GraphInt3.addNode(1);
    GraphInt3.addNode(2);
    GraphInt3.addNode(3);
    GraphInt3.addNode(4);
    GraphInt3.addNode(5);
    GraphInt3.connectNode(1, vector<int> {2});
    GraphInt3.connectNode(2, vector<int> {3, 4});
    GraphInt3.connectNode(3, vector<int> {4});
    GraphInt3.connectNode(4, vector<int> {5});
    cout << "GraphInt3" << endl;
    GraphInt3.EulerLoop();
    
    Graph<int> GraphInt4;
    for (int i = 0; i < 19; i++) GraphInt4.addNode(i);
    for (int i = 0; i < 19; i++) for (int j = 0; j < 19; j++) if (i != j) GraphInt4.connectNode(i, vector<int> {j});
    GraphInt4.EulerLoop();
}
