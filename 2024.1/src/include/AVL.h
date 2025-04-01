#ifndef UT_AVT_TREE_H
#define UT_AVT_TREE_H

#include "BSTree.h"
#include<cmath>

namespace EDA{

template<typename T>
class AVL : public BSTree<T>{
protected:
    virtual Node<T>* _Insert(Node<T>* root, T value) override;
    virtual Node<T>* _Remove(Node<T>* root, T value) override;

    Node<T>* _FixupNode(Node<T>* node, T key);
    Node<T>* _FixupDeletion(Node<T>* node);
    int _Balance(Node<T>* node);
    Node<T>* _RemoveSuccessor(Node<T>* root, Node<T>* node);

public:

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
    int bal = this->_Balance(node);
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
Node<T>* AVL<T>::_Remove(Node<T>* node, T key){
    if(node  == nullptr) return nullptr;
    if(key < node->key)
        node->left = _Remove(node->left, key);
    else if(key > node->key)
        node->right = _Remove(node->right, key);
    else if(node->right == nullptr){
        Node<T>* child = node->left;
        delete node;
        return child;
    }
    else
        node->right = this->_RemoveSuccessor(node, node->right);
    
    node = _FixupDeletion(node);
    return node;
}

template<typename T>
Node<T>* AVL<T>::_FixupDeletion(Node<T>* node){
    node->height = 1 + std::max( this->Height( node->left ) , this->Height( node->right ));
    int bal = this->_Balance( node );
    if(bal > 1 && this->_Balance( node->right ) >= 0){
        return this->_LeftRotate(node);
    }
    else if( bal > 1 && this->_Balance( node->right ) < 0){
        return this->_DoubleRotateLeft( node ) ;
    }
    else if( bal < -1 && this->_Balance ( node->left ) <= 0){
        return this->_RightRotate( node );
    }
    else if( bal < -1 && this->_Balance ( node->left ) > 0){
        return this->_DoubleRotateRight(node);
    }
    return  node;
}

template<typename T>
int AVL<T>::_Balance(Node<T>* node){
    return this->Height(node->right) - this->Height(node->left);
}

template<typename T>
Node<T>* AVL<T>::_RemoveSuccessor(Node<T>* root, Node<T>* node){
    if( node -> left != nullptr )
        node -> left = this->_RemoveSuccessor( root , node->left );
    else {
        root -> key = node->key ;
        Node<T> * aux = node->right ;
        delete node;
        return aux ;
    }
    node = this->_FixupDeletion( node );
    return node;
}



}

#endif