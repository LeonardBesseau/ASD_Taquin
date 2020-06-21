#include "graph.h"

Graph::Graph(const std::string &data, const Graph *parent, size_t g) : parent(parent), g(g) {
    this->data = transformIntoIntVector(data);
    nbLines = sqrt(this->data.size());
    nullPos = getNullPos(this->data);
    h = heuristic();
    f = g + h;
}

Graph::Graph(std::vector<int> data, int nbLines, const Graph *parent, size_t g, int nullPos) : data(
        std::move(data)), nbLines(nbLines), parent(parent), g(g), nullPos(nullPos) {
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
        output.emplace_back(tmp, nbLines, this, g + 1, pos - 1);

    }
    // UP
    if (pos - nbLines >= 0) {
        std::vector<int> tmp(data);
        std::swap(tmp[pos], tmp[pos - nbLines]);
        output.emplace_back(tmp, nbLines, this, g + 1, pos - nbLines);
    }
    // Right
    if ((pos + 1) % nbLines) {
        std::vector<int> tmp(data);
        std::swap(tmp[pos], tmp[pos + 1]);
        output.emplace_back(tmp, nbLines, this, g + 1, pos + 1);
    }
    // DOWN
    if (pos + nbLines < size) {
        std::vector<int> tmp(data);
        std::swap(tmp[pos], tmp[pos + nbLines]);
        output.emplace_back(tmp, nbLines, this, g + 1, pos + nbLines);
    }

    return output;
}

size_t Graph::getNullPos(const std::vector<int> &v) {
    for (int i = 0; i < v.size(); ++i) {
        if (v[i] == 0) {
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

std::string Graph::displayParent(size_t &length) {
    std::string out;
    const Graph *p = this;
    length = 0;
    while (p->parent != nullptr) {
        out.insert(0, std::to_string(p->nullPos) + " ");
        ++length;
        p = p->parent;
    }
    return out;
}

std::vector<int> Graph::transformIntoIntVector(const std::string &data) {
    std::stringstream iss(data);
    std::vector<int> out;
    out.reserve(data.size());
    int i;
    while (!iss.eof()) {
        iss >> i;
        out.push_back(i);
    }
    return out;
}

size_t Graph::getH() const {
    return h;
}