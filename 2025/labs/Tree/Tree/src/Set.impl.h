#ifndef QXD_SET_IMPL
#define QXD_SET_IMPL

#include "../include/Set.h"

namespace Perikan {
    namespace TREE {
    
template<typename T>
Set<T>::Set() {
    _tree = new AVLTree<T>();
}

template<typename T>
Set<T>::~Set() {
    _tree->clear();
    delete _tree;
}
    
    
}}
#endif