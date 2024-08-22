#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>

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

    // void bfs(size_t vertex);
    // void dfs(size_t vertex);
    // void bcc(size_t vertex);   
    // Stack<Tv>* tSort(size_t vertex);
    // void prim(size_t vertex); 
    // void dijkstra(size_t vertex);     
    // template <typename PU>
    // void pfs(size_t vertex, PU);

   protected:
    size_t vertex_number_;
    size_t edge_number_;
};

#endif