#ifndef QXD_SET
#define QXD_SET

#include "../include/AVLTree.h"
using namespace Perikan::TREE;


class Set {
private:
    AVLTree<int>* _tree;
    std::string _name ;

public:
    Set();
    ~Set();

    // Basic operations
    void insert(int value);
    void erase(int value);
    bool contains(int value) const;
    void clear();
    void swap(Set& other);

    // Query operations
    int minimum() const;
    int maximum() const;
    int successor(int value) const;
    int predecessor(int value) const;
    bool empty() const;
    size_t size() const;

    // Binary operations
    static void unionSet(const Set& set1, const Set& set2, Set& response);
    static void intersection(const Set& set1, const Set& set2, Set& response);
    static void difference(const Set& set1, const Set& set2, Set& response);

    void print(std::string title);

private:
    // Helper methods for binary operations
    /*void unionHelper(Node<int>* node);
    void intersectionHelper(Node<int>* node, const Set& other);
    void differenceHelper(Node<int>* node, const Set& other);*/
};

#endif