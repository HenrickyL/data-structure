#ifndef QXD_SET
#define QXD_SET

#include "../include/AVLTree.h"

namespace Perikan {namespace TREE {

template <typename T>
class Set {
private:
    AVLTree<T> _tree;

public:
    Set();
    ~Set();

    // Basic operations
    void insert(const T& value);
    void erase(const T& value);
    bool contains(const T& value) const;
    void clear();
    void swap(Set<T>& other);

    // Query operations
    T minimum() const;
    T maximum() const;
    T successor(const T& value) const;
    T predecessor(const T& value) const;
    bool empty() const;
    size_t size() const;

    // Binary operations
    static Set<T> unionSet(const Set<T>& set1, const Set<T>& set2);
    static Set<T> intersection(const Set<T>& set1, const Set<T>& set2);
    static Set<T> difference(const Set<T>& set1, const Set<T>& set2);

private:
    // Helper methods for binary operations
    void unionHelper(Node<T>* node);
    void intersectionHelper(Node<T>* node, const Set<T>& other);
    void differenceHelper(Node<T>* node, const Set<T>& other);
};

}}
#include "../src/Set.impl.h"
#endif