#include "../include/BinarySearchTree.h"
#include<iostream>
#include <stdexcept>
#include<queue>
#include <sstream>
#include <climits>

namespace Perikan { namespace TREE {


struct Node{
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int k, int h = 1, Node* l = nullptr, Node* r = nullptr) :key(k), left(l), right(r), height(h) {}

    std::string to_string() const {
        std::ostringstream oss;
        oss << "(" << key << ")";
        return oss.str();
    }
};


BinarySearchTree::BinarySearchTree(): _root(nullptr){}

BinarySearchTree::~BinarySearchTree(){
    clear();
}


void BinarySearchTree::clear(){
    _root = _clear(_root);
}


bool BinarySearchTree::_isNull(const Node* node) const {
    return node == nullptr;
}



Node* BinarySearchTree::_clear(Node* node) {
    if (node == nullptr) return nullptr;
    else {
        node->left = _clear(node->left);
        node->right = _clear(node->right);
        delete node;
        return nullptr;
    }

}


    bool BinarySearchTree::isEmpty() const {
        return _isNull(this->_root);
    }


    std::string BinarySearchTree::to_string() const {
        return _to_string(this->_root);
    }



    std::string BinarySearchTree::_to_string(Node * node) const {
        //caso base:
        if (_isNull(node)) return "#";
        //recursao:
        else {
            std::string left = _to_string(node->left);
            std::string right = _to_string(node->right);
            return node->to_string() + left + " " + right;
        }
    }


    void BinarySearchTree::add(int key) {
        _root = _add(key, _root);
    }


    Node* BinarySearchTree::_add(int key, Node * node) {
        if (_isNull(node)) return new Node(key, 1);
        if (key < node->key) {
            node->left = _add(key, node->left);
        }
        else if (key > node->key) {
            node->right = _add(key, node->right);
        }
        return node;
    }


    int BinarySearchTree::size() const {
        return _size(_root);
    }


    int BinarySearchTree::_size(Node * node) const {
        if (_isNull(node)) return 0;
        else {
            return _size(node->left) + _size(node->right) + 1;
        }
    }



    int BinarySearchTree::countLeafs() const {
        return _countLeafs(_root);
    }




    int BinarySearchTree::_countLeafs(const Node * node) const {
        if (_isNull(node)) return 0;
        else if (_isLeaf(node)) {
            return 1;
        }
        else {
            return _countLeafs(node->left) + _countLeafs(node->right);
        }
    }



    void BinarySearchTree::removeLeafs() {
        _root = _removeLeafs(_root);
    }



