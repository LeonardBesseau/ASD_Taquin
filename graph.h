//
// Created by leonard on 6/12/20.
//

#ifndef TAQUIN_GRAPH_H
#define TAQUIN_GRAPH_H

#include <string>
#include <vector>
#include <sstream>
#include <cmath>


class Graph {
    std::vector<int> data;
    int nbLines;
    const Graph *parent;
    int nullPos;
    size_t g;
    size_t h;
    size_t f;

    static size_t getNullPos(const std::vector<int> &v);

    std::vector<Graph> adjacent(int pos) const;



public:
    size_t getH() const;

    Graph(const std::string &data, const Graph *parent, size_t g);

    Graph(std::vector<int> data, int nbLines, const Graph *parent, size_t g, int nullPos);


    static std::vector<int> transformIntoIntVector(const std::string &data);

    size_t heuristic();


    std::vector<Graph> adjacent() const;

    bool operator==(const Graph &rhs) const;

    bool operator!=(const Graph &rhs) const;

    bool operator<(const Graph &rhs) const;

    bool operator>(const Graph &rhs) const;

    bool operator<=(const Graph &rhs) const;

    bool operator>=(const Graph &rhs) const;

    static bool compareCost(const Graph &a, const Graph &b);

    std::string displayParent(size_t &length);
};


#endif //TAQUIN_GRAPH_H
