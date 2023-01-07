#include "pch.h"
#include "Graph.h"

vector<Edge<int> > arr1 = 
{ 
    {0, 1, 6}, {1, 2, 7}, {2, 0, 5}, {2, 1, 4},
    {3, 2, 10}, {4, 5, 3}, {5, 4, 1}
};
vector<Edge<int> > arr1_inverse =
{
    {1, 0, 6}, {2, 1, 7}, {0, 2, 5}, {1, 2, 4},
    {2, 3, 10}, {5, 4, 3}, {4, 5, 1}
};
vector<vector<int>> arr2 =
{
    {0,6,0,0,0,0}, {0,0,7,0,0,0}, {5,4,0,0,0,0},
    {0,0,10,0,0,0}, {0,0,0,0,0,3}, {0,0,0,0,1,0}
};
vector<vector<int>> arr3 = { {0,1,1}, {4,0,1}, {2,1,0} };
vector<vector<pair<int, int>>> arr =
{ 
    {make_pair(1, 6)}, {make_pair(2, 7)}, {make_pair(0, 5), make_pair(1, 4)},
    {make_pair(2, 10)}, {make_pair(5, 3)}, {make_pair(4, 1)} 
};
ORGraph<int> graph1(arr1, 6), graph2(arr2, 6), graph3(arr3, 3), graph1_inverse(arr1_inverse, 6);
vector<int> way = { 1, 1, 3, 1, 2, 1 };
vector<int> components1 = { 0, 1, 2, 3 };
vector<int> components2 = { 4, 5 };


TEST(TestORGraph, TestList) 
{
    int i = 0;
    for (auto& k : graph1.GetORGraph()) {
        ASSERT_EQ(k[0], arr[i][0]);
        i++;
    }
}

TEST(TestORGraph, TestMatrix)
{
    int i = 0;
    for (auto& k : graph2.GetORGraph()) {
        ASSERT_EQ(k[0], arr[i][0]);
        i++;
    }
}

TEST(TestORGraph, TestTheBestWay)
{
    ASSERT_EQ(graph3.theBestWay(2, 1), way[0]);
    ASSERT_EQ(graph3.theBestWay(0, 2), way[1]);
    ASSERT_EQ(graph3.theBestWay(1, 0), way[2]);
    ASSERT_EQ(graph3.theBestWay(1, 2), way[3]);
    ASSERT_EQ(graph3.theBestWay(2, 0), way[4]);
    ASSERT_EQ(graph3.theBestWay(2, 1), way[5]);
}

TEST(TestORGraph, TestFindStrongComponents)
{
    ASSERT_EQ(graph1.findStrongComponents()[0], components1);
    ASSERT_EQ(graph1.findStrongComponents()[1], components2);
}

TEST(TestORGraph, TestInverse)
{
    graph1.inverse();
    ASSERT_EQ(graph1, graph1_inverse);
}


