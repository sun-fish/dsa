#ifndef GRAPH_UTILITY
#define GRAPH_UTILITY

#include <assert.h>

#include "graph.h"

template <typename Tvertex, typename Tedge>
struct BfsPU {
    virtual void operator()(Graph<Tvertex, Tedge>* g, size_t uk, size_t v) {
        if (g->vertexStatus(v) == VertexStatus::UNDISCOVERED) {
            if (g->priority(v) > g->priority(uk) + 1) {
                g->setPriority(v, g->priority(uk) + 1);
                g->setParent(v, uk);
            }
        }
    }
};

template <typename Tvertex, typename Tedge>
struct DfsPU {
    virtual void operator()(Graph<Tvertex, Tedge>* g, size_t uk, size_t v) {
        if (g->vertexStatus(v) == VertexStatus::UNDISCOVERED) {
            if (g->priority(v) > g->priority(uk) - 1) {
                g->setPriority(v, g->priority(uk) - 1);
                g->setParent(v, uk);
                return; //notice: different to BfsPU() if one vertex is updated , need return
            }
        }
    }
};

template <typename Tvertex, typename Tedge>
struct DijkPU {
    virtual void operator()(Graph<Tvertex, Tedge>* g, size_t v, size_t u) {
        if (VertexStatus::UNDISCOVERED == g->vertexStatus(u)) {
            if (g->priority(u) > g->priority(v) + g->weight(v, u)) {
                g->setPriority(u, g->priority(v) + g->weight(v, u));
                g->setParent(u, v);
            }
        }
    }
};

#endif  // !GRAPH_UTILITY