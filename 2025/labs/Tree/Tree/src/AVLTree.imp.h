#ifndef QXD_AVL_IMPL
#define QXD_AVL_IMPL

#include <algorithm>
#include "../include/AVLTree.h"

namespace Perikan {
    namespace TREE {


template <typename T>
AVLTree<T>::AVLTree() : BinarySearchTree<T>(){}

template <typename T>
AVLTree<T>::~AVLTree() {
    this->clear();
}


template <typename T>
int AVLTree<T>::height()const {
    return _height(this->_root);
}

template <typename T>
int AVLTree<T>::_height(const Node<T>* node) const {
    return (node == nullptr) ? 0 : node->height;
}
template <typename T>
int AVLTree<T>::_balance(const Node<T>* node) const {
    if (node == nullptr) {
        throw std::runtime_error("[balance] node not be null!");
    }
    return _height(node->right) - _height(node->left);
}

template <typename T>
Node<T>* AVLTree<T>::_rightRotation(Node<T>* node) {
    Node<T>* aux = node->left;
    node->left = aux->right;
    aux->right = node;
    //fix
    node->height = 1 + std::max(_height(node->left), _height(node->right));
    aux->height = 1 + std::max(_height(aux->left), _height(aux->right));
    return aux;
}

template <typename T>
Node<T>* AVLTree<T>::_leftRotation(Node<T>* node) {
    Node<T>* aux = node->right;
    node->right = aux->left;
    aux->left = node;
    //fix
    node->height = 1 + std::max(_height(node->left), _height(node->right));
    aux->height = 1 + std::max(_height(aux->left), _height(aux->right));
    return aux;
}

template <typename T>
Node<T>* AVLTree<T>::_fixup_node(Node<T>* node, int key) {
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
template <typename T>
Node<T>* AVLTree<T>::_fixup_deletion(Node<T>* node) {
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
template <typename T>
Node<T>* AVLTree<T>::_add(int key, T value, Node<T>* node){
    if (node == nullptr) {
        return new Node<T>(key, value, 1);
    }
    else {
        if (key == node->key) return node;
        else if (key < node->key) {
            node->left = _add(key, value, node->left);
        }
        else {
            node->right = _add(key, value, node->right);
        }

        //fix
        node = _fixup_node(node, key);
        return node;
    }
}

template <typename T>
Node<T>* AVLTree<T>::_remove(int key, Node<T>* node) {
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
            Node<T>* child = node->left;
            delete node;
            return child;
        }
        else { // Tem filho direito: troca pelo sucessor
            node->right = _remove_successor(node, node->right);
        }
    }

    // Atualiza a altura do nó e regula o nó
    node = _fixup_deletion(node);
    return node;
}

template <typename T>
Node<T>* AVLTree<T>::_remove_successor(Node<T>* root, Node<T>* node) {
    if (node->left != nullptr) {
        node->left = _remove_successor(root, node->left);
    }
    else {
        root->key = node->key;
        Node<T>* aux = node->right;
        delete node;
        return aux;
    }

    // Atualiza a altura do nó e regula o nó
    node = _fixup_deletion(node);
    return node;
}




}}

#endif