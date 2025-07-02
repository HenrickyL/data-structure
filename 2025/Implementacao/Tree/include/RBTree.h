#ifndef RBTREE_H
#define RBTREE_H

#include "../include/BinarySearchTree.h"
#include "../include/RBNode.h"

namespace Perikan {namespace TREE {


template <typename VALUE, typename KEY = int>
class RBTree : public BinarySearchTree<VALUE,KEY> {
private:
	RBNode<VALUE,KEY>* _nill;
public:
	RBTree();
	~RBTree();
};

}}

#include "../src/RBTree.impl.h"

#endif