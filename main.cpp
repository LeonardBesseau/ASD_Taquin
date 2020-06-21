#include <iostream>
#include <set>
#include <list>
#include <queue>
#include <chrono>

#include "graph.h"


class Compare {
public:
    bool operator()(const Graph &a, const Graph &b) {
        return Graph::compareCost(a, b);
    }
};

std::string AStart(const std::string &input) {
    Graph start(input, nullptr, 0);
    std::priority_queue<Graph, std::vector<Graph>, Compare> open;
    std::set<Graph> endList;
    open.push(start);
    std::string sol;
    size_t solutionSize = 0;
    size_t createdNodes = 0;
    while (!open.empty()) {
        Graph current = open.top();
        open.pop();

        auto test = endList.insert(current);
        if (!test.second) {
            continue;
        }

        if (!current.getH()) {
            sol = current.displayParent(solutionSize);
            break;
        }

        for (const auto &adj : (*test.first).adjacent()) {
            ++createdNodes;
            open.emplace(adj);
        }
    }
    std::cout << "Solution size\t: " << solutionSize << std::endl
              << "Created nodes\t: " << createdNodes << " : " << createdNodes * sizeof(Graph) / 1000 << " KB"
              << std::endl
              << "Explored nodes\t: " << endList.size() << std::endl;
    return sol;
}


int main() {
    std::string input = "4 3 7 2 10 1 5 11 8 12 6 15 14 13 0 9";
    auto t1 = std::chrono::high_resolution_clock::now();
    std::string sol = AStart(input);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << sol << std::endl << duration<<" ms" ;
    return 0;
}
