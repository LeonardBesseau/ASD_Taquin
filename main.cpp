/* ---------------------------
Laboratoire : 12
Fichier : main.cpp
Auteur(s) : Besseau
Date : 21-06-2020

But : Ecrire un programme permettant de générer la séquence la plus courte
      des cases à bouger pour remettre le taquin 3x3 suivant en ordre

Remarque(s) : Complexité en temps 3x3 20 ms (moyenne)
              Complexité en mémoire 3x3 moyenne 200KB max 2200 KB
              4x4 possible mais temps variable selon complexité
              5x5 aussi mais de forte chances de manquer de mémoire avant de trouver une solution
              (utiliser IDA au lieu de A*)

Compilateur : gcc version 7.4.0

--------------------------- */
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
    std::priority_queue<Graph, std::deque<Graph>, Compare> frontier;
    std::set<Graph> explored;
    frontier.push(start);
    std::string sol;
    size_t solutionSize = 0;
    size_t createdNodes = 0;
    while (!frontier.empty()) {
        Graph current = frontier.top();
        frontier.pop();

        auto test = explored.insert(current);
        if (!test.second) {
            continue;
        }

        if (!current.getH()) {
            sol = current.displayParent(solutionSize);
            break;
        }

        for (const auto &adj : (*test.first).adjacent()) {
            ++createdNodes;
            frontier.emplace(adj);
        }
    }
    std::cout << "Solution size\t: " << solutionSize << std::endl
              << "Created nodes\t: " << createdNodes << " : " << createdNodes * sizeof(Graph) / 1000 << " KB"
              << std::endl
              << "Explored nodes\t: " << explored.size() << std::endl;
    return sol;
}



int main() {

    //Input can be given all on one line or separated by \n
    // 8 7 6 0 4 1 2 5 3 : 31 movement for solution (longest possible)
    // 8 0 6 5 4 7 2 3 1 : 31 movement for solution (longest possible)
    std::string input = "8 0 6 5 4 7 2 3 1";
    auto t1 = std::chrono::high_resolution_clock::now();
    std::string sol = AStart(input);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << sol << std::endl << duration<<" ms" ;
    return 0;
}
