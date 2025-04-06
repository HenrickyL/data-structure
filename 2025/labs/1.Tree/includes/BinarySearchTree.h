#ifndef QXD_BST
#define QXD_BST

namespace Perikan{
namespace TREE{

struct Node;

class BinarySearchTree{
private:
    Node* _root;
public:
    BinarySearchTree();
    bool isEmpty() const;
};

}}
#endif