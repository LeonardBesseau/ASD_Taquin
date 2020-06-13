//
// Created by leonard on 6/12/20.
//

#ifndef TAQUIN_GRAPH_H
#define TAQUIN_GRAPH_H

#include <string>
#include <vector>
#include <sstream>


class Graph {
    std::vector<int> data;

private:
    int nbLines;
    const Graph *parent;
    int nullPos;
    int swap;
    size_t g;
public:

private:
    size_t h;
    size_t f;

    static size_t getNullPos(const std::vector<int>& v);



public:
    Graph(const std::string &data, int nbLines, const Graph *parent, size_t g, int swap = -1);

    Graph(std::vector<int> data, int nbLines, const Graph *parent, size_t g, int nullPos, int swap = -1);

    static std::vector<int> transformIntoIntVector(const std::string & data);

    size_t heuristic();

    std::vector<Graph> adjacent(int pos) const;

    std::vector<Graph> adjacent() const;

    bool operator==(const Graph &rhs) const;

    bool operator!=(const Graph &rhs) const;

    bool operator<(const Graph &rhs) const;

    bool operator>(const Graph &rhs) const;

    bool operator<=(const Graph &rhs) const;

    bool operator>=(const Graph &rhs) const;

    static bool compareCost(const Graph &a, const Graph &b);

    std::string displayParent();

    bool isEqualTo(const std::vector<int>& s);
};

Graph::Graph(const std::string &data, int nbLines, const Graph *parent, size_t g, int swap) : nbLines(nbLines),
                                                                                              parent(parent), g(g),
                                                                                              swap(swap) {
    this->data = transformIntoIntVector(data);
    nullPos = getNullPos(this->data);
    h = heuristic();
    f = g + h;
}

Graph::Graph(std::vector<int> data, int nbLines, const Graph *parent, size_t g, int nullPos, int swap) : data(
        std::move(data)), nbLines(nbLines), parent(parent), g(g), nullPos(nullPos), swap(swap) {
    h = heuristic();
    f = g + h;
}

std::vector<Graph> Graph::adjacent(int pos) const {
    std::vector<Graph> output;
    int size = nbLines * nbLines;
    // LEFT
    if (pos % nbLines - 1 >= 0) {
        std::vector<int> tmp(data);
        std::swap(tmp[pos], tmp[pos - 1]);
        output.emplace_back(tmp, nbLines, this, g + 1, pos-1, pos - 1);

    }
    // UP
    if (pos - nbLines >= 0) {
        std::vector<int> tmp(data);
        std::swap(tmp[pos], tmp[pos - nbLines]);
        output.emplace_back(tmp, nbLines, this, g + 1, pos - nbLines, pos - nbLines);
    }
    // Right
    if ((pos + 1) % nbLines) {
        std::vector<int> tmp(data);
        std::swap(tmp[pos], tmp[pos + 1]);
        output.emplace_back(tmp, nbLines, this, g + 1, pos + 1, pos + 1);
    }
    // DOWN
    if (pos + nbLines < size) {
        std::vector<int> tmp(data);
        std::swap(tmp[pos], tmp[pos + nbLines]);
        output.emplace_back(tmp, nbLines, this, g + 1, pos + nbLines, pos + nbLines);
    }

    return output;
}

size_t Graph::getNullPos(const std::vector<int>& v) {
    for (int i = 0; i < v.size(); ++i) {
        if(v[i] == 0){
            return i;
        }
    }
    throw std::invalid_argument("get null pos");
}

size_t Graph::heuristic() {
    size_t cost = 0;
    for (int i = 0; i < data.size(); i++) {
        int v = data[i];
        if (!v) {
            continue;
        }
        int gx = v % nbLines;
        int gy = v / nbLines;
        int x = i % nbLines;
        int y = i / nbLines;

        cost += abs(x - gx) + abs(y - gy);
    }
    return cost;
}


bool Graph::operator==(const Graph &rhs) const {
    return data == rhs.data;
}

bool Graph::operator!=(const Graph &rhs) const {
    return !(rhs == *this);
}

bool Graph::operator<(const Graph &rhs) const {
    return data < rhs.data;
}

bool Graph::operator>(const Graph &rhs) const {
    return rhs < *this;
}

bool Graph::operator<=(const Graph &rhs) const {
    return !(rhs < *this);
}

bool Graph::operator>=(const Graph &rhs) const {
    return !(*this < rhs);
}

bool Graph::compareCost(const Graph &a, const Graph &b) {
    return a.f > b.f;
}

std::vector<Graph> Graph::adjacent() const {
    return adjacent(nullPos);
}

std::string Graph::displayParent() {
    std::string out;
    const Graph *p = this;
    while (p != nullptr) {
        if (p->swap != -1) {
            out.insert(0,std::to_string(p->swap)+" ");
        }
        p = p->parent;
    }
    return out;
}

std::vector<int> Graph::transformIntoIntVector(const std::string &data) {
    std::stringstream iss(data);
    std::vector<int> out;
    out.reserve(data.size());
    int i;
    while(!iss.eof()){
        iss >> i;
        out.push_back(i);
    }
    return out;
}

bool Graph::isEqualTo(const std::vector<int> &s) {
    if (s.size() != data.size()){
        throw std::invalid_argument("is equal to");
    }
    for (int i = 0; i < data.size(); ++i) {
        if(data[i] != (s[i])){
            return false;
        }
    }
    return true;
}


#endif //TAQUIN_GRAPH_H
