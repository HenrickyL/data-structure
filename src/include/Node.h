#ifndef UT_NODE_H
#define UT_NODE_H
namespace EDA{
    template<typename T>
    struct Node{
        T value;
        Node* left;
        Node* right;
    };
}
#endif