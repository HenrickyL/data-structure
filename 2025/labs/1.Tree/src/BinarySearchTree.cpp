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


std::string BinarySearchTree::_to_string(Node* root) const{
    //caso base:
    if(root == nullptr) return "#";
    //recursao:
    else{
        std::string left = _to_string(root->left);
        std::string right = _to_string(root->right);
        return std::to_string(root->key)+" " + left + " " + right;
    }
}


void BinarySearchTree::add(int key){
    _root = _add(key, _root);
}

Node* BinarySearchTree::_add(int key, Node* root){
    if(root == nullptr) return new Node(key);
    if(key < root->key){
        root->left = _add(key, root->left);
    }else if(key > root->key){
        root->right = _add(key, root->right);
    }
    return root;
}

}}