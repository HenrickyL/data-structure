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
protected:
	using NodeBase = Node<VALUE, KEY>;
	using NodeType = RBNode<VALUE, KEY>;


	bool _isNull(const NodeBase* node) const override;
	//NodeBase* _add(const KEY& key, const VALUE& value, NodeBase* node) override;
	//NodeBase* _remove(const KEY& key, NodeBase* node) override;
	//NodeBase* _createNode(const KEY& key, const VALUE& value) override;
	NodeType* _createNode(const KEY& key, const VALUE& value, NodeType* father) const;


	int _blackHeight(const NodeType* node) const;
};

}}

#include "../src/RBTree.impl.h"

#endif