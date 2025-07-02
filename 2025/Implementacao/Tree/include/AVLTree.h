#ifndef QXD_AVL
#define QXD_AVL

#include"../include/BinarySearchTree.h"
#include "../include/AVLNode.h"

namespace Perikan {namespace TREE {

template <typename VALUE, typename KEY = int>
class AVLTree : public BinarySearchTree<VALUE,KEY> {
public:
	AVLTree();
	~AVLTree();


    int balance() const;

protected:
    using NodeBase = Node<VALUE, KEY>;
    using NodeType = AVLNode<VALUE, KEY>;

    NodeBase* _add(const KEY& key, const VALUE& value, NodeBase* node) override;
    NodeBase* _remove(const KEY& key, NodeBase* node) override;
    NodeBase* _createNode(const KEY& key, const VALUE& value) override;
    int _height(const NodeBase* node) const override;
    //NodeBase* _getRoot() const override;
    //void _setRoot(NodeBase* root) override;

    int _balance(const NodeType* node) const;
    NodeType* _rightRotation(NodeType* node);
    NodeType* _leftRotation(NodeType* node);
    NodeType* _fixup_node(NodeType* node, int key);
    NodeType* _fixup_deletion(NodeType* node);
    NodeType* _remove_successor(NodeBase* root, NodeBase* node);
};
// ---
}};

#include "../src/AVLTree.impl.h"

#endif