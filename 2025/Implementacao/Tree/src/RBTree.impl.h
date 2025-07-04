#ifndef RB_TREE_IMPL_H
#define RB_TREE_IMPL_H

#include "../include/RBTree.h"
#include<queue>
namespace Perikan {namespace TREE {


////
template <typename VALUE, typename KEY>
RBTree<VALUE,KEY>::RBTree() : BinarySearchTree<VALUE,KEY>() {
	this->_nill = new RBNode<VALUE,KEY>(KEY{}, VALUE{}, BLACK);
    this->_nill->left = this->_nill;
    this->_nill->right = this->_nill;
    this->_nill->parent = this->_nill;
    this->_root = this->_nill; // importante
}


template <typename VALUE, typename KEY>
RBTree<VALUE, KEY>::~RBTree() {
	this->clear();
	delete this->_nill;
    this->_root = nullptr;
}

template <typename VALUE, typename KEY>
Node<VALUE, KEY>* RBTree<VALUE, KEY>::_getNull() const {
    return static_cast<Node<VALUE, KEY>*>(this->_nill);
}


template <typename VALUE, typename KEY>
Node<VALUE, KEY>* RBTree<VALUE, KEY>::_clear(Node<VALUE, KEY>* node) {
    if (node == this->_nill) return node;
    std::queue<Node<VALUE, KEY>*> q;
    q.push(node);
    while (!q.empty()) {
        Node<VALUE, KEY>* current = q.front();
        q.pop();
        if (current->left != this->_nill)
            q.push(current->left);
        if (current->right != this->_nill)
            q.push(current->right);
        delete current;
    }
    return static_cast<Node<VALUE, KEY>*>(this->_nill);
}



template <typename VALUE, typename KEY>
bool RBTree<VALUE, KEY>::_isNull(const NodeBase* node) const {
    const NodeType* current = static_cast<const NodeType*>(node);
    return node == this->_nill;
}


template <typename VALUE, typename KEY>
int RBTree<VALUE, KEY>::_blackHeight(const NodeType* node) const {
    if (this->_isNull(node)) return 1;
    else {
        int bh_left = _blackHeight(node->Left());

        if (node->color == BLACK)
            return 1 + bh_left;
        else
            return bh_left;
    }
}

template <typename VALUE, typename KEY>
void RBTree<VALUE, KEY>::_rightRotation(NodeType* y) {
    NodeType* x = y->Left();
    y->left = x->right;

    if (x->right != _nill)
        x->Right()->parent = y;

    x->parent = y->parent;

    if (y->parent == _nill)
        this->_root = x;
    else if (y == y->parent->Right())
        y->parent->right = x;
    else
        y->parent->left = x;

    x->right = y;
    y->parent = x;
}


template <typename VALUE, typename KEY>
void RBTree<VALUE, KEY>::_leftRotation(NodeType* x) {
    NodeType* y = x->Right();
    x->right = y->Left();

    if (y->left != _nill)
        y->Left()->parent = x;

    y->parent = x->parent;

    if (x->parent == _nill)
        this->_root = y;
    else if (x == x->parent->Left())
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

template <typename VALUE, typename KEY>
void RBTree<VALUE, KEY>::_add(const KEY& key, const VALUE& value) {
    NodeType* z = new RBNode<VALUE, KEY>(key, value, RED, nullptr, this->_nill, this->_nill);
    NodeType* y = _nill;
    NodeType* x = static_cast<NodeType*>(this->_root);

    while (x != _nill) {
        y = x;
        if (z->key < x->key)
            x = x->Left();
        else
            x = x->Right();
    }

    z->parent = y;
    if (y == _nill)
        this->_root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    z->left = _nill;
    z->right = _nill;
    z->color = RED;

    _addFixup(z);
}

template <typename VALUE, typename KEY>
void RBTree<VALUE, KEY>::_addFixup(NodeType* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            NodeType* y = z->parent->parent->Right(); // tio

            // Caso 1: tio vermelho -> recolore
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                // Caso 2: z e filho a direita -> rotacao esquerda
                if (z == z->parent->right) {
                    z = z->parent;
                    _leftRotation(z);
                }

                // Caso 3: z e filho a esquerda -> rotacao direita
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                _rightRotation(z->parent->parent);
            }
        }
        else {
            // Espelhamento: pai esta a direita do avo
            NodeType* y = static_cast<NodeType*>(z->parent->parent->left); // tio

            // Caso 1: tio vermelho
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                // Caso 2: z e filho a esquerda -> rotacao direita
                if (z == z->parent->left) {
                    z = z->parent;
                    _rightRotation(z);
                }

                // Caso 3: z e filho a direita -> rotacao esquerda
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                _leftRotation(z->parent->parent);
            }
        }
    }

    // Regra 2: a raiz deve ser preta
    static_cast<NodeType*>(this->_root)->color = BLACK;
}

