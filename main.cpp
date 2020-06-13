#include <iostream>

#include "graph.h"



#include <set>
#include <list>
#include <queue>
#include <functional>
#include <algorithm>

class Compare
{
public:
    bool operator() (const Graph& a, const Graph& b)
    {
        return Graph::compareCost(a,b);
    }
};



int main() {
    std::string input = "4 7 1 0 2 3 6 8 5";
    Graph start(input, 3, nullptr, 0);
    std::vector<int> end = Graph::transformIntoIntVector("0 1 2 3 4 5 6 7 8");
    std::priority_queue<Graph, std::vector<Graph>, Compare> open;
    std::set<Graph> endList;
    open.push(start);
    std::string sol;
    while (!open.empty()){
        Graph current = open.top();
        open.pop();
        if (current.isEqualTo(end)){
            sol = current.displayParent();
            break;
        }
        auto test =endList.insert(current);
        if (!test.second){
            continue;
        }
        for(const auto& adj : (*test.first).adjacent()){
            open.emplace(adj);
        }
    }
    for (char & i : sol) {
        std::cout << i;
    }
    return 0;
}
