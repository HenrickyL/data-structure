#include "../include/AVLTree.h"
#include <stdexcept>
#include <algorithm>
#include <sstream>


namespace Perikan {namespace TREE {

struct Node {
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

AVLTree::AVLTree() : BinarySearchTree(){}


AVLTree::~AVLTree() {
    this->clear();
}



int AVLTree::height()const {
    return _height(this->_root);
}


int AVLTree::_height(const Node* node) const {
    return (node == nullptr) ? 0 : node->height;
}

int AVLTree::_balance(const Node* node) const {
    if (node == nullptr) {
        throw std::runtime_error("[balance] node not be null!");
    }
    return _height(node->right) - _height(node->left);
}


Node* AVLTree::_rightRotation(Node* node) {
    Node* aux = node->left;
    node->left = aux->right;
    aux->right = node;
    //fix
    node->height = 1 + std::max(_height(node->left), _height(node->right));
    aux->height = 1 + std::max(_height(aux->left), _height(aux->right));
    return aux;
}


Node* AVLTree::_leftRotation(Node* node) {
    Node* aux = node->right;
    node->right = aux->left;
    aux->left = node;
    //fix
    node->height = 1 + std::max(_height(node->left), _height(node->right));
    aux->height = 1 + std::max(_height(aux->left), _height(aux->right));
    return aux;
}


Node* AVLTree::_fixup_node(Node* node, int key) {
    // Obtém balanço de p
    int bal = _balance(node);

    // Caso 1(a): rotação direita
    if (bal < -1 && key < node->left->key)
        return _rightRotation(node);

    // Caso 1(b): rotação dupla direita
    else if (bal < -1 && key > node->left->key) {
        node->left = _leftRotation(node->left);
        return _rightRotation(node);
    }

    // Caso 2(a): rotação esquerda
    else if (bal > 1 && key > node->right->key)
        return _leftRotation(node);

    // Caso 2(b): rotação dupla esquerda
    else if (bal > 1 && key < node->right->key) {
        node->right = _rightRotation(node->right);
        return _leftRotation(node);
    }

    // Atualiza altura deste nó ancestral p
    node->height = 1 + std::max(_height(node->left), _height(node->right));

    return node;
}

Node* AVLTree::_fixup_deletion(Node* node) {
    int bal = _balance(node);
    // O nó pode estar desregulado, há 4 casos a considerar
    if (bal > 1) {
        if (_balance(node->right) >= 0) {
            return _leftRotation(node);
        }
        else {
            node->right = _rightRotation(node->right);
            return _leftRotation(node);
        }
    }
    else if (bal < -1) {
        if (_balance(node->left) <= 0) {
            return _rightRotation(node);
        }
        else {
            node->left = _leftRotation(node->left);
            return _rightRotation(node);
        }
    }

    // Atualiza altura do nó
    node->height = 1 + std::max(_height(node->left), _height(node->right));

    return node;

}


/* --------------------------------------------------------------- */

Node* AVLTree::_add(int key, Node* node){
    if (node == nullptr) {
        return new Node(key, 1);
    }
    else {
        if (key == node->key) return node;
        else if (key < node->key) {
            node->left = _add(key, node->left);
        }
        else {
            node->right = _add(key, node->right);
        }

        //fix
        node = _fixup_node(node, key);
        return node;
    }
}


Node* AVLTree::_remove(int key, Node* node) {
    if (node == nullptr) // Nó não encontrado
        return nullptr;

    if (key < node->key) {
        node->left = _remove(key, node->left);
    }
    else if (key > node->key) {
        node->right = _remove(key, node->right);
    }
    else { // Encontramos o nó
        if (node->right == nullptr) { // Sem filho direito
            Node* child = node->left;
            delete node;
            return child;
        }
        else { // Tem filho direito: troca pelo sucessor
            node->right = _remove_successor(node, node->right);
        }
    }

    // Atualiza a altura
    node = _fixup_deletion(node);
    return node;
}


Node* AVLTree::_remove_successor(Node* root, Node* node) {
    if (node->left != nullptr) {
        node->left = _remove_successor(root, node->left);
    }
    else {
        root->key = node->key;
        Node* aux = node->right;
        delete node;
        return aux;
    }

    // Atualiza a altura do nó e regula o nó
    node = _fixup_deletion(node);
    return node;
}




}}

