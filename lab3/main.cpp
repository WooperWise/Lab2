#include <iostream>
#include "Graph.h"
#include <string>
#include "crow_all.h"

#define crow_json crow::json::wvalue

using namespace std;

vector<Edge<int>> RandomGraph(int size)
{
   	vector<Edge<int>> e;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++) 
		{
			int weight = rand() % 100;
            int flag = rand() % 3;
            if (flag)
                weight = 0;
            if ((weight != 0) && (i != j))
            {
			    Edge<int> tmp = { i, j, weight };
			    e.push_back(tmp);
            }
            flag--;
		}
	return e;
}

int main()
{
	clock_t start, end;
	string time;
	crow::SimpleApp app;
    int sizeGraph = 0;
    vector<Edge<int>> e_res;

    CROW_ROUTE(app, "/CreateORGraph/<int>")([&](int size) {
        vector<Edge<int>> e = RandomGraph(size);
    if (!e_res.empty()) e_res.clear();
    for (auto& k : e) e_res.push_back(k);
    sizeGraph = size;
    start = clock();
    ORGraph<int> graph(e, size);
    end = clock();
    cout << graph << '\n';
    time = to_string((int)(end - start) / (CLOCKS_PER_SEC / 1000)) + " ms";
    crow_json data;
    crow_json::list from, to, weight, nodes;
    for (int i = 0; i < size; i++) nodes.push_back(to_string(i));
    for (auto k : e)
        if (k.weight != 0)
        {
            from.push_back(k.from);
            to.push_back(k.to);
            weight.push_back(k.weight);
        }
    data["Nodes"] = crow_json(nodes);
    data["From"] = crow_json(from);
    data["To"] = crow_json(to);
    data["Weight"] = crow_json(weight);
    data["Time"] = crow_json::list({ time });
    crow::response ans(data);
    ans.add_header("Access-Control-Allow-Origin", "*");
    return ans;
        });

    CROW_ROUTE(app, "/ORGraphTheBestWay/<int>/<int>")([&](int a, int b) {
        int d = 0;
    start = clock();
    ORGraph<int> graph(e_res, sizeGraph);
    d = graph.theBestWay(a, b);
    end = clock();
    time = to_string((int)(end - start) / (CLOCKS_PER_SEC / 1000)) + " ms";
    crow_json data;
    crow_json::list theBestWay;
    theBestWay.push_back(d);
    data["Time"] = crow_json::list({ time });
    data["TheBestWay"] = crow_json(theBestWay);
    crow::response ans(data);
    ans.add_header("Access-Control-Allow-Origin", "*");
    return ans;
        });
    
    CROW_ROUTE(app, "/ORGraphFindStrongComponents")([&]() {
        vector<vector<int>> d;
    start = clock();
    ORGraph<int> graph(e_res, sizeGraph);
    d = graph.findStrongComponents();
    end = clock();
    time = to_string((int)(end - start) / (CLOCKS_PER_SEC / 1000)) + " ms";
    crow_json data;
    crow_json::list FSC;
    string fsc = " ";
    for (auto& k : d)
    {
        for (auto& h : k)
        {
            string tmp = to_string(h) + " ";
            fsc += tmp;
        }
        FSC.push_back(fsc);
        fsc = " ";
    }
    data["Time"] = crow_json::list({ time });
    data["FSC"] = crow_json(FSC);
    crow::response ans(data);
    ans.add_header("Access-Control-Allow-Origin", "*");
    return ans;
        });

    CROW_ROUTE(app, "/ORGraphInverse")([&]() {
        vector<vector<int>> d;
    start = clock();
    ORGraph<int> graph(e_res, sizeGraph);
    graph.inverse();
    e_res = graph.ArrToEdge();
    end = clock();
    time = to_string((int)(end - start) / (CLOCKS_PER_SEC / 1000)) + " ms";
    crow_json data;
    crow_json::list from, to, weight, nodes;
    for (int i = 0; i < sizeGraph; i++) nodes.push_back(to_string(i));
    data["Nodes"] = crow_json(nodes);
    for (auto& k : e_res)
        if (k.weight != 0)
        {
            from.push_back(k.from);
            to.push_back(k.to);
            weight.push_back(k.weight);
        }
    string fsc = " ";
    data["From"] = crow_json(from);
    data["To"] = crow_json(to);
    data["Weight"] = crow_json(weight);
    data["Time"] = crow_json::list({ time });
    crow::response ans(data);
    ans.add_header("Access-Control-Allow-Origin", "*");
    return ans;
        });

    CROW_ROUTE(app, "/ORGraphNoInverse")([&]() {
        vector<vector<int>> d;
    start = clock();
    ORGraph<int> graph(e_res, sizeGraph);
    graph.inverse();
    e_res = graph.ArrToEdge();
    end = clock();
    time = to_string((int)(end - start) / (CLOCKS_PER_SEC / 1000)) + " ms";
    crow_json data;
    crow_json::list from, to, weight, nodes;
    for (int i = 0; i < sizeGraph; i++) nodes.push_back(to_string(i));
    data["Nodes"] = crow_json(nodes);
    for (auto& k : e_res)
        if (k.weight != 0)
        {
            from.push_back(k.from);
            to.push_back(k.to);
            weight.push_back(k.weight);
        }
    string fsc = " ";
    data["From"] = crow_json(from);
    data["To"] = crow_json(to);
    data["Weight"] = crow_json(weight);
    data["Time"] = crow_json::list({ time });
    crow::response ans(data);
    ans.add_header("Access-Control-Allow-Origin", "*");
    return ans;
        });

    app.port(1337)
        .server_name("CrowCpp")
        .multithreaded()
        .run();
}

