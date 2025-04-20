#include "../include/BinarySearchTree.h"
#include<iostream>
#include<vector>
#include <stdexcept>

namespace Perikan{
    namespace TREE{

struct Node{
    int key;
    Node* left;
    Node* right;
    Node(int val) : key(val), left(nullptr), right(nullptr) {}
};

BinarySearchTree::BinarySearchTree(): _root(nullptr){}
BinarySearchTree::~BinarySearchTree(){
    clear();
}

void BinarySearchTree::clear(){
    _root = _clear(_root);
}

Node* BinarySearchTree::_clear(Node* node){
    if(node == nullptr) return nullptr;
    else{
        node->left = _clear(node->left);
        node->right = _clear(node->right);
        delete node;
        return nullptr;
    }
}


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


int BinarySearchTree::countLeafs() const{
    return _countLeafs(_root);
}


int BinarySearchTree::_countLeafs(const Node* node) const{
    if(node == nullptr) return 0;
    else if(node->left == nullptr && node->right == nullptr){
        return 1;
    }else{
        return _countLeafs(node->left) + _countLeafs(node->right);
    }
}

void BinarySearchTree::removeLeafs(){
     _root = _removeLeafs(_root);
}


Node* BinarySearchTree::_removeLeafs(Node* node){
    if(node == nullptr) return nullptr;
    else if(node->left == nullptr && node->right == nullptr){
        delete node;
        return nullptr;
    }else{
        node->left =_removeLeafs(node->left);
        node->right = _removeLeafs(node->right);
        return node;
    }
}

bool BinarySearchTree::_isLeaf(const Node* node) const {
    return node == nullptr ? false : node->left == nullptr && node->right == nullptr;
}


void BinarySearchTree::print() const{
    _print(_root);
    std::cout << std::endl;
}
void BinarySearchTree::_print(const Node* node) const{
    if(node != nullptr){
        std::cout <<node->key << " " ;
        _print(node->left);
        _print(node->right);
    }else{
        std::cout<< " #";
    }
}

bool BinarySearchTree::find(int key) const{
    const Node* node = _find(key, _root);
    return node != nullptr;
}

const Node* BinarySearchTree::_find(int key, const Node* node) const{
    if(node == nullptr) return nullptr;
    else if(node->key == key) return node;
    else{
        if(key < node->key) return _find(key, node->left);
        else return _find(key, node->right);
    }
}


int BinarySearchTree::countInterNodes() const {
    return _countInterNodes(_root);
}


int BinarySearchTree::_countInterNodes(Node* node) const {
    if ( node == nullptr || (node->left == nullptr && node->right ==nullptr) ) return 0;
    else {
        return _countInterNodes(node->left) + _countInterNodes(node->right) + 1;
    }
}

int BinarySearchTree::max() const { 
   Node* nodeMax = _max(_root);
   if(nodeMax == nullptr) throw std::runtime_error("Max Key NotFound");
   return nodeMax->key;
}

Node* BinarySearchTree::_max(Node* node) const {
    if (node == nullptr) return node;
    else if (_isLeaf(node)) return node;
    else {
        Node* left = _max(node->left);
        Node* right = _max(node->right);
        
        if (left == nullptr) return right;
        if (right == nullptr) return left;
        return left->key > right->key ? left : right;
    }
}

/////////////////////////////

void BinarySearchTree::printInOrder() const {
    std::cout << "In..: ";
    this->_printInOrder(_root);
    std::cout << std::endl;

}
void BinarySearchTree::printPreOrder() const {
    std::cout << "Pre.: ";
    this->_printPreOrder(_root);
    std::cout << std::endl;
}
void BinarySearchTree::printPosOrder() const {
    std::cout << "Post: ";
    this->_printPosOrder(_root);
    std::cout << std::endl;
}

void BinarySearchTree::_printInOrder(const Node* node) const {
    if (node != nullptr) {
        _printInOrder(node->left);
        std::cout << node->key << " ";
        _printInOrder(node->right);
    }
}
void BinarySearchTree::_printPreOrder(const Node* node) const{
    if (node != nullptr) {
        std::cout << node->key << " ";
        _printPreOrder(node->left);
        _printPreOrder(node->right);
    }
}
void BinarySearchTree::_printPosOrder(const Node* node) const{
    if (node != nullptr) {
        _printPosOrder(node->left);
        _printPosOrder(node->right);
        std::cout << node->key << " ";
    }
}


////////////////////////////
}}