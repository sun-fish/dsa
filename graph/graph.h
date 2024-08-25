#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <queue>
#include <stack>

// EXAMPLE char @ represent vertex, char ------> represent edge
//
//                  edge 1 and edge 2 are tree edge,
//                  edge 3 is cross edge,
//                  edge 4 is back edge,
//                  edge 5 is forward edge
//
//                     ------->@----------  f
//                 b  |       / \         | o
//                 a  |     tree tree     | r
//                 c  4     1     2       5 w
//                 k  |    /       \      | a
//                    |   \/       \/     | r
//                     ---@-cross3->@<----  d

using VertexStatus = enum { UNDISCOVERED, DISCOVERED, VISITED };  // vertex status
using EdgeType = enum { UNDITERMINED, TREE, CROSS, FORWARD, BACKWARD };

template <typename Tvertex, typename Tedge>
class Graph {
   private:
    void reset() {
        for (size_t i = 0; i < vertex_number_; ++i) {
            setVertexStatus(i, VertexStatus::UNDISCOVERED);
            setParent(i, -1);
            setPriority(i, INT_MAX);
            for (size_t j = 0; j < vertex_number_; ++j) {
                if (hasEdge(i, j)) {
                    setEdgeType(i, j, EdgeType::UNDITERMINED);
                }
            }
        }
    };

   public:
    // key algorithm
    void BFS(size_t vertex, size_t& clock);
    void DFS(size_t vertex, size_t& clock);
    template <typename PU>
    void PFS(size_t v, PU prioUpdater);
    bool TopologicalSort(size_t vertex, size_t& clock, std::stack<Tvertex>* s);

    size_t vertex_number() { return vertex_number_; }
    void set_vertex_number(size_t vertex_number) { vertex_number_ = vertex_number; }

    size_t edge_number() { return edge_number_; }
    void set_edge_number(size_t edge_number) { edge_number_ = edge_number; }

    virtual size_t addVertex(Tvertex vertex) = 0;
    virtual Tvertex removeVertex(size_t index) = 0;
    virtual Tvertex& vertexData(size_t index) = 0;
    virtual size_t inDegree(size_t index) = 0;
    virtual size_t outDegree(size_t index) = 0;
    virtual size_t firstNeighbor(size_t index) = 0;
    virtual size_t nextNeighbor(size_t index, size_t max_index) = 0;

    virtual VertexStatus vertexStatus(size_t index) = 0;
    virtual void setVertexStatus(size_t index, VertexStatus vs) = 0;
    virtual size_t discoveredTime(size_t index) = 0;
    virtual void setDiscoveredTime(size_t index, size_t dt) = 0;
    virtual size_t finishedTime(size_t index) = 0;
    virtual void setFinishedTime(size_t index, size_t ft) = 0;
    virtual size_t parent(size_t index) = 0;
    virtual void setParent(size_t index, size_t parent) = 0;
    virtual int priority(size_t index) = 0;
    virtual void setPriority(size_t index, int prio) = 0;

    // edge related methods
    virtual bool hasEdge(size_t vertex1, size_t vertex2) = 0;
    virtual void addEdge(Tedge edge, int weight, size_t vertex1, size_t vertex2) = 0;
    virtual Tedge removeEdge(size_t vertex1, size_t vertex2) = 0;
    virtual EdgeType edgeType(size_t vertex1, size_t vertex2) = 0;
    virtual void setEdgeType(size_t vertex1, size_t vertex2, EdgeType et) = 0;
    virtual Tedge& edgeData(size_t vertex1, size_t vertex2) = 0;
    virtual int edgeWeight(size_t vertex1, size_t vertex2) = 0;

    // user interface
    void bfs(size_t vertex);
    void dfs(size_t vertex);
    std::stack<Tvertex>* tSort(size_t vertex);
    void dijkstra(size_t vertex);
    template <typename PU>
    void pfs(size_t vertex, PU);

    // void bcc(size_t vertex);
    // void prim(size_t vertex);

   protected:
    size_t vertex_number_;
    size_t edge_number_;
};

