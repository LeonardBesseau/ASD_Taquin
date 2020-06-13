//
// Created by leonard on 6/12/20.
//

#ifndef TAQUIN_GRAPH_H
#define TAQUIN_GRAPH_H

#include <string>
#include <vector>



class Graph{
    std::string data;
public:
    const std::string &getData() const;

private:
    int nbLines;
    const Graph* parent;
    int nullPos;
    int swap;
    size_t g;
public:
    size_t getG() const;

    void setG(size_t g);

    size_t getH() const;

    void setH(size_t h);

    size_t getF() const;

    void setF(size_t f);

private:
    size_t h;
    size_t f;
    size_t getNullPos(const std::string& data);
public:
    Graph(std::string data, int nbLines,const Graph* parent, size_t g,int swap =-1);
    size_t size() const;

    size_t heuristic();

    std::vector<Graph> adjacent(int pos) const;
    std::vector<Graph> adjacent() const;

    bool operator==(const Graph &rhs) const;

    bool operator!=(const Graph &rhs) const;

    bool operator<(const Graph &rhs) const;

    bool operator>(const Graph &rhs) const;

    bool operator<=(const Graph &rhs) const;

    bool operator>=(const Graph &rhs) const;

    static bool compareCost(const  Graph&a, const Graph&b);

    std::string displayParent();
};

Graph::Graph(std::string data, int nbLines,const Graph* parent, size_t g, int swap) : data(std::move(data)), nbLines(nbLines), parent(parent), g(g), swap(swap){
    nullPos = getNullPos(this->data);
    h = heuristic();
    f = g+h;
}

size_t Graph::size() const {
    return nbLines*nbLines;
}


std::vector<Graph> Graph::adjacent(int pos) const{
    std::vector<Graph> output;
    int size = nbLines * nbLines;
    // LEFT
    if (pos % nbLines - 1 >= 0) {
        std::string tmp(data);
        std::swap(tmp[pos], tmp[pos - 1]);
        output.emplace_back(tmp, nbLines, this, g+1, pos-1);

    }
    // UP
    if (pos - nbLines >= 0) {
        std::string tmp(data);
        std::swap(tmp[pos], tmp[pos - nbLines]);
        output.emplace_back(tmp, nbLines, this, g+1, pos-nbLines);
    }
    // Right
    if ((pos + 1) % nbLines) {
        std::string tmp(data);
        std::swap(tmp[pos], tmp[pos + 1]);
        output.emplace_back(tmp, nbLines, this, g+1, pos+1);
    }
    // DOWN
    if (pos + nbLines < size) {
        std::string tmp(data);
        std::swap(tmp[pos], tmp[pos + nbLines]);
        output.emplace_back(tmp, nbLines, this, g+1, pos+nbLines);
    }

    return output;
}

size_t Graph::getNullPos(const std::string &data) {
    size_t output = data.find('0');
    if(output == std::string::npos){
        throw std::invalid_argument("");
    }
    return output;
}

size_t Graph::heuristic() {
    size_t cost = 0;
    for (int i = 0; i < data.size(); i++) {
        int v = data[i]-'0';
        if (!v){
            continue;
        }
        int gx = v%nbLines;
        int gy = v/nbLines;
        int x = i %nbLines;
        int y = i / nbLines;

        cost+= abs(x-gx)+abs(y-gy);
    }
    return cost;
}

size_t Graph::getG() const {
    return g;
}

void Graph::setG(size_t g) {
    Graph::g = g;
}

size_t Graph::getH() const {
    return h;
}

void Graph::setH(size_t h) {
    Graph::h = h;
}

size_t Graph::getF() const {
    return f;
}

void Graph::setF(size_t f) {
    Graph::f = f;
}

const std::string &Graph::getData() const {
    return data;
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
    return a.f < b.f;
}

std::vector<Graph> Graph::adjacent() const {
    return adjacent(nullPos);
}

std::string Graph::displayParent() {
    std::string out;
    const Graph* p = this;
    while (p != nullptr){
        if (p->swap!= -1){
            out+= std::to_string(p->swap);
        }
        std::cout << p->data <<" "<<p->swap<< std::endl;
        p = p->parent;
    }
    return out;
}

#endif //TAQUIN_GRAPH_H
