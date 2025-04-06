#ifndef QXD_BST
#define QXD_BST

#include<string>

namespace Perikan{namespace TREE{

struct Node;

class BinarySearchTree{
protected:
    Node* _root;
public:
    BinarySearchTree();

    void add(int key);
    bool isEmpty() const;
    std::string to_string() const;
    int countNodes() const;
private:
    std::string _to_string(Node* node) const;
    Node* _add(int key, Node* node);
    int _countNodes(Node* node) const;
};

}}
#endif