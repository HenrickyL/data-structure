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


}}

#endif
