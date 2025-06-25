#include "../include/RBTree.h"

namespace Perikan {namespace TREE {

constexpr int RED = 1;;
constexpr int BLACK = 0;;

struct Node {
	int key;
	bool color; //0 black 1 red
	Node* left;
	Node* right;
	Node* father;

	Node(int k, bool c, Node* f, Node* l = nullptr, Node* r = nullptr) : key(k), color(c),father(f), left(l), right(r) {}
};

////

RBTree::RBTree() {
	_nill = new Node(0, BLACK, nullptr);
}
RBTree::~RBTree() {
	clear();
	delete _nill;
	delete _root;
}




}}