template <typename VALUE, typename KEY>
void RBTree<VALUE, KEY>::add(const KEY& key, const VALUE& value) {
    _add(key, value);
}

template <typename VALUE, typename KEY>
void RBTree<VALUE, KEY>::_print(const Node<VALUE, KEY>* n) const {
    const RBNode<VALUE, KEY>* node = static_cast<const RBNode<VALUE, KEY>*>(n);
    if (!_isNull(node)) {
        std::cout << node->to_string() << " ";
        _print(node->Left());
        _print(node->Right());
    }
    else {
        std::cout << " #";
    }
}

template <typename VALUE, typename KEY>
void RBTree<VALUE, KEY>::_remove(NodeType* z) {
    NodeType* y = z;
    NodeType* x;
    bool yOriginalColor = y->color;

    if (z->left == this->_nill) {
        x = z->Right();
        _transplant(z, z->Right());
    }
    else if (z->right == this->_nill) {
        x = z->Left();
        _transplant(z, z->Left());
    }
    else {
        y = _minimum(z->Right());
        yOriginalColor = y->color;
        x = y->Right();

        if (y->parent == z)
            x->parent = y;
        else {
            _transplant(y, y->Right());
            y->right = z->Right();
            y->Right()->parent = y;
        }

        _transplant(z, y);
        y->left = z->Left();
        y->Left()->parent = y;
        y->color = z->color;
    }

    delete z;

    if (yOriginalColor == BLACK)
        _removeFixup(x);
}

template <typename VALUE, typename KEY>
void RBTree<VALUE, KEY>::_removeFixup(NodeType* x) {
    while (x != this->_root && x->color == BLACK) {
        if (x == x->parent->left) {
            NodeType* w = x->parent->Right(); // irmão

            // Caso 1: irmão vermelho
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                _leftRotation(x->parent);
                w = x->parent->Right();
            }

            // Caso 2: irmão e filhos pretos
            if (w->Left()->color == BLACK && w->Right()->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                // Caso 3: irmão preto, filho esquerdo vermelho, direito preto
                if (w->Right()->color == BLACK) {
                    w->Left()->color = BLACK;
                    w->color = RED;
                    _rightRotation(w);
                    w = x->parent->Right();
                }

                // Caso 4: irmão preto, filho direito vermelho
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->Right()->color = BLACK;
                _leftRotation(x->parent);
                x = static_cast<NodeType*>(this->_root);
            }
        }
        else {
            // Espelhamento
            NodeType* w =x->parent->Left();

            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                _rightRotation(x->parent);
                w = x->parent->Left();
            }

            if (w->Right()->color == BLACK && w->Left()->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->Left()->color == BLACK) {
                    w->Right()->color = BLACK;
                    w->color = RED;
                    _leftRotation(w);
                    w = static_cast<NodeType*>(x->parent->left);
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->Left()->color = BLACK;
                _rightRotation(x->parent);
                x = static_cast<NodeType*>(this->_root);
            }
        }
    }

    x->color = BLACK;
}

template <typename VALUE, typename KEY>
void RBTree<VALUE, KEY>::_transplant(NodeType* u, NodeType* v) {
    if (u->parent == this->_nill)
        this->_root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    v->parent = u->parent;
}

template <typename VALUE, typename KEY>
typename RBTree<VALUE, KEY>::NodeType*
RBTree<VALUE, KEY>::_minimum(NodeType* node) const {
    while (node->left != this->_nill) {
        node = node->Left();
    }
    return node;
}

template <typename VALUE, typename KEY>
void RBTree<VALUE, KEY>::remove(const KEY& key) {
    NodeType* z = static_cast<NodeType*>(this->_root);

    while (z != this->_nill) {
        if (key == z->key)
            break;
        else if (key < z->key)
            z = z->Left();
        else
            z = z->Right();
    }

    if (z == this->_nill)
        return; // Nó não encontrado

    _remove(z);
}




}}

#endif
