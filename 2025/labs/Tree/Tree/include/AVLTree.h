#ifndef QXD_AVL
#define QXD_AVL

#include"../include/BinarySearchTree.h"

namespace Perikan {
	namespace TREE {

template <typename T>
struct Node;


template <typename T>
class AVLTree : public BinarySearchTree<T> {
public:
	AVLTree();
	~AVLTree();

	int height() const;
protected:
	Node<T>* _add(int key, T value, Node<T>* node) override;
	Node<T>* _remove(int key, Node<T>* node) override;

	int _height(const Node<T>* node) const;
	int _balance(const Node<T>* node) const;
	Node<T>* _rightRotation(Node<T>* node);
	Node<T>* _leftRotation(Node<T>* node);
	Node<T>* _fixup_node(Node<T>* node, int key);
	Node<T>* _fixup_deletion(Node<T>* node);
	Node<T>* _remove_successor(Node<T>* root, Node<T>* node);
};
// ---
}};

#include "../src/AVLTree.impl.h"
#endif