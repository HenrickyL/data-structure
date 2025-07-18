#ifndef QXD_BST_IMPL
#define QXD_BST_IMPL

#include "../include/BinarySearchTree.h"
#include<iostream>
#include <stdexcept>
#include<queue>
#include <sstream>
#include <climits>


namespace Perikan { namespace TREE {

template <typename VALUE, typename KEY>
BinarySearchTree<VALUE, KEY>::BinarySearchTree(): 
    _root(nullptr), _comparisonCount(0),_searchCount(0),_insertionCount(0) {}

template <typename VALUE, typename KEY>
BinarySearchTree<VALUE, KEY>::~BinarySearchTree(){
    clear();
}


template <typename VALUE, typename KEY>
void BinarySearchTree<VALUE, KEY>::_setRoot(Node<VALUE, KEY>* root) {
    this->_root = root;
}

template <typename VALUE, typename KEY>
void BinarySearchTree<VALUE, KEY>::clear(){
    Node<VALUE, KEY>* node = _clear(this->_root);
    _setRoot(node);
}

template <typename VALUE, typename KEY>
bool BinarySearchTree<VALUE, KEY>::_isNull(const Node<VALUE,KEY>* node) const {
    return node == nullptr;
}
template <typename VALUE, typename KEY>
Node<VALUE, KEY>* BinarySearchTree<VALUE, KEY>::_getNull() const{ 
    return nullptr;
}

template <typename VALUE, typename KEY>
Node<VALUE,KEY>* BinarySearchTree<VALUE, KEY>::_clear(Node<VALUE,KEY>* node) {
    if (_isNull(node)) return _getNull();
    else {
        node->left = _clear(node->left);
        node->right = _clear(node->right);
        delete node;
        return  _getNull();
    }
}

template <typename VALUE, typename KEY>
bool BinarySearchTree<VALUE, KEY>::isEmpty() const {
    return _isNull(this->_root);
}


template <typename VALUE, typename KEY>
std::string BinarySearchTree<VALUE, KEY>::to_string() const {
    return _to_string(this->_root);
}


template <typename VALUE, typename KEY>
std::string BinarySearchTree<VALUE, KEY>::_to_string(Node<VALUE,KEY>* node) const {
    //caso base:
    if (_isNull(node)) return "#";
    //recursao:
    else {
        std::string left = _to_string(node->left);
        std::string right = _to_string(node->right);
        return node->to_string() + left + " " + right;
    }
}

template <typename VALUE, typename KEY>
void BinarySearchTree<VALUE, KEY>::add(const KEY& key, const VALUE& value) {
    Node<VALUE, KEY>* node = _add(key, value, this->_root);
    _setRoot(node);
}

template <typename VALUE, typename KEY>
Node<VALUE,KEY>* BinarySearchTree<VALUE, KEY>::_add(const KEY& key, const VALUE& value, Node<VALUE,KEY>* node) {
    _comparisonCount++;
    if (_isNull(node)) {
        _insertionCount++;
        return _createNode(key, value); 
    }
    _comparisonCount++;
    if (key < node->key) {
        node->left = _add(key, value, node->left);
    }
    else if (key > node->key) {
        node->right = _add(key,value, node->right);
    }
    return node;
}


template <typename VALUE, typename KEY>
Node<VALUE, KEY>* BinarySearchTree<VALUE, KEY>::_createNode(const KEY& key, const VALUE& value) {
    return new Node<VALUE, KEY>(key, value);
}


template <typename VALUE, typename KEY>
int BinarySearchTree<VALUE, KEY>::size() const {
    return _size(this->_root);
}

template <typename VALUE, typename KEY>
int BinarySearchTree<VALUE, KEY>::_size(Node<VALUE,KEY>* node) const {
    if (_isNull(node)) return 0;
    else {
        return _size(node->left) + _size(node->right) + 1;
    }
}


template <typename VALUE, typename KEY>
int BinarySearchTree<VALUE, KEY>::countLeafs() const {
    return _countLeafs(this->_root);
}



template <typename VALUE, typename KEY>
int BinarySearchTree<VALUE, KEY>::_countLeafs(const Node<VALUE,KEY>* node) const {
    if (_isNull(node)) return 0;
    else if (_isLeaf(node)) {
        return 1;
    }
    else {
        return _countLeafs(node->left) + _countLeafs(node->right);
    }
}


template <typename VALUE, typename KEY>
void BinarySearchTree<VALUE, KEY>::removeLeafs() {
    Node<VALUE, KEY>* node = _removeLeafs(this->_root);
    _setRoot(node);
}


template <typename VALUE, typename KEY>
Node<VALUE,KEY>* BinarySearchTree<VALUE, KEY>::_removeLeafs(Node<VALUE,KEY>* node) {
    if (node == nullptr) return nullptr;
    else if (node->left == nullptr && node->right == nullptr) {
        delete node;
        return nullptr;
    }
    else {
        node->left = _removeLeafs(node->left);
        node->right = _removeLeafs(node->right);
        return node;
    }
}

template <typename VALUE, typename KEY>
bool BinarySearchTree<VALUE, KEY>::_isLeaf(const Node<VALUE,KEY>* node) const {
    return _isNull(node) ? false : _isNull(node->left) && _isNull(node->right);
}


template <typename VALUE, typename KEY>
void BinarySearchTree<VALUE, KEY>::print() const {
    _print(this->_root);
    std::cout << std::endl;
}

template <typename VALUE, typename KEY>
void BinarySearchTree<VALUE, KEY>::_print(const Node<VALUE,KEY>* node) const {
    if (!_isNull(node)) {
        std::cout << node->to_string() << " ";
        _print(node->left);
        _print(node->right);
    }
    else {
        std::cout << " #";
    }
}


/*T BinarySearchTree<VALUE, KEY>::find(int key) const {
    const Node<VALUE,KEY>* node = _find(key, _root);
    if (_isNull(node)) throw std::runtime_error("[find] Not found");
    return node->value;
}*/

template <typename VALUE, typename KEY>
bool BinarySearchTree<VALUE, KEY>::contains(const KEY& key) const {
    const Node<VALUE,KEY>* node = _find(key, this->_root);
    return node != nullptr;
}


/*int BinarySearchTree<VALUE, KEY>::findByValue(T value) const {
    const Node<VALUE,KEY>* node = _findByValue(value, _root);
    if (_isNull(node)) throw std::runtime_error("[findByValue] Not found");
    return node->key;
}*/


template <typename VALUE, typename KEY>
const Node<VALUE,KEY>* BinarySearchTree<VALUE, KEY>::_find(const KEY& key, const Node<VALUE,KEY>* node) const {
    _searchCount++;
    if (_isNull(node)) return nullptr;
    _comparisonCount++;
    if (node->key == key) return node;
    _comparisonCount++;
    if (key < node->key) return _find(key, node->left);
    return _find(key, node->right);
}

template <typename VALUE, typename KEY>
Node<VALUE, KEY>* BinarySearchTree<VALUE, KEY>::_find(const KEY& key, Node<VALUE, KEY>* node) {
    _searchCount++;
    if (_isNull(node)) return nullptr;
    _comparisonCount++;
    if (node->key == key) return node;
    _comparisonCount++;
    if (key < node->key) return _find(key, node->left);
    return _find(key, node->right);
}


template <typename VALUE, typename KEY>
const VALUE BinarySearchTree<VALUE, KEY>::find(const KEY& key) const {
    const Node<VALUE, KEY>* node = _find(key, _root);
    if (node==nullptr) throw std::runtime_error("Not find key:" + key);
    return node->value;
}
template <typename VALUE, typename KEY>
VALUE& BinarySearchTree<VALUE, KEY>::find(const KEY& key) {
    Node<VALUE, KEY>* node = _find(key, _root);
    if (node == nullptr) throw std::runtime_error("Not find key:" + key);
    return node->value;
}



/*const Node<VALUE,KEY>* BinarySearchTree<VALUE, KEY>::_findByValue(T value, const Node<VALUE,KEY>* node) const {
    if (_isNull(node)) return nullptr;
    else if (node->value == value) return node;
    else {
        const Node<VALUE,KEY>* left = _findByValue(value, node->left);
        if (!_isNull(left)) return left;
        const Node<VALUE,KEY>* right = _findByValue(value, node->right);
        if (!_isNull(right)) return right;
        return nullptr;
    }
}*/


template <typename VALUE, typename KEY>
int BinarySearchTree<VALUE, KEY>::countInterNodes() const {
    return _countInterNodes(this->_root);
}


template <typename VALUE, typename KEY>
int BinarySearchTree<VALUE, KEY>::_countInterNodes(Node<VALUE,KEY>* node) const {
    if (_isNull(node) || _isLeaf(node)) return 0;
    else {
        return _countInterNodes(node->left) + _countInterNodes(node->right) + 1;
    }
}

template <typename VALUE, typename KEY>
int BinarySearchTree<VALUE, KEY>::max() const {
    Node<VALUE,KEY>* nodeMax = _max(this->_root);
    if (_isNull(nodeMax)) throw std::runtime_error("Max Key NotFound");
    return nodeMax->key;
}

template <typename VALUE, typename KEY>
Node<VALUE,KEY>* BinarySearchTree<VALUE, KEY>::_max(Node<VALUE,KEY>* node) const {
    if (_isNull(node)) return node;
    else if (_isLeaf(node)) return node;
    else {
        Node<VALUE,KEY>* left = _max(node->left);
        Node<VALUE,KEY>* right = _max(node->right);

        if (_isNull(left)) return right;
        if (_isNull(right)) return left;
        return left->key > right->key ? left : right;
    }
}

/////////////////////////////
template <typename VALUE, typename KEY>
void BinarySearchTree<VALUE, KEY>::printInOrder() const {
    std::cout << "In..: ";
    this->_printInOrder(this->_root);
    std::cout << std::endl;

}
template <typename VALUE, typename KEY>
void BinarySearchTree<VALUE, KEY>::printPreOrder() const {
    std::cout << "Pre.: ";
    this->_printPreOrder(this->_root);
    std::cout << std::endl;
}

template <typename VALUE, typename KEY>
void BinarySearchTree<VALUE, KEY>::printPosOrder() const {
    std::cout << "Post: ";
    this->_printPosOrder(this->_root);
    std::cout << std::endl;
}

template <typename VALUE, typename KEY>
void BinarySearchTree<VALUE, KEY>::_printInOrder(const Node<VALUE,KEY>* node) const {
    if (!_isNull(node)) {
        _printInOrder(node->left);
        std::cout << node->key << " ";
        _printInOrder(node->right);
    }
}

template <typename VALUE, typename KEY>
void BinarySearchTree<VALUE, KEY>::_printPreOrder(const Node<VALUE,KEY>* node) const {
    if (!_isNull(node)) {
        std::cout << node->key << " ";
        _printPreOrder(node->left);
        _printPreOrder(node->right);
    }
}

template <typename VALUE, typename KEY>
void BinarySearchTree<VALUE, KEY>::_printPosOrder(const Node<VALUE,KEY>* node) const {
    if (!_isNull(node)) {
        _printPosOrder(node->left);
        _printPosOrder(node->right);
        std::cout << node->key << " ";
    }
}

template <typename VALUE, typename KEY>
void BinarySearchTree<VALUE, KEY>::printBFS() const {
    std::queue<Node<VALUE,KEY>*> frontier;
    Node<VALUE,KEY>* node = this->_root;
    frontier.push(node);

    while (!frontier.empty()) {
        node = frontier.front();
        frontier.pop();
        if (node->left)frontier.push(node->left);
        if (node->right)frontier.push(node->right);
        std::cout << node->key << " ";
    }
    std::cout << std::endl;
}


template <typename VALUE, typename KEY>
int BinarySearchTree<VALUE, KEY>::height()const {
    return _height(this->_root);
}

template <typename VALUE, typename KEY>
int BinarySearchTree<VALUE, KEY>::_height(const Node<VALUE,KEY>* node)const {
    if (_isNull(node)) return 0;
    else if (_isLeaf(node)) return 1;
    else {
        int left = _height(node->left);
        int right = _height(node->right);
        return (left > right ? left : right) + 1;
    }
}

template <typename VALUE, typename KEY>
void BinarySearchTree<VALUE, KEY>::remove(const KEY& key) {
    Node<VALUE, KEY>* node = _remove(key, this->_root);
    _setRoot(node);
}


template <typename VALUE, typename KEY>
Node<VALUE,KEY>* BinarySearchTree<VALUE, KEY>::_remove(const KEY& key, Node<VALUE,KEY>* node) {
    if (_isNull(node)) return node;
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


template <typename VALUE, typename KEY>
Node<VALUE,KEY>* BinarySearchTree<VALUE, KEY>::_removeRoot(Node<VALUE,KEY>* node) {
    Node<VALUE,KEY>* father, * aux;
    if (_isNull(node->right)) {
        aux = node->left;
    }
    else {
        father = node;
        aux = node->right;
        while (!_isNull(aux->left)) {
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

template <typename VALUE, typename KEY>
void BinarySearchTree<VALUE, KEY>::printOrdered() const {
    //this->_printOrdered(_root);
    std::cout << _keyOrderedString(this->_root) << std::endl;
}


template <typename VALUE, typename KEY>
void BinarySearchTree<VALUE, KEY>::_printOrdered(const Node<VALUE,KEY>* node) const {
    if (!_isNull(node)) {
        _printOrdered(node->left);
        std::cout << node->key << " ";
        _printOrdered(node->right);
    }
}

template <typename VALUE, typename KEY>
std::string BinarySearchTree<VALUE, KEY>::keyOrderedString() const {
    return _keyOrderedString(this->_root);
}


template <typename VALUE, typename KEY>
std::string BinarySearchTree<VALUE, KEY>::_keyOrderedString(const Node<VALUE,KEY>* node) const {
    if (!_isNull(node)) {
        std::string s = node->to_string();
        return _keyOrderedString(node->left) + " " + s + " " + _keyOrderedString(node->right);
    }
    else {
        return "";
    }
}

template <typename VALUE, typename KEY>
int BinarySearchTree<VALUE, KEY>::keyMinimum() const {
    if (_isNull(this->_root)) throw std::runtime_error("Tree empty");
    return _minimum(this->_root)->key;
}

template <typename VALUE, typename KEY>
int BinarySearchTree<VALUE, KEY>::keyMaximum() const {
    if (_isNull(this->_root)) throw std::runtime_error("Tree empty");
    return _maximum(this->_root)->key;
}


template <typename VALUE, typename KEY>
const Node<VALUE,KEY>* BinarySearchTree<VALUE, KEY>::_minimum(const Node<VALUE,KEY>* node) const {
    if (_isNull(node)) return nullptr;
    else {
        if (_isNull(node->left)) return node;
        const Node<VALUE,KEY>* left = _minimum(node->left);
        return left->key < node->key ? left : node;
    }
}

template <typename VALUE, typename KEY>
const Node<VALUE,KEY>* BinarySearchTree<VALUE, KEY>::_maximum(const Node<VALUE,KEY>* node) const {
    if (_isNull(node)) return nullptr;
    else {
        if (_isNull(node->right)) return node;
        const Node<VALUE,KEY>* right = _maximum(node->right);
        return right->key > node->key ? right : node;
    }
}


template <typename VALUE, typename KEY>
KEY BinarySearchTree<VALUE, KEY>::keySuccessor(const KEY& key) const {
    if (_isNull(this->_root)) throw std::runtime_error("Tree Empty");
    const Node<VALUE,KEY>* node = _successor(key, this->_root, this->_root);
    if (_isNull(node)) throw std::runtime_error("Successor not found");
    return node->key;
}

template <typename VALUE, typename KEY>
KEY BinarySearchTree<VALUE, KEY>::keyPredecessor(const KEY& key) const {
    if (_isNull(this->_root)) throw std::runtime_error("Tree Empty");
    const Node<VALUE,KEY>* node = _predecessor(key, this->_root, this->_root);
    if (_isNull(node)) throw std::runtime_error("Predecessor not found");
    return node->key;
}

template <typename VALUE, typename KEY>
const Node<VALUE,KEY>* BinarySearchTree<VALUE, KEY>::_successor(const KEY& key, const Node<VALUE,KEY>* node, const Node<VALUE,KEY>* parent) const {
    if (_isNull(node)) return nullptr;
    else if (key < node->key) return _successor(key, node->left, node);
    else if (key > node->key) return _successor(key, node->right, parent);
    else {
        if (!_isNull(node->right)) {
            const Node<VALUE,KEY>* current = node->right;
            while (!_isNull(current->left)) {
                current = current->left;
            }
            return current;
        }
        else {
            return parent;
        }
    }
}

template <typename VALUE, typename KEY>
const Node<VALUE,KEY>* BinarySearchTree<VALUE, KEY>::_predecessor(const KEY& key, const Node<VALUE,KEY>* node, const Node<VALUE,KEY>* parent) const {
    if (_isNull(node)) return nullptr;
    else if (key < node->key) return _predecessor(key, node->left, parent);
    else if (key > node->key) return _predecessor(key, node->right, node);
    else {
        if (!_isNull(node->left)) {
            const Node<VALUE,KEY>* current = node->left;
            while (!_isNull(current->right)) {
                current = current->right;
            }
            return current;
        }
        else {
            return parent;
        }
    }
}


template <typename VALUE, typename KEY>
std::vector<int> BinarySearchTree<VALUE, KEY>::getKeys() const {
    std::vector<int> ls;
    _auxGetKeys(this->_root, ls);
    return ls;
}

template <typename VALUE, typename KEY>
void BinarySearchTree<VALUE, KEY>::_auxGetKeys(const Node<VALUE,KEY>* node, std::vector<int>&ls) const {
    if (_isNull(node)) {
        _auxGetKeys(node->left, ls);
        ls.push_back(node->key);
        _auxGetKeys(node->right, ls);
    }
}
template <typename VALUE, typename KEY>
void BinarySearchTree<VALUE, KEY>::setValue(const KEY& key, const VALUE& value) {
    Node<VALUE, KEY>* node = _find(key, _root);
    if(_isNull(node)) throw std::runtime_error("Not found with key: " << key);
    node->value = value;

}
template <typename VALUE, typename KEY>
void BinarySearchTree<VALUE, KEY>::resetMetrics(){ 
    _comparisonCount = _insertionCount =_searchCount = 0; 
}

template<typename VALUE, typename KEY>
std::vector<std::pair<KEY, VALUE>> BinarySearchTree<VALUE, KEY>::getSortedEntries() const {
    std::vector<std::pair<KEY, VALUE>> entries;
    _inOrderCollect(this->_root, entries);
    return entries;
}

template<typename VALUE, typename KEY>
void BinarySearchTree<VALUE, KEY>::_inOrderCollect(const Node<VALUE, KEY>* node, std::vector<std::pair<KEY, VALUE>>& entries) const {
    if (_isNull(node)) return;
    _inOrderCollect(node->left, entries);
    entries.emplace_back(node->key, node->value);
    _inOrderCollect(node->right, entries);
}
    ////////////////////////////

}}


#endif