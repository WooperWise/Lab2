#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

template <class T>
struct Edge {
        int from;
        int to;
        T weight;
};

template <class T>
class ORGraph {
private:
    vector<vector<pair<int, T>>> arr;   //для представления списков смежности или матрицы инцидентности
    vector<vector<int>> components;     //компоненты сильной связности
    vector<int> countOut;
    vector<bool> visited;
    int size = 0, count = 0, countOfEdge = 0;

public:
    ORGraph(const ORGraph<T>& graph)
    {
        arr = graph.arr;
        components = graph.components;
        countOut = graph.countOut;
        visited = graph.visited;
        size = graph.size;
        count = graph.count;
        countOfEdge = graph.countOfEdge;
    }

    ORGraph<T> operator=(const ORGraph<T>& graph) {
        this->arr = graph.arr;
        this->components = graph.components;
        this->countOut = graph.countOut;
        this->visited = graph.visited;
        this->size = graph.size;
        this->count = graph.count;
        this->countOfEdge = graph.countOfEdge;
        return *this;
    };

    bool operator==(const ORGraph<T>& graph) const {
        if 
        (
            (this->arr == graph.arr) &&
            (this->size == graph.size) &&
            (this->countOfEdge == graph.countOfEdge)
        )
            return 1;
        else return 0;
    };

    ORGraph(const vector<Edge<T>>& edges, int n)    //Инициализация с помощью списка смежности
    {
        size = n;
        countOfEdge = edges.size();
        arr.resize(size);
        countOut.resize(size, 0);
        visited.resize(size, false);
        for (auto& v : edges) {
            arr[v.from].push_back(make_pair(v.to, v.weight));
        }
    }

    ORGraph(const vector<vector<int>>& edges, int n)   //Инициализация с помощью матрицы смежности
    {
        size = n;
        arr.resize(size);
        countOut.resize(size);
        visited.resize(size, false);
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (edges[i][j] != 0)
                {
                    arr[i].push_back(make_pair(j, edges[i][j]));
                    countOfEdge++;
                }
    }

    vector<vector<pair<int, T>>> GetORGraph() const { return arr; }

    void DFS(int vertex)  //Поиск компонент сильной связности
    {
        countOut[vertex] = count++;
        visited[vertex] = true;
        for (auto& k : arr[vertex])
            if (visited[k.first] == false)
                DFS(k.first);
        countOut[vertex] = count++;
    }

    void inverse()  //Инвертирование орграфа
    {
        vector<vector<pair<int, T>>> res(size);
        int i = 0;
        for (auto& v : arr)
        {
            int j = 0;
            for (auto& element : v)
            {
                if (arr[i][j].first + 1 > size)
                    res.resize(arr[i][j].first + 1);
                res[arr[i][j].first].push_back(make_pair(i, arr[i][j].second));
                j++;
            }
            i++;
        }
        arr.clear();
        arr = res;
    }

    vector<Edge<T>> ArrToEdge()
    {
        vector<Edge<T>> e;
        for (int i = 0; i < arr.size(); i++)
            for (int j = 0; j < arr[i].size(); j++)
            {
                Edge<T> tmp = { i, arr[i][j].first, arr[i][j].second };
                e.push_back(tmp);
            }
        return e;
    }

    int  theBestWay(int start, int end)   //Поиск наилучшего пути
    {
        int Inf = INT_MAX;
        vector<int> d(size, Inf);
        d[start] = 0;
        vector<Edge<T>> e = ArrToEdge();
        for (int i = 0; i < size - 1; ++i)
            for (int j = 0; j < countOfEdge; ++j)
                if (d[e[j].from] < Inf)
                    d[e[j].to] = min(d[e[j].to], d[e[j].from] + e[j].weight);
        for (auto& k : d)
            if (k == Inf) k = -1;
        return d[end];
    }

    vector<int>  theBestWay(int start)   //Поиск наилучшего пути
    {
        int Inf = INT_MAX;
        vector<int> d(size, Inf);
        d[start] = 0;
        vector<Edge<T>> e = ArrToEdge();
        for (int i = 0; i < size - 1; ++i)
            for (int j = 0; j < countOfEdge; ++j)
                if (d[e[j].from] < Inf)
                    d[e[j].to] = min(d[e[j].to], d[e[j].from] + e[j].weight);
        for (auto& k : d)
            if (k == Inf) k = -1;
        return d;
    }

    vector<vector<int>> findStrongComponents()
    {
        resetData();
        DFS(0);
        vector<pair<int, int>> dict;
        for (int i = 0; i < countOut.size(); i++)
            dict.emplace_back(make_pair(i, countOut[i]));
        sort(dict.begin(), dict.end(), [&](pair<int, int>& a, pair<int, int>& b) {return a.second > b.second; });
        inverse();
        resetData();
        vector <bool> marked(size);
        for (pair<int, int> v : dict)
        {
            DFS(v.first);
            vector<int> x;
            for (int i = 0; i < visited.size(); i++) {
                if (visited[i] && !marked[i])
                {
                    marked[i] = true;
                    x.push_back(i);
                }
            }
            if (!x.empty())
                components.push_back(x);
        }
        return components;
    }

    void resetData()
    {
        count = 0;
        countOut.clear();
        countOut.resize(size);
        visited.assign(size, false);
    }

    friend ostream& operator<<(ostream& out, const ORGraph<T>& graph) {
        for (int i = 0; i < graph.arr.size(); i++)
        {
            for (pair<int, T> v : graph.arr[i])
                out << "(" << i << ", " << v.first << ", " << v.second << ") ";
            out << endl;
        }
        return out;
    }
};
