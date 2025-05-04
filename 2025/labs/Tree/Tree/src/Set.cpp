
#include "../include/Set.h"

    
Set::Set() {
    _tree = new AVLTree<int>();
}

Set::~Set() {
    //_tree->clear();
    delete _tree;
}

void Set::insert(int value) {
    this->_tree->add(value);
}


void Set::erase(int value) {
    _tree->remove(value);
}


bool Set::contains(int value) const {
    return _tree->contain(value);
}

void Set::clear() {
    _tree->clear();
}


int Set::minimum() const {
    return _tree->keyMinimum();
}
int Set::maximum() const {
    return _tree->keyMaximum();
}

int Set::successor(int value) const {
    return _tree->keySuccessor(value);
}
int Set::predecessor(int value) const {
    return _tree->keyPredecessor(value);
}


bool Set::empty() const {
    return _tree->isEmpty();
}
size_t Set::size() const {
    return _tree->size();
}


Set Set::unionSet(const Set& set1, const Set& set2) {
    const Set& larger = (set1.size() > set2.size()) ? set1 : set2;
    const Set& smaller = (set1.size() > set2.size()) ? set2 : set1;

    Set response;
    //add small in large
    for (int elem : larger._tree->getKeys()) {
        response.insert(elem);
    }
    for (int elem : smaller._tree->getKeys()) {
        response.insert(elem);
    }
    return response;
}
Set Set::intersection(const Set& set1, const Set& set2){
    const Set& larger = (set1.size() > set2.size()) ? set1 : set2;
    const Set& smaller = (set1.size() > set2.size()) ? set2 : set1;

    Set response;
    //add small in large
    for (int elem : larger._tree->getKeys()) {
        response.insert(elem);
    }
    for (int elem : smaller._tree->getKeys()) {
        if (response.contains(elem)) {
            response.insert(elem);
        }
    }
    return response;
}
Set Set::difference(const Set& set1, const Set& set2){
    const Set& larger = (set1.size() > set2.size()) ? set1 : set2;
    const Set& smaller = (set1.size() > set2.size()) ? set2 : set1;

    Set response;
    //add small in large
    for (int elem : larger._tree->getKeys()) {
        response.insert(elem);
    }
    for (int elem : smaller._tree->getKeys()) {
        if (!response.contains(elem)) {
            response.insert(elem);
        }
    }
    return response;
}


void Set::print(std::string title) const {
    std::cout << title << ": ";
    _tree->printOrdered();
}
