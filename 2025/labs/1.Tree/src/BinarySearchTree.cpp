#include "../includes/BinarySearchTree.h"


namespace Perikan{
    namespace TREE{

struct Node{
    int key;
    Node* left;
    Node* right;
};


BinarySearchTree::BinarySearchTree(): _root(nullptr){

}

bool BinarySearchTree::isEmpty() const{
    return this->_root == nullptr;
}

}}