template <typename Tvertex, typename Tedge>
void Graph<Tvertex, Tedge>::BFS(size_t vertex, size_t& discoveredClock) {
    std::queue<size_t> help_queue;
    setVertexStatus(vertex, DISCOVERED);
    help_queue.push(vertex);
    setDiscoveredTime(vertex, discoveredClock++);
    size_t v1 = vertex;

    // discoveredClock is equal to generation
    while (!help_queue.empty()) {
        if (discoveredTime(v1) < discoveredTime(help_queue.front())) {
            discoveredClock++;
        }

        v1 = help_queue.front();
        help_queue.pop();

        for (size_t v2 = firstNeighbor(v1); vertex_number_ != v2; v2 = nextNeighbor(v1, v2)) {
            if (UNDISCOVERED == vertexStatus(v2)) {
                setVertexStatus(v2, VertexStatus::DISCOVERED);
                help_queue.push(v2);
                setDiscoveredTime(v2, discoveredClock);
                setEdgeType(v1, v2, EdgeType::TREE);
                setParent(v2, v1);
            } else {
                setEdgeType(v1, v2, EdgeType::CROSS);
            }
        }

        std::cout << vertexData(v1) << "    ";
        setVertexStatus(v1, VertexStatus::VISITED);
    }
}

template <typename Tvertex, typename Tedge>
void Graph<Tvertex, Tedge>::bfs(size_t vertex_index) {
    reset();
    size_t discoveredClock = 0;
    for (size_t i = vertex_index; i < vertex_index + vertex_number_; ++i) {
        if (UNDISCOVERED == vertexStatus(i % vertex_number_)) {
            BFS(i % vertex_number_, discoveredClock);
        }
    }
}

template <typename Tvertex, typename Tedge>
void Graph<Tvertex, Tedge>::dfs(size_t vertex) {
    reset();
    size_t clock = 0;
    for (size_t i = vertex; i < vertex + vertex_number_; ++i) {
        if (UNDISCOVERED == vertexStatus(i % vertex_number_)) {
            DFS(i, clock);
        }
    }
    return;
}

template <typename Tvertex, typename Tedge>
void Graph<Tvertex, Tedge>::DFS(size_t vertex, size_t& clock) {
    setDiscoveredTime(vertex, ++clock);
    setVertexStatus(vertex, VertexStatus::DISCOVERED);
    for (size_t v2 = firstNeighbor(vertex); vertex_number_ != v2; v2 = nextNeighbor(vertex, v2)) {
        switch (vertexStatus(v2)) {
            case UNDISCOVERED:
                setParent(v2, vertex);
                setEdgeType(vertex, v2, EdgeType::TREE);
                DFS(v2, clock);
                break;
            case DISCOVERED:
                setEdgeType(vertex, v2, EdgeType::BACKWARD);
                break;
            default:
                // if true backtrack to vertex else another path the a visited node
                if (discoveredTime(vertex) < discoveredTime(v2)) {
                    setEdgeType(vertex, v2, EdgeType::FORWARD);
                } else {
                    setEdgeType(vertex, v2, EdgeType::CROSS);
                }
                break;
        }
    }
    setVertexStatus(vertex, VISITED);
    setFinishedTime(vertex, clock++);
    std::cout << vertexData(vertex) << "    ";
    return;
}

template <typename Tvertex, typename Tedge>
std::stack<Tvertex>* Graph<Tvertex, Tedge>::tSort(size_t vertex) {
    reset();
    size_t clock = 0;
    std::stack<Tvertex>* help_stack = new std::stack<Tvertex>;
    for (size_t i = vertex; i < vertex + vertex_number_; ++i) {
        if (UNDISCOVERED == vertexStatus(i % vertex_number_)) {
            // any connected sub graph is not DAG
            if (!TopologicalSort(i % vertex_number_, clock, help_stack)) {
                while (!help_stack->empty()) {
                    help_stack->pop();
                }
                break;
            }
        }
    }
    return help_stack;
}

