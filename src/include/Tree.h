#ifndef UT_TREE_H
#define UT_TREE_H

#include "Node.h"

namespace EDA{
    template<typename T>
    class Tree{
        protected:
            Node<T>* _root = nullptr;
        public:
            bool IsEmpty() const;
            void Add(Node<T> item);
    };

    #include "Tree.inl"
}
#endif