#ifndef RB_TREE_IMPL_H
#define RB_TREE_IMPL_H

#include "../include/RBTree.h"

namespace Perikan {namespace TREE {


////
template <typename VALUE, typename KEY>
RBTree<VALUE,KEY>::RBTree() : BinarySearchTree<VALUE,KEY>() {
	_nill = new RBNode<VALUE,KEY>(KEY{}, VALUE{}, BLACK, nullptr);
}

template <typename VALUE, typename KEY>
RBTree<VALUE, KEY>::~RBTree() {
	this->clear();
	delete this->_nill;
	delete this->_root;
}


template <typename VALUE, typename KEY>
bool RBTree<VALUE, KEY>::_isNull(const NodeBase* node) const {
    const NodeType* current = static_cast<const NodeType*>(node);
    return node == this->_nill;
}

template <typename VALUE, typename KEY>
typename RBTree<VALUE, KEY>::NodeType*
RBTree<VALUE, KEY>::_createNode(const KEY& key, const VALUE& value, NodeType* father) const{
	return new RBNode<VALUE, KEY>(key, value, true, father, this->_nil, this->_nil);
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



}}

#endif