template <typename Tvertex, typename Tedge>
bool Graph<Tvertex, Tedge>::TopologicalSort(size_t vertex, size_t& clock, std::stack<Tvertex>* help_stack) {
    setDiscoveredTime(vertex, ++clock);
    setVertexStatus(vertex, VertexStatus::DISCOVERED);
    for (size_t v2 = firstNeighbor(vertex); vertex_number_ != v2; v2 = nextNeighbor(vertex, v2)) {
        switch (vertexStatus(v2)) {
            case UNDISCOVERED:
                setParent(v2, vertex);
                setEdgeType(vertex, v2, EdgeType::TREE);
                if (!TopologicalSort(v2, clock, help_stack)) {
                    return false;
                }
                break;
            case DISCOVERED:
                setEdgeType(vertex, v2, EdgeType::BACKWARD);
                return false;
            default:
                // the vertex v2 and its descendants have been visited then braak;
                if (discoveredTime(vertex) < discoveredTime(v2)) {
                    setEdgeType(vertex, v2, EdgeType::FORWARD);
                } else {
                    setEdgeType(vertex, v2, EdgeType::CROSS);
                }
                break;
        }
    }
    setVertexStatus(vertex, VISITED);
    help_stack->push(vertexData(vertex));
    return true;
}

// pu define function object(fang han shu) or lambda function
template <typename Tvertex, typename Tedge>
template <typename PU>
void Graph<Tvertex, Tedge>::pfs(size_t s, PU prioUpdater) {
    reset();
    for (size_t v = s; v < s + vertex_number_; v++)
        if (VertexStatus::UNDISCOVERED == vertexStatus(v % vertex_number_)) PFS(v % vertex_number_, prioUpdater);
}

template <typename Tvertex, typename Tedge>
template <typename PU>
void Graph<Tvertex, Tedge>::PFS(size_t v, PU prioUpdater) {
    setPriority(v, 0);
    setVertexStatus(v, VertexStatus::VISITED);  // add vertex v to the pfs tree

    while (1) {
        for (size_t u = firstNeighbor(v); vertex_number_ != u; u = nextNeighbor(v, u)) {
            // update the priority of vertex u and its parent
            prioUpdater(this, v, u);
        }

        int shortest = INT_MAX;
        for (size_t u = 0; u < vertex_number_; ++u) {
            if ((UNDISCOVERED == vertexStatus(u)) && (shortest > priority(u))) {
                shortest = priority(u);
                v = u;
            }
        }
        if (shortest == INT_MAX) {
            break;
        }

        setVertexStatus(v, VertexStatus::VISITED);
        setEdgeType(parent(v), v, EdgeType::TREE);
    }
}

//likely chuan xiao zu zhi, each time, the shortest priority node will be added to path and become new vertex source
// vs source vertex
// if a node has no direct path to source vertex, the priority is set to finite at first
template <typename Tvertex, typename Tedge>
void Graph<Tvertex, Tedge>::dijkstra(size_t vs) {
    reset();
    setPriority(vs, 0);
    for (size_t i = 0; i < vertex_number_; ++i) {
        setVertexStatus(vs, VertexStatus::VISITED);

        if (-1 != parent(vs)) {
            setEdgeType(parent(vs), vs, EdgeType::TREE);
        }

        //update neighbor priority
        for (size_t j = firstNeighbor(vs); vertex_number_ != j; j = nextNeighbor(vs, j)) {
            if ((vertexStatus(j) == VertexStatus::UNDISCOVERED) && (priority(j) > priority(vs) + edgeWeight(vs, j))) {
                setPriority(j, priority(vs) + edgeWeight(vs, j));
                setParent(j, vs);
            }
        }

        // each iterative find the shortest priority node to be new source vertex
        int shortest = INT_MAX;
        for (size_t j = 0; j < vertex_number_; j++) {
            if ((vertexStatus(j) == VertexStatus::UNDISCOVERED) && (shortest > priority(j))) {
                shortest = priority(j);
                vs = j;
            }
        }
    }
}

#endif