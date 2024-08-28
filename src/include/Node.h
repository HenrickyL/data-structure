#ifndef UT_NODE_H
#define UT_NODE_H
namespace EDA{
    template<typename T>
    struct Node{
        T key;
        Node<T>* left;
        Node<T>* right;
        int height=0;        

        Node(T _value_, Node<T>* _left = nullptr, Node<T>* _right = nullptr){
            key = _value_;
            left = _left;
            right = _right; 
        }
    };
}
#endif