#ifndef BINARY_NODE_H
#define BINARY_NODE_H

#if defined(DSA_REDBLACK)                   // Red-Black Tree
#define stature(p) ((p) ? (p)->height : 0)  // initial height is 0, else recursive
#else
#define stature(p) ((int)((p) ? (p)->height : -1))  // initial height is -1, else recursive
#endif

typedef enum { RB_RED, RB_BLACK } RBColor;

template <typename T>
class BinaryNode {
   public:
    BinaryNode()
        : parent_(nullptr),
          left_child_(nullptr),
          right_child_(nullptr),
          height_(0),
          null_path_length_(1),
          color_(RB_RED) {}

    BinaryNode(T e, BinaryNode<T>* parent = nullptr, BinaryNode<T>* left_child = nullptr,
               BinaryNode<T>* right_child = nullptr, int height = 0, int npl = 1, RBColor color = RB_RED)
        : data_(e),
          parent_(parent),
          left_child_(left_child),
          right_child_(right_child),
          height_(height),
          null_path_length_(npl),
          color_(color) {}

    bool operator<(BinaryNode<T>& bn) { return data_ < bn.data(); }
    bool operator==(BinaryNode<T>& bn) { return data_ == bn.data(); }

    T data() { return data_; }
    void set_data(T data) { data_ = data; }

    BinaryNode<T>* parent() { return parent_; }
    void set_parent(BinaryNode<T>* parent) { parent_ = parent; }

    BinaryNode<T>* left_child() { return left_child_; }
    void set_left_child(BinaryNode<T>* left_child) { left_child_ = left_child; }

    BinaryNode<T>* right_child() { return right_child_; }
    void set_right_child(BinaryNode<T>* right_child) { right_child_ = right_child; }

    size_t height() { return height_; };
    void set_height(size_t height) { height_ = height; }

    size_t null_path_length() { return null_path_length_; }
    void set_null_path_length(size_t null_path_length) { null_path_length_ = null_path_length; }

    RBColor color() { return color_; }
    void set_color(RBColor color) { color_ = color; }

   private:
    T data_;
    BinaryNode<T>*parent_, *left_child_, *right_child_;
    size_t height_;
    size_t null_path_length_;  // nullptr Path Length, left heap
    RBColor color_;            // used for red black tree
};

#endif