    Node* BinarySearchTree::_removeLeafs(Node * node) {
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


    bool BinarySearchTree::_isLeaf(const Node * node) const {
        return _isNull(node) ? false : _isNull(node->left) && _isNull(node->right);
    }



    void BinarySearchTree::print() const {
        _print(_root);
        std::cout << std::endl;
    }


    void BinarySearchTree::_print(const Node * node) const {
        if (!_isNull(node)) {
            std::cout << node->key << " ";
            _print(node->left);
            _print(node->right);
        }
        else {
            std::cout << " #";
        }
    }


    /*T BinarySearchTree::find(int key) const {
        const Node* node = _find(key, _root);
        if (_isNull(node)) throw std::runtime_error("[find] Not found");
        return node->value;
    }*/


    bool BinarySearchTree::contain(int key) const {
        const Node* node = _find(key, _root);
        return !_isNull(node);
    }


    /*int BinarySearchTree::findByValue(T value) const {
        const Node* node = _findByValue(value, _root);
        if (_isNull(node)) throw std::runtime_error("[findByValue] Not found");
        return node->key;
    }*/



    const Node* BinarySearchTree::_find(int key, const Node * node) const {
        if (_isNull(node)) return nullptr;
        else if (node->key == key) return node;
        else {
            if (key < node->key) return _find(key, node->left);
            else return _find(key, node->right);
        }
    }


    /*const Node* BinarySearchTree::_findByValue(T value, const Node * node) const {
        if (_isNull(node)) return nullptr;
        else if (node->value == value) return node;
        else {
            const Node* left = _findByValue(value, node->left);
            if (!_isNull(left)) return left;
            const Node* right = _findByValue(value, node->right);
            if (!_isNull(right)) return right;
            return nullptr;
        }
    }*/



    int BinarySearchTree::countInterNodes() const {
        return _countInterNodes(_root);
    }



    int BinarySearchTree::_countInterNodes(Node * node) const {
        if (_isNull(node) || _isLeaf(node)) return 0;
        else {
            return _countInterNodes(node->left) + _countInterNodes(node->right) + 1;
        }
    }


    int BinarySearchTree::max() const {
        Node* nodeMax = _max(_root);
        if (_isNull(nodeMax)) throw std::runtime_error("Max Key NotFound");
        return nodeMax->key;
    }


    Node* BinarySearchTree::_max(Node * node) const {
        if (_isNull(node)) return node;
        else if (_isLeaf(node)) return node;
        else {
            Node* left = _max(node->left);
            Node* right = _max(node->right);

            if (_isNull(left)) return right;
            if (_isNull(right)) return left;
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


    void BinarySearchTree::_printInOrder(const Node * node) const {
        if (!_isNull(node)) {
            _printInOrder(node->left);
            std::cout << node->key << " ";
            _printInOrder(node->right);
        }
    }

    void BinarySearchTree::_printPreOrder(const Node * node) const {
        if (!_isNull(node)) {
            std::cout << node->key << " ";
            _printPreOrder(node->left);
            _printPreOrder(node->right);
        }
    }

    void BinarySearchTree::_printPosOrder(const Node * node) const {
        if (!_isNull(node)) {
            _printPosOrder(node->left);
            _printPosOrder(node->right);
            std::cout << node->key << " ";
        }
    }


    void BinarySearchTree::printBFS() const {
        std::queue<Node*> frontier;
        Node* node = _root;
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



    int BinarySearchTree::height()const {
        return _height(_root);
    }


    int BinarySearchTree::_height(const Node * node)const {
        if (_isNull(node)) return 0;
        else if (_isLeaf(node)) return 1;
        else {
            int left = _height(node->left);
            int right = _height(node->right);
            return (left > right ? left : right) + 1;
        }
    }


    void BinarySearchTree::remove(int key) {
        _root = _remove(key, _root);
    }



    Node* BinarySearchTree::_remove(int key, Node * node) {
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



    Node* BinarySearchTree::_removeRoot(Node * node) {
        Node* father, * aux;
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


    void BinarySearchTree::printOrdered() const {
        //this->_printOrdered(_root);
        std::cout << _keyOrderedString(_root) << std::endl;
    }



    void BinarySearchTree::_printOrdered(const Node * node) const {
        if (!_isNull(node)) {
            _printOrdered(node->left);
            std::cout << node->key << " ";
            _printOrdered(node->right);
        }
    }


    std::string BinarySearchTree::keyOrderedString() const {
        return _keyOrderedString(_root);
    }



    std::string BinarySearchTree::_keyOrderedString(const Node * node) const {
        if (!_isNull(node)) {
            std::string s = std::to_string(node->key);
            return _keyOrderedString(node->left) + " " + s + " " + _keyOrderedString(node->right);
        }
        else {
            return "";
        }
    }

    int BinarySearchTree::keyMinimum() const {
        if (_isNull(_root)) throw std::runtime_error("Tree empty");
        return _minimum(_root)->key;
    }

    int BinarySearchTree::keyMaximum() const {
        if (_isNull(_root)) throw std::runtime_error("Tree empty");
        return _maximum(_root)->key;
    }


    const Node* BinarySearchTree::_minimum(const Node * node) const {
        if (_isNull(node)) return nullptr;
        else {
            if (_isNull(node->left)) return node;
            const Node* left = _minimum(node->left);
            return left->key < node->key ? left : node;
        }
    }

    const Node* BinarySearchTree::_maximum(const Node * node) const {
        if (_isNull(node)) return nullptr;
        else {
            if (_isNull(node->right)) return node;
            const Node* right = _maximum(node->right);
            return right->key > node->key ? right : node;
        }
    }


    int BinarySearchTree::keySuccessor(int key) const {
        if (_isNull(_root)) throw std::runtime_error("Tree Empty");
        const Node* node = _successor(key, _root, _root);
        if (_isNull(node)) throw std::runtime_error("Successor not found");
        return node->key;
    }

    int BinarySearchTree::keyPredecessor(int key) const {
        if (_isNull(_root)) throw std::runtime_error("Tree Empty");
        const Node* node = _predecessor(key, _root, _root);
        if (_isNull(node)) throw std::runtime_error("Predecessor not found");
        return node->key;
    }


    const Node* BinarySearchTree::_successor(int key, const Node * node, const Node * parent) const {
        if (_isNull(node)) return nullptr;
        else if (key < node->key) return _successor(key, node->left, node);
        else if (key > node->key) return _successor(key, node->right, parent);
        else {
            if (!_isNull(node->right)) {
                const Node* current = node->right;
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

    const Node* BinarySearchTree::_predecessor(int key, const Node * node, const Node * parent) const {
        if (_isNull(node)) return nullptr;
        else if (key < node->key) return _predecessor(key, node->left, parent);
        else if (key > node->key) return _predecessor(key, node->right, node);
        else {
            if (!_isNull(node->left)) {
                const Node* current = node->left;
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



    std::vector<int> BinarySearchTree::getKeys() const {
        std::vector<int> ls;
        _auxGetKeys(_root, ls);
        return ls;
    }


    void BinarySearchTree::_auxGetKeys(const Node * node, std::vector<int>&ls) const {
        if (_isNull(node)) {
            _auxGetKeys(node->left, ls);
            ls.push_back(node->key);
            _auxGetKeys(node->right, ls);
        }
    }


    ////////////////////////////

}}