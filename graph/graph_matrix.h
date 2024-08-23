#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H

#include <assert.h>

#include <vector>

#include "graph.h"

template <typename Tvertex>
struct Vertex {
    Tvertex data_;
    int in_degree_;
    int out_degree_;
    VertexStatus status_;
    size_t discovered_time_;
    size_t finished_time_;
    size_t parent_;
    int priority_;

    Vertex(Tvertex data)
        : data_(data),
          in_degree_(0),
          out_degree_(0),
          status_(VertexStatus::UNDISCOVERED),
          discovered_time_(-1),
          finished_time_(-1),
          parent_(-1),
          priority_(INT_MAX) {}
};

template <typename Tedge>
struct Edge {
    Tedge data_;
    int weight_;
    EdgeType edge_type_;

    Edge(Tedge data, int w) : data_(data), weight_(w), edge_type_(EdgeType::UNDITERMINED) {}
};

template <typename Tvertex, typename Tedge>
class GraphMatrix : public Graph<Tvertex, Tedge> {
   public:
    GraphMatrix() {
        vertex_number_ = 0;
        edge_number_ = 0;
    }

    ~GraphMatrix() {
        for (int i = 0; i < vertex_number_; ++i) {
            for (int j = 0; j < vertex_number_; ++j) {
                delete edges_[i][j];
            }
        }
    }

    virtual size_t addVertex(Tvertex vertex) override {
        for (size_t i = 0; i < vertex_number_; ++i) {
            edges_[i].push_back(nullptr);
        }
        std::vector<Edge<Tedge>*> edge(vertex_number_ + 1, nullptr);
        edges_.emplace_back(edge);

        Vertex<Tvertex> v(vertex);
        vertices_.emplace_back(v);
        ++vertex_number_;

        return vertex_number_ - 1;
    }

    // to do later complicated memory handle
    virtual Tvertex removeVertex(size_t index) override {
        return vertexData(index);
    }

    virtual size_t firstNeighbor(size_t index) override { return nextNeighbor(index, vertex_number_); }
    virtual size_t nextNeighbor(size_t index1, size_t index2) override {
        if (vertex_number_ == 0) {
            return vertex_number_;
        }

        if (index2 == 0) {
            return vertex_number_;
        }

        --index2;
        if (index2 >= vertex_number_) {
            index2 = vertex_number_ - 1;
        }

        while (index2 != 0) {
            if (hasEdge(index1, index2)) {
                return index2;
            }
            --index2;
        }

        return hasEdge(index1, 0) ? 0 : vertex_number_;
    }

    virtual Tvertex& vertexData(size_t index) override { return vertices_[index].data_; }
    virtual size_t inDegree(size_t index) override { return vertices_[index].in_degree_; }
    virtual size_t outDegree(size_t index) override { return vertices_[index].out_degree_; }
    virtual VertexStatus vertexStatus(size_t index) override { return vertices_[index].status_; }
    virtual void setVertexStatus(size_t index, VertexStatus vs) override { vertices_[index].status_ = vs; }
    virtual size_t discoveredTime(size_t index) override { return vertices_[index].discovered_time_; }
    virtual void setDiscoveredTime(size_t index, size_t dt) override { vertices_[index].discovered_time_ = dt; }
    virtual size_t finishedTime(size_t index) override { return vertices_[index].finished_time_; }
    virtual void setFinishedTime(size_t index, size_t ft) override { vertices_[index].finished_time_ = ft; }
    virtual size_t parent(size_t index) override { return vertices_[index].parent_; }
    virtual void setParent(size_t index, size_t parent) override { vertices_[index].parent_ = parent; }
    virtual int priority(size_t index) override { return vertices_[index].priority_; }
    virtual void setPriority(size_t index, int prio) override { vertices_[index].priority_ = prio; }

    // edge related methods
    virtual Tedge& edgeData(size_t vertex1, size_t vertex2) override { return edges_[vertex1][vertex2]->data_; }
    virtual int edgeWeight(size_t vertex1, size_t vertex2) override { return edges_[vertex1][vertex2]->weight_; }
    virtual EdgeType edgeType(size_t vertex1, size_t vertex2) override { return edges_[vertex1][vertex2]->edge_type_; }
    virtual void setEdgeType(size_t vertex1, size_t vertex2, EdgeType et) override {
        edges_[vertex1][vertex2]->edge_type_ = et;
    }
    virtual bool hasEdge(size_t vertex1, size_t vertex2) override {
        return (vertex1 < vertex_number_) && (vertex2 < vertex_number_) && (edges_[vertex1][vertex2] != nullptr);
    }
    virtual void addEdge(Tedge edge, int weight, size_t vertex1, size_t vertex2) override { 
        if (hasEdge(vertex1, vertex2)) return;
        edges_[vertex1][vertex2] = new Edge<Tedge>(edge, weight);
        ++edge_number_;
        ++vertices_[vertex1].out_degree_;
        ++vertices_[vertex2].in_degree_;
    }
    virtual Tedge removeEdge(size_t vertex1, size_t vertex2) override { 
        Tedge edge_data = edgeData(vertex1, vertex2);
        delete edges_[vertex1][vertex2];
        edges_[vertex1][vertex2] = nullptr;
        ++edge_number_;
        --vertices_[vertex1].out_degree_;
        --vertices_[vertex2].in_degree_;
        return edge_data;
    }

   private:
    std::vector<Vertex<Tvertex>> vertices_;
    std::vector<std::vector<Edge<Tedge>*>> edges_;
};

#endif