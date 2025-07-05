#ifndef QXD_BST
#define QXD_BST

#include<string>
#include<vector>
#include "Node.h"

namespace Perikan{namespace TREE{

template <typename VALUE, typename KEY=int>
class BinarySearchTree {
protected:
    Node<VALUE,KEY>* _root;
public:
    BinarySearchTree();
    virtual ~BinarySearchTree();

    virtual void add(const KEY& key, const VALUE& value);
    virtual void remove(const KEY& key);

    const VALUE find(const KEY& key)const;
    void clear();
    bool isEmpty() const;
    std::string to_string() const;
    int size() const;
    int height()const;
    int countLeafs() const;
    void removeLeafs();
    void print() const;
    void setValue(const KEY& key, const VALUE& Value);
    
    bool contains(const KEY& key) const;
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

    KEY keySuccessor(const KEY& key) const;
    KEY keyPredecessor(const KEY& key) const;


    std::vector<int> getKeys() const;

protected:
    virtual Node<VALUE, KEY>* _add(const KEY& key, const VALUE& value, Node<VALUE, KEY>* node);
    virtual Node<VALUE, KEY>* _remove(const KEY& key, Node<VALUE, KEY>* node);
    virtual bool _isNull(const Node<VALUE, KEY>*) const;
    virtual Node<VALUE, KEY>* _getNull() const;

    virtual Node<VALUE, KEY>* _createNode(const KEY& key, const VALUE& value);
    virtual int _height(const Node<VALUE, KEY>* node)const;
    virtual void _setRoot(Node<VALUE, KEY>* root);
    virtual void _print(const Node<VALUE, KEY>* node) const;


    virtual Node<VALUE, KEY>* _clear(Node<VALUE, KEY>* node);
    std::string _to_string(Node<VALUE, KEY>* node) const;
    int _size(Node<VALUE, KEY>* node) const;
    int _countLeafs(const Node<VALUE, KEY>* node) const;
    Node<VALUE, KEY>* _removeLeafs(Node<VALUE, KEY>* node);
    const Node<VALUE, KEY>* _find(const KEY& key, const Node<VALUE, KEY>* node) const;
    //const Node<VALUE, KEY>* _findByValue(T value, const Node<VALUE, KEY>* node) const;
    int _countInterNodes(Node<VALUE, KEY>* node) const;
    Node<VALUE, KEY>* _max(Node<VALUE, KEY>* node) const;
    bool _isLeaf(const Node<VALUE, KEY>* node) const;
    void _printInOrder(const Node<VALUE, KEY>* node) const;
    void _printPreOrder(const Node<VALUE, KEY>* node) const;
    void _printPosOrder(const Node<VALUE, KEY>* node) const;

    void _printOrdered(const Node<VALUE, KEY>* node) const;
    std::string _keyOrderedString(const Node<VALUE, KEY>* node) const;

    const Node<VALUE, KEY>* _minimum(const Node<VALUE, KEY>* node) const;
    const Node<VALUE, KEY>* _maximum(const Node<VALUE, KEY>* node) const;
    
    const Node<VALUE, KEY>* _successor(const KEY& key, const Node<VALUE, KEY>* node, const Node<VALUE, KEY>* parent) const;
    const Node<VALUE, KEY>* _predecessor(const KEY& key, const Node<VALUE, KEY>* node, const Node<VALUE, KEY>* parent) const;


private:
    Node<VALUE, KEY>* _removeRoot(Node<VALUE, KEY>* node);
    void _auxGetKeys(const Node<VALUE, KEY>* node, std::vector<int>& ls) const;

};

}}

#include "../src/BinarySearchTree.impl.h"

#endif