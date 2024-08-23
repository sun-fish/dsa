#include <iostream>

#include "graph_matrix.h"
#include "utility.h"

int main(int argc, char** argv) {
    GraphMatrix<char, int> graph1;
    size_t va = graph1.addVertex('a');
    size_t vb = graph1.addVertex('b');
    size_t vc = graph1.addVertex('c');
    size_t vd = graph1.addVertex('d');
    size_t ve = graph1.addVertex('e');
    size_t vf = graph1.addVertex('f');
    size_t vg = graph1.addVertex('g');
    size_t vs = graph1.addVertex('s');

    graph1.addEdge(1, 1, vs, va);
    graph1.addEdge(1, 1, vs, vc);
    graph1.addEdge(1, 1, vs, vd);
    graph1.addEdge(1, 1, va, vc);
    graph1.addEdge(1, 1, va, ve);
    graph1.addEdge(1, 1, vc, vb);
    graph1.addEdge(1, 1, vd, vb);
    graph1.addEdge(1, 1, ve, vf);
    graph1.addEdge(1, 1, ve, vg);
    graph1.addEdge(1, 1, vg, vf);
    graph1.addEdge(1, 1, vg, vb);

    graph1.bfs(vs);
    std::cout << std::endl << "graph1 breadth first visit end!" << std::endl;

    GraphMatrix<char, int> graph2;
    va = graph2.addVertex('a');
    vb = graph2.addVertex('b');
    vc = graph2.addVertex('c');
    vd = graph2.addVertex('d');
    ve = graph2.addVertex('e');
    vf = graph2.addVertex('f');
    vg = graph2.addVertex('g');

    graph2.addEdge(1, 1, va, vb);
    graph2.addEdge(1, 1, va, vc);
    graph2.addEdge(1, 1, va, vf);
    graph2.addEdge(1, 1, vb, vc);
    graph2.addEdge(1, 1, vd, va);
    graph2.addEdge(1, 1, vd, ve);
    graph2.addEdge(1, 1, ve, vf);
    graph2.addEdge(1, 1, vf, vg);
    graph2.addEdge(1, 1, vg, vc);
    graph2.addEdge(1, 1, vg, va);
    graph2.dfs(va);
    std::cout << std::endl << "graph2 depth first visit end!" << std::endl;

    GraphMatrix<char, int> graph3;
    va = graph3.addVertex('a');
    vb = graph3.addVertex('b');
    vc = graph3.addVertex('c');
    vd = graph3.addVertex('d');
    ve = graph3.addVertex('e');
    vf = graph3.addVertex('f');

    graph3.addEdge(1, 1, va, vc);
    graph3.addEdge(1, 1, va, vd);
    graph3.addEdge(1, 1, vb, vc);
    graph3.addEdge(1, 1, vc, vd);
    graph3.addEdge(1, 1, vc, ve);
    graph3.addEdge(1, 1, vc, vf);
    graph3.addEdge(1, 1, ve, vf);

    std::stack<char>* s = graph3.tSort(vc);
    while (!s->empty()) {
        std::cout << s->top() << "    ";
        s->pop();
    }
    delete s;
    std::cout << std::endl << "graph3 topological sort end!" << std::endl;

    graph3.dijkstra(va);
    graph3.pfs(va, BfsPU<char, int>());

    std::cout << "Press Enter to continue...";
    std::cin.get();
    return 0;
}