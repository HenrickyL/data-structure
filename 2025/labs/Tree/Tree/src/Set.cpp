
#include "../include/Set.h"

    
Set::Set() {
    _tree = new AVLTree<int>();
}

Set::~Set() {
    _tree->clear();
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
    return 0;
}
    
