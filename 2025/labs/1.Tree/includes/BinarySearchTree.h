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
    ~BinarySearchTree();

    void clear();
    void add(int key);
    bool isEmpty() const;
    std::string to_string() const;
    int countNodes() const;
    int countLeafs() const;
    void removeLeafs();

private:
    Node* _clear(Node* node);
    std::string _to_string(Node* node) const;
    Node* _add(int key, Node* node);
    int _countNodes(Node* node) const;
    int _countLeafs(Node* node) const;
    Node* _removeLeafs(Node* node);
};

}}
#endif