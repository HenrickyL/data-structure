
#include "../include/Set.h"
#include <iostream>
    
Set::Set(std::string name) {
    _tree = new AVLTree();
    _name = name;
    std::cout << "Set constroy\n";
}

Set::~Set() {
    //_tree->clear();
    delete _tree;
    std::cout << "[" << _name<< "]:" << "Set Destroy\n";
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

void Set::swap(Set& other) {
    AVLTree* aux = _tree;
    _tree = other._tree;
    other._tree = aux;
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


void Set::unionSet(const Set& set1, const Set& set2, Set& response) {
    const Set& larger = (set1.size() > set2.size()) ? set1 : set2;
    const Set& smaller = (set1.size() > set2.size()) ? set2 : set1;

    //add small in large
    for (int elem : larger._tree->getKeys()) {
        response.insert(elem);
    }
    for (int elem : smaller._tree->getKeys()) {
        response.insert(elem);
    }
}
void Set::intersection(const Set& set1, const Set& set2, Set& response){
    const Set& larger = (set1.size() > set2.size()) ? set1 : set2;
    const Set& smaller = (set1.size() > set2.size()) ? set2 : set1;

    //add small in large
    for (int elem : smaller._tree->getKeys()) {
        if (larger.contains(elem)) {
            response.insert(elem);
        }
    }
}
void Set::difference(const Set& set1, const Set& set2, Set& response){
    const Set& larger = (set1.size() > set2.size()) ? set1 : set2;
    const Set& smaller = (set1.size() > set2.size()) ? set2 : set1;

    //add small in large
    for (int elem : larger._tree->getKeys()) {
        response.insert(elem);
    }
    for (int elem : smaller._tree->getKeys()) {
        response.erase(elem);
    }
}


void Set::print() const {
    std::cout << _name << ": ";
    _tree->printOrdered();
}
