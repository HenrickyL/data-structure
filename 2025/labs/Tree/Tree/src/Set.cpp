
#include "../include/Set.h"

    
Set::Set() {
    _tree = new AVLTree<int>();
}

Set::~Set() {
    _tree->clear();
    delete _tree;
}
    
    
