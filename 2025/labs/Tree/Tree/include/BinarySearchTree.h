#ifndef QXD_BST
#define QXD_BST

#include<string>
#include<vector>

namespace Perikan{namespace TREE{

template <typename T>
struct Node;

template <typename T>
class BinarySearchTree{
protected:
    Node<T>* _root;
public:
    BinarySearchTree();
    ~BinarySearchTree();

    void add(int key, T value = T());
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
    T find(int key) const;
    int findByValue(T value) const;

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
    virtual Node<T>* _add(int key, T value, Node<T>* node);
    virtual Node<T>* _remove(int key, Node<T>* node);


    Node<T>* _clear(Node<T>* node);
    std::string _to_string(Node<T>* node) const;
    int _size(Node<T>* node) const;
    int _height(const Node<T>* node)const;
    int _countLeafs(const Node<T>* node) const;
    Node<T>* _removeLeafs(Node<T>* node);
    void _print(const Node<T>* node) const;
    const Node<T>* _find(int key, const Node<T>* node) const;
    const Node<T>* _findByValue(T value, const Node<T>* node) const;
    int _countInterNodes(Node<T>* node) const;
    Node<T>* _max(Node<T>* node) const;
    bool _isLeaf(const Node<T>* node) const;
    void _printInOrder(const Node<T>* node) const;
    void _printPreOrder(const Node<T>* node) const;
    void _printPosOrder(const Node<T>* node) const;

    void _printOrdered(const Node<T>* node) const;
    std::string _keyOrderedString(const Node<T>* node) const;

    const Node<T>* _minimum(const Node<T>* node) const;
    const Node<T>* _maximum(const Node<T>* node) const;
    
    const Node<T>* _successor(int key, const Node<T>* node, const Node<T>* parent) const;
    const Node<T>* _predecessor(int key, const Node<T>* node, const Node<T>* parent) const;

private:
    Node<T>* _removeRoot(Node<T>* node);
    void _auxGetKeys(const Node<T>* node, std::vector<int>& ls) const;
};

}}

#include "../src/BinarySearchTree.impl.h"
#endif