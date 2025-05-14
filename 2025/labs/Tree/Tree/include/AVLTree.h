#ifndef QXD_AVL
#define QXD_AVL

#include"../include/BinarySearchTree.h"

namespace Perikan {
	namespace TREE {

struct Node;


class AVLTree : public BinarySearchTree {
public:
	AVLTree();
	~AVLTree();

	int height() const;
protected:
	Node* _add(int key, Node* node) override;
	Node* _remove(int key, Node* node) override;

	int _height(const Node* node) const;
	int _balance(const Node* node) const;
	Node* _rightRotation(Node* node);
	Node* _leftRotation(Node* node);
	Node* _fixup_node(Node* node, int key);
	Node* _fixup_deletion(Node* node);
	Node* _remove_successor(Node* root, Node* node);
};
// ---
}};

#endif