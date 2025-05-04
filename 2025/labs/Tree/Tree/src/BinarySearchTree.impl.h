#ifndef QXD_BST_IMPL
#define QXD_BST_IMPL

#include "../include/BinarySearchTree.h"
#include<iostream>
#include<vector>
#include <stdexcept>
#include<queue>
#include <sstream>
#include <climits>

namespace Perikan{
    namespace TREE{

template <typename T>
struct Node{
    int key;
    T value;
    Node<T>* left;
    Node<T>* right;
    int height;

    Node(int k, T v = T(), int h = 1, Node<T>* l = nullptr, Node<T>* r = nullptr) : key(k), value(v), height(h), left(l), right(r) {}

    std::string to_string() const {
        std::ostringstream oss;
        oss << "(" << key << ", " << value << ")";
        return oss.str();
    }
};

template <typename T>
BinarySearchTree<T>::BinarySearchTree(): _root(nullptr){}
template <typename T>
BinarySearchTree<T>::~BinarySearchTree(){
    clear();
}

template <typename T>

void BinarySearchTree<T>::clear(){
    _root = _clear(_root);
}

template <typename T>
Node<T>* BinarySearchTree<T>::_clear(Node<T>* node){
    if(node == nullptr) return nullptr;
    else{
        node->left = _clear(node->left);
        node->right = _clear(node->right);
        delete node;
        return nullptr;
    }
}


template <typename T>
bool BinarySearchTree<T>::isEmpty() const{
    return this->_root == nullptr;
}

template <typename T>
std::string BinarySearchTree<T>::to_string() const{
    return _to_string(this->_root);
}


template <typename T>
std::string BinarySearchTree<T>::_to_string(Node<T>* node) const{
    //caso base:
    if(node == nullptr) return "#";
    //recursao:
    else{
        std::string left = _to_string(node->left);
        std::string right = _to_string(node->right);
        std::string value_str = "";
       
        return node->to_string() + left + " " + right;
    }
}

template <typename T>
void BinarySearchTree<T>::add(int key, T value){
    _root = _add(key, value, _root);
}

template <typename T>
Node<T>* BinarySearchTree<T>::_add(int key, T value, Node<T>* node){
    if(node == nullptr) return new Node<T>(key, value, 1);
    if(key < node->key){
        node->left = _add(key, value, node->left);
    }else if(key > node->key){
        node->right = _add(key,value, node->right);
    }
    return node;
}

template <typename T>
int BinarySearchTree<T>::size() const{
    return _size(_root);
}

template <typename T>
int BinarySearchTree<T>::_size(Node<T>* node) const{
    if(node == nullptr) return 0;
    else{
        return _size(node->left) + _size(node->right) + 1;
    }
}


template <typename T>
int BinarySearchTree<T>::countLeafs() const{
    return _countLeafs(_root);
}



template <typename T>
int BinarySearchTree<T>::_countLeafs(const Node<T>* node) const{
    if(node == nullptr) return 0;
    else if(node->left == nullptr && node->right == nullptr){
        return 1;
    }else{
        return _countLeafs(node->left) + _countLeafs(node->right);
    }
}


template <typename T>
void BinarySearchTree<T>::removeLeafs(){
     _root = _removeLeafs(_root);
}


template <typename T>
Node<T>* BinarySearchTree<T>::_removeLeafs(Node<T>* node){
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

template <typename T>
bool BinarySearchTree<T>::_isLeaf(const Node<T>* node) const {
    return node == nullptr ? false : node->left == nullptr && node->right == nullptr;
}


template <typename T>
void BinarySearchTree<T>::print() const{
    _print(_root);
    std::cout << std::endl;
}

template <typename T>
void BinarySearchTree<T>::_print(const Node<T>* node) const{
    if(node != nullptr){
        std::cout <<node->key << " " ;
        _print(node->left);
        _print(node->right);
    }else{
        std::cout<< " #";
    }
}

template <typename T>
T BinarySearchTree<T>::find(int key) const{
    const Node<T>* node = _find(key, _root);
    if (node == nullptr) throw std::runtime_error("[find] Not found");
    return node->value;
}

template <typename T>
bool BinarySearchTree<T>::contain(int key) const {
    const Node<T>* node = _find(key, _root);
    return node != nullptr;
}

template <typename T>
int BinarySearchTree<T>::findByValue(T value) const {
    const Node<T>* node = _findByValue(value, _root);
    if (node == nullptr) throw std::runtime_error("[findByValue] Not found");
    return node->key;
}


template <typename T>
const Node<T>* BinarySearchTree<T>::_find(int key, const Node<T>* node) const{
    if(node == nullptr) return nullptr;
    else if(node->key == key) return node;
    else{
        if(key < node->key) return _find(key, node->left);
        else return _find(key, node->right);
    }
}

template <typename T>
const Node<T>* BinarySearchTree<T>::_findByValue(T value, const Node<T>* node) const {
    if (node == nullptr) return nullptr;
    else if (node->value == value) return node;
    else {
        const Node<T>* left = _findByValue(value, node->left);
        if (left != nullptr) return left;
        const Node<T>* right = _findByValue(value, node->right);
        if (right != nullptr) return right;
        return nullptr;
    }
}


template <typename T>
int BinarySearchTree<T>::countInterNodes() const {
    return _countInterNodes(_root);
}


template <typename T>
int BinarySearchTree<T>::_countInterNodes(Node<T>* node) const {
    if ( node == nullptr || (node->left == nullptr && node->right ==nullptr) ) return 0;
    else {
        return _countInterNodes(node->left) + _countInterNodes(node->right) + 1;
    }
}

template <typename T>
int BinarySearchTree<T>::max() const { 
   Node<T>* nodeMax = _max(_root);
   if(nodeMax == nullptr) throw std::runtime_error("Max Key NotFound");
   return nodeMax->key;
}

template <typename T>
Node<T>* BinarySearchTree<T>::_max(Node<T>* node) const {
    if (node == nullptr) return node;
    else if (_isLeaf(node)) return node;
    else {
        Node<T>* left = _max(node->left);
        Node<T>* right = _max(node->right);
        
        if (left == nullptr) return right;
        if (right == nullptr) return left;
        return left->key > right->key ? left : right;
    }
}

/////////////////////////////
template <typename T>
void BinarySearchTree<T>::printInOrder() const {
    std::cout << "In..: ";
    this->_printInOrder(_root);
    std::cout << std::endl;

}
template <typename T>
void BinarySearchTree<T>::printPreOrder() const {
    std::cout << "Pre.: ";
    this->_printPreOrder(_root);
    std::cout << std::endl;
}
template <typename T>
void BinarySearchTree<T>::printPosOrder() const {
    std::cout << "Post: ";
    this->_printPosOrder(_root);
    std::cout << std::endl;
}

template <typename T>
void BinarySearchTree<T>::_printInOrder(const Node<T>* node) const {
    if (node != nullptr) {
        _printInOrder(node->left);
        std::cout << node->key << " ";
        _printInOrder(node->right);
    }
}
template <typename T>
void BinarySearchTree<T>::_printPreOrder(const Node<T>* node) const{
    if (node != nullptr) {
        std::cout << node->key << " ";
        _printPreOrder(node->left);
        _printPreOrder(node->right);
    }
}
template <typename T>
void BinarySearchTree<T>::_printPosOrder(const Node<T>* node) const{
    if (node != nullptr) {
        _printPosOrder(node->left);
        _printPosOrder(node->right);
        std::cout << node->key << " ";
    }
}

template <typename T>
void BinarySearchTree<T>::printBFS() const {
    std::queue<Node<T>*> frontier;
    Node<T>* node = _root;
    frontier.push(node);

    while (!frontier.empty()) {
        node = frontier.front();
        frontier.pop();
        if(node->left)frontier.push(node->left);
        if (node->right)frontier.push(node->right);
        std::cout << node->key << " ";
    }
    std::cout << std::endl;
}


template <typename T>
int BinarySearchTree<T>::height()const {
    return _height(_root);
}

template <typename T>
int BinarySearchTree<T>::_height(const Node<T>* node)const {
    if (node == nullptr) return 0;
    else if (_isLeaf(node)) return 1;
    else {
        int left = _height(node->left);
        int right = _height(node->right);
        return (left > right ? left : right) + 1;
    }
}

template <typename T>
void BinarySearchTree<T>::remove(int key) {
    _root = _remove(key, _root);
}


template <typename T>
Node<T>* BinarySearchTree<T>::_remove(int key, Node<T>* node) {
    if (node == nullptr) return node;
    else {
        if (node->key == key) {
            return _removeRoot(node);
        }
        else if (node->key > key) {
            node->left = _remove(key, node->left);
        }
        else {
            node->right = _remove(key, node->right);
        }
        return node;
    }
}


template <typename T>
Node<T>* BinarySearchTree<T>::_removeRoot(Node<T>* node) {
    Node<T> *father, *aux;
    if (node->right == nullptr) {
        aux = node->left;
    }
    else {
        father = node;
        aux = node->right;
        while (aux->left != nullptr) {
            father = aux;
            aux = aux->left;
        }
        if (father != node) {
            father->left = aux->right;
            aux->right = node->right;
        }
        aux->left = node->left;
    }
    delete node;
    return aux;
}

template <typename T>
void BinarySearchTree<T>::printOrdered() const {
    //this->_printOrdered(_root);
    std::cout << _keyOrderedString(_root) << std::endl;
}


template <typename T>
void BinarySearchTree<T>::_printOrdered(const Node<T>* node) const {
    if(node != nullptr) {
        _printOrdered(node->left);
        std::cout << node->key << " ";
        _printOrdered(node->right);
    }
}

template <typename T>
std::string BinarySearchTree<T>::keyOrderedString() const {
    return _keyOrderedString(_root);
}


template <typename T>
std::string BinarySearchTree<T>::_keyOrderedString(const Node<T>* node) const {
    if (node != nullptr) {
        return _keyOrderedString(node->left) + " " + std::to_string(node->key) + " " + _keyOrderedString(node->right);
    }
    else {
        return "";
    }
}
template <typename T>
int BinarySearchTree<T>::keyMinimum() const {
    if (_root == nullptr) throw std::runtime_error("Tree empty");
    return _keyMinimum(_root);
}
template <typename T>
int BinarySearchTree<T>::keyMaximum() const {
    if (_root == nullptr) throw std::runtime_error("Tree empty");
    return _keyMaximum(_root);
}

template <typename T>
int BinarySearchTree<T>::_keyMinimum(const Node<T>* node) const {
    if (node == nullptr) return INT_MAX;
    else {
        int left = _keyMinimum(node->left);
        return left < node->key  ? left : node->key ;
    }
}
template <typename T>
int BinarySearchTree<T>::_keyMaximum(const Node<T>* node) const {
    if (node == nullptr) return INT_MIN;
    else {
        int right = _keyMaximum(node->right);
        return right > node->key  ? right : node->key ;
    }
}

////////////////////////////
}}

#endif