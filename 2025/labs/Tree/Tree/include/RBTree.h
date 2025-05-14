#ifndef RBTREE_H
#define RBTREE_H

#include "../include/BinarySearchTree.h"
namespace Perikan {namespace TREE {

struct Node;

class RBTree : public BinarySearchTree {
private:
	Node* _nill;
public:
	RBTree();
	~RBTree();

};

}}

#endif