#ifndef QXD_BST
#define QXD_BST

#include<string>
#include<vector>

namespace Perikan{namespace TREE{

struct Node;

class BinarySearchTree{
protected:
    Node* _root;
public:
    BinarySearchTree();
    virtual ~BinarySearchTree();

    void add(int key);
    void remove(int key);

    void clear();
    bool isEmpty() const;
    std::string to_string() const;
    int size() const;
    int height()const;
    int countLeafs() const;
    void removeLeafs();
    void print() const;
    
    bool contain(int key) const;
    //T find(int key) const;
    //int findByValue(T value) const;

    int countInterNodes() const;
    int max() const;

    void printInOrder() const;
    void printPreOrder() const;
    void printPosOrder() const;

    void printBFS() const;

    void printOrdered() const;
    std::string keyOrderedString() const;

    int keyMinimum() const;
    int keyMaximum() const;

    int keySuccessor(int key) const;
    int keyPredecessor(int key) const;


    std::vector<int> getKeys() const;

protected:
    virtual Node* _add(int key, Node* node);
    virtual Node* _remove(int key, Node* node);
    virtual bool _isNull(const Node*) const;

    Node* _clear(Node* node);
    std::string _to_string(Node* node) const;
    int _size(Node* node) const;
    int _height(const Node* node)const;
    int _countLeafs(const Node* node) const;
    Node* _removeLeafs(Node* node);
    void _print(const Node* node) const;
    const Node* _find(int key, const Node* node) const;
    //const Node* _findByValue(T value, const Node* node) const;
    int _countInterNodes(Node* node) const;
    Node* _max(Node* node) const;
    bool _isLeaf(const Node* node) const;
    void _printInOrder(const Node* node) const;
    void _printPreOrder(const Node* node) const;
    void _printPosOrder(const Node* node) const;

    void _printOrdered(const Node* node) const;
    std::string _keyOrderedString(const Node* node) const;

    const Node* _minimum(const Node* node) const;
    const Node* _maximum(const Node* node) const;
    
    const Node* _successor(int key, const Node* node, const Node* parent) const;
    const Node* _predecessor(int key, const Node* node, const Node* parent) const;


private:
    Node* _removeRoot(Node* node);
    void _auxGetKeys(const Node* node, std::vector<int>& ls) const;
};

}}

#endif