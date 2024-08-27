#ifndef QUAD_LIST_NODE_H
#define QUAD_LIST_NODE_H


/////////////////////////////////////////////////////
//                                               ////
//                     above_                    ////
//                      /\                       ////
//                      ||                       ////
//                 _____||_____                  ////
//                |            |                 ////
//      pred_<----|QuadListNode|---->succ_       ////
//                |____________|                 ////
//                      ||                       ////
//                      ||                       ////
//                      \/                       ////
//                     below_                    ////
//                                               ////
/////////////////////////////////////////////////////

template <typename T>
class QuadListNode {
   public:
    QuadListNode(T entry = T(), QuadListNode<T>* pred = nullptr, QuadListNode<T>* succ = nullptr,
          QuadListNode<T>* above = nullptr, QuadListNode<T>* below = nullptr)
        : entry_(entry), pred_(pred), succ_(succ), above_(above), below_(below) {}

    T entry_;
    QuadListNode<T>* pred_;
    QuadListNode<T>* succ_;
    QuadListNode<T>* above_;
    QuadListNode<T>* below_;
};

#endif