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

    virtual void add(int key);
    virtual void remove(int key);

    void clear();
    bool isEmpty() const;
    std::string to_string() const;
    int size() const;
    int height()const;
    int countLeafs() const;
    void removeLeafs();
    void print() const;
    bool find(int key) const;
    int countInterNodes() const;
    int max() const;

    void printInOrder() const;
    void printPreOrder() const;
    void printPosOrder() const;

    void printBFS() const;


protected:
    virtual Node* _add(int key, Node* node);
    virtual Node* _remove(int key, Node* node);


    Node* _clear(Node* node);
    std::string _to_string(Node* node) const;
    int _size(Node* node) const;
    int _height(const Node* node)const;
    int _countLeafs(const Node* node) const;
    Node* _removeLeafs(Node* node);
    void _print(const Node* node) const;
    const Node* _find(int key, const Node* node) const;
    int _countInterNodes(Node* node) const;
    Node* _max(Node* node) const;
    bool _isLeaf(const Node* node) const;

    void _printInOrder(const Node* node) const;
    void _printPreOrder(const Node* node) const;
    void _printPosOrder(const Node* node) const;
private:
    Node* _removeRoot(Node* node);

};

}}
#endif