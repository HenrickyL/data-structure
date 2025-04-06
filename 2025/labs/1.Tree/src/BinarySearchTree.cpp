#include "../includes/BinarySearchTree.h"
#include<iostream>
#include<vector>
namespace Perikan{
    namespace TREE{

struct Node{
    int key;
    Node* left;
    Node* right;
    Node(int val) : key(val), left(nullptr), right(nullptr) {}
};

BinarySearchTree::BinarySearchTree(): _root(nullptr){}

bool BinarySearchTree::isEmpty() const{
    return this->_root == nullptr;
}

std::string BinarySearchTree::to_string() const{
    return _to_string(this->_root);
}


std::string BinarySearchTree::_to_string(Node* node) const{
    //caso base:
    if(node == nullptr) return "#";
    //recursao:
    else{
        std::string left = _to_string(node->left);
        std::string right = _to_string(node->right);
        return std::to_string(node->key)+" " + left + " " + right;
    }
}

void BinarySearchTree::add(int key){
    _root = _add(key, _root);
}

Node* BinarySearchTree::_add(int key, Node* node){
    if(node == nullptr) return new Node(key);
    if(key < node->key){
        node->left = _add(key, node->left);
    }else if(key > node->key){
        node->right = _add(key, node->right);
    }
    return node;
}

int BinarySearchTree::countNodes() const{
    return _countNodes(_root);
}
int BinarySearchTree::_countNodes(Node* node) const{
    if(node == nullptr) return 0;
    else{
        return _countNodes(node->left) + _countNodes(node->right) + 1;
    }
}



////////////////////////////
}}