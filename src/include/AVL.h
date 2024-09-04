#ifndef UT_AVT_TREE_H
#define UT_AVT_TREE_H

#include "BSTree.h"
#include<cmath>

namespace EDA{

template<typename T>
class AVL : public BSTree<T>{
protected:
    virtual Node<T>* _Insert(Node<T>* root, T value) override;

    Node<T>* _FixupNode(Node<T>* node, T key);
public:
    int Balance(Node<T>* node);

};

template<typename T>
Node<T>* AVL<T>::_Insert(Node<T>* node, T key){
    if(node == nullptr){
        return new Node<T>(key, 1);
    }else if(key == node->key){ //repeated key
        return node;
    }else if(key < node->key){
        node->left = _Insert(node->left, key);
    }else{
        node->right = _Insert(node->right, key);
    }
    node = _FixupNode(node, key);

    return node;
}

template<typename T>
Node<T>* AVL<T>::_FixupNode(Node<T>* node, T key){
    node->height = 1+ std::max(this->Height(node->left), this->Height(node->right));
    int bal = this->Balance(node);
// Caso 1(a)
    if( bal < -1 && key < node->left->key ){
        return this->_RightRotate(node);
    }
// Caso 1(b):
    else if( bal < -1 && key > node->left->key ) {
       return this->_DoubleRotateRight(node);
    }
// Caso 2(a)
    else if(  bal > 1 && key > node->right->key) {
        return this->_LeftRotate(node);
    }
// Caso 2(b)
    else if( bal > 1 && key < node->right->key ){
        return this->_DoubleRotateLeft(node);
    }
    return node;
}

template<typename T>
int AVL<T>::Balance(Node<T>* node){
    return this->Height(node->right) - this->Height(node->left);
}


}

#endif