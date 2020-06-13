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
        return !Graph::compareCost(a,b);
    }
};



int main() {
    std::string input = "3 8 1 7 2 0 5 6 4";
    input.erase(remove_if(input.begin(), input.end(), isspace), input.end());
    Graph start(input, 3, nullptr, 0);
    Graph test("012345678", 3, nullptr, 0);
    test.heuristic();
    std::string end = "012345678";
    std::priority_queue<Graph, std::vector<Graph>, Compare> open;
    std::set<Graph> endList;
    open.push(start);
    std::string sol;
    while (!open.empty()){
        Graph current = open.top();
        open.pop();
        if (current.getData() == end){
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
    for (auto i = sol.rbegin(); i != sol.rend();++i) {
        std::cout << *i<<" ";
    }
    return 0;
}
