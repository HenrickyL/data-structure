#ifndef RBTREE_H
#define RBTREE_H

#include "../include/BinarySearchTree.h"
#include "../include/RBNode.h"

namespace Perikan {namespace TREE {


template <typename VALUE, typename KEY = int>
class RBTree : public BinarySearchTree<VALUE,KEY> {
private:
	RBNode<VALUE,KEY>* _nill;
	int _rotationCount=0;
public:
	RBTree();
	~RBTree();


	void add(const KEY& key, const VALUE& value) override;
	void remove(const KEY& key) override;

	inline int getRotationCount() const { return _rotationCount; }
	void resetMetrics() override;

protected:
	using NodeBase = Node<VALUE, KEY>;
	using NodeType = RBNode<VALUE, KEY>;


	bool _isNull(const NodeBase* node) const override;
	//NodeBase* _add(const KEY& key, const VALUE& value, NodeBase* node) override;
	//NodeBase* _createNode(const KEY& key, const VALUE& value) override;
	void _print(const Node<VALUE, KEY>* node) const override;
	void _remove(NodeType* z);
	Node<VALUE, KEY>* _getNull() const override;
	Node<VALUE, KEY>* _clear(Node<VALUE, KEY>* node) override;


	NodeType* _minimum(NodeType* node) const;
	void _removeFixup(NodeType* x);
	void _transplant(NodeType* u, NodeType* v);
	int _blackHeight(const NodeType* node) const;
	void _rightRotation(NodeType* node);
	void _leftRotation(NodeType* node);
	void _add(const KEY& key, const VALUE& value);
	void _addFixup(NodeType* node);
};

}}

#include "../src/RBTree.impl.h"

#endif


/**

1. Cada no e vermelho ou preto.
2. A raiz e preta.
3. Toda folha (NIL) e preta.
4. Um no vermelho nao pode ter filhos vermelhos.
5. Todo caminho simples da raiz ate as folhas contem o mesmo numero de nos pretos.

**/