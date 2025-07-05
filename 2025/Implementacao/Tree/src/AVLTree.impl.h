#ifndef AVL_TREE_IMPL_H
#define AVL_TREE_IMPL_H


#include "../include/AVLTree.h"
#include <stdexcept>
#include <algorithm>
#include <sstream>


namespace Perikan {namespace TREE {


template <typename VALUE, typename KEY>
AVLTree<VALUE,KEY>::AVLTree() : BinarySearchTree<VALUE,KEY>(){}

template <typename VALUE, typename KEY>
AVLTree<VALUE,KEY>::~AVLTree() {
    this->clear();
}


//template <typename VALUE, typename KEY>
//typename AVLTree<VALUE, KEY>::NodeBase*
//AVLTree<VALUE, KEY>::_getRoot() const {
//    return this->_root;
//}
//
//template <typename VALUE, typename KEY>
//void AVLTree<VALUE, KEY>::_setRoot(NodeBase* root) {
//    this->_root = static_cast<NodeType*>(root);
//}

template <typename VALUE, typename KEY>
int AVLTree<VALUE, KEY>::balance() const {
    return _balance(static_cast<NodeType*>(this->_root));
}


template <typename VALUE, typename KEY>
int AVLTree<VALUE,KEY>::_balance(const NodeType* node) const {
    if (node == nullptr) {
        throw std::runtime_error("[balance] node not be null!");
    }
    return _height(node->right) - _height(node->left);
}
template <typename VALUE, typename KEY>
int AVLTree<VALUE, KEY>::rotationCount() const {
    return _rotationCount;
}
template <typename VALUE, typename KEY>
void AVLTree<VALUE, KEY>::resetMetric() {
    this->_rotationCount = 0;
}



template <typename VALUE, typename KEY>
typename AVLTree<VALUE, KEY>::NodeType* AVLTree<VALUE,KEY>::_rightRotation(NodeType* node) {
    NodeType* aux = static_cast<NodeType*>(node->left);
    node->left = aux->right;
    aux->right = node;
    //fix
    node->height = 1 + std::max(_height(node->left), _height(node->right));
    aux->height = 1 + std::max(_height(aux->left), _height(aux->right));

    this->_rotationCount++;
    return aux;
}

template <typename VALUE, typename KEY>
typename AVLTree<VALUE, KEY>::NodeType* AVLTree<VALUE,KEY>::_leftRotation(NodeType* node) {
    NodeType* aux =node->Right();
    node->right = aux->left;
    aux->left = node;
    //fix
    node->height = 1 + std::max(_height(node->left), _height(node->right));
    aux->height = 1 + std::max(_height(aux->left), _height(aux->right));
    
    this->_rotationCount++;
    return aux;
}

template <typename VALUE, typename KEY>
typename AVLTree<VALUE, KEY>::NodeType* AVLTree<VALUE,KEY>::_fixup_node(NodeType* node, const KEY& key) {
    // Obtém balanço de p
    int bal = _balance(node);

    // Caso 1(a): rotação direita
    if (bal < -1 && key < node->left->key)
        return _rightRotation(node);

    // Caso 1(b): rotação dupla direita
    else if (bal < -1 && key > node->left->key) {
        node->left = _leftRotation(static_cast<NodeType*>(node->left));
        return _rightRotation(node);
    }

    // Caso 2(a): rotação esquerda
    else if (bal > 1 && key > node->right->key)
        return _leftRotation(node);

    // Caso 2(b): rotação dupla esquerda
    else if (bal > 1 && key < node->right->key) {
        node->right = _rightRotation(static_cast<NodeType*>(node->right));
        return _leftRotation(node);
    }

    // Atualiza altura deste nó ancestral p
    node->height = 1 + std::max(_height(node->left), _height(node->right));

    return node;
}

template <typename VALUE, typename KEY>
typename AVLTree<VALUE, KEY>::NodeType* AVLTree<VALUE,KEY>::_fixup_deletion(NodeType* node) {
    int bal = _balance(node);
    // O nó pode estar desregulado, há 4 casos a considerar
    if (bal > 1) {
        if (_balance(node->Right()) >= 0) {
            return _leftRotation(node);
        }
        else {
            node->right = _rightRotation(node->Right());
            return _leftRotation(node);
        }
    }
    else if (bal < -1) {
        if (_balance(node->Left()) <= 0) {
            return _rightRotation(node);
        }
        else {
            node->left = _leftRotation(node->Left());
            return _rightRotation(node);
        }
    }

    // Atualiza altura do nó
    node->height = 1 + std::max(_height(node->left), _height(node->right));

    return node;

}


/* --------------------------------------------------------------- */

template <typename VALUE, typename KEY>
typename AVLTree<VALUE, KEY>::NodeBase*
AVLTree<VALUE, KEY>::_createNode(const KEY& key, const VALUE& value) {
    return new NodeType(key, value);
}

template <typename VALUE, typename KEY>
typename AVLTree<VALUE, KEY>::NodeBase*
AVLTree<VALUE, KEY>::_add(const KEY& key, const VALUE& value, NodeBase* node) {
    NodeType* casted = static_cast<NodeType*>(node);

    if (casted == nullptr) {
        return _createNode(key, value);
    }
    else {
        if (key == casted->key) return casted;
        else if (key < casted->key) {
            casted->left = _add(key, value, casted->left);  // continua usando NodeBase*
        }
        else {
            casted->right = _add(key, value, casted->right);
        }

        // Rebalanceamento AVL
        casted = _fixup_node(casted, key);
        return casted;
    }
}

template <typename VALUE, typename KEY>
typename AVLTree<VALUE, KEY>::NodeBase*
AVLTree<VALUE, KEY>::_remove(const KEY& key, NodeBase* node) {
    NodeType* casted = static_cast<NodeType*>(node);

    if (casted == nullptr)
        return nullptr;

    if (key < casted->key) {
        casted->left = _remove(key, casted->left);
    }
    else if (key > casted->key) {
        casted->right = _remove(key, casted->right);
    }
    else {
        // Encontrou o nó
        if (casted->right == nullptr) {
            NodeType* child = casted->Left();
            delete casted;
            return child;
        }
        else {
            casted->right = _remove_successor(casted, 
                casted->Right() 
            );
        }
    }
}


template <typename VALUE, typename KEY>
typename AVLTree<VALUE, KEY>::NodeType* AVLTree<VALUE,KEY>::_remove_successor(NodeBase* root, NodeBase* node) {
    NodeType* response;
    if (node->left != nullptr) {
        node->left = _remove_successor(root, node->left);
    }
    else {
        root->key = node->key;
        NodeType* aux = static_cast<NodeType*>(node->right);
        delete node;
        return aux;
    }

    // Atualiza a altura do nó e regula o nó
    response = _fixup_deletion(static_cast<NodeType*>(node));
    return response;
}

template <typename VALUE, typename KEY>
int AVLTree<VALUE, KEY>::_height(const NodeBase* node) const {
    return node == nullptr ? 0 : static_cast<const NodeType*>(node)->height;
}


}}

#endif // !AVL_TREE_IMPL_H
