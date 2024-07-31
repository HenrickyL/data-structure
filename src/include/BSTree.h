#ifndef UT_BS_TREE_H
#define UT_BS_TREE_H


#include <iostream>
#include <string>
#include "Node.h"

namespace EDA{
    // template<typename T>
    // struct Node;


    //Binary Search Tree
    template<typename T>
    class BSTree{
        private:
            Node<T>* _node = nullptr;
        protected:
            Node<T>* _root = nullptr;

            virtual bool _Insert(Node<T>* root, T value);
            void _Clear(Node<T>* root);
            void _Print(Node<T>* root)const;
        public:
            ~BSTree();
            bool IsEmpty() const;
            virtual bool Insert(T item);
            void Print()const;


    };

    //--------------------------------------------------------------------------

    // #include "BSTree.inl"
    template<typename T>
    BSTree<T>::~BSTree(){
        _Clear(_root);
        std::cout << "\nTree Clear!" <<std::endl;
    }

    template<typename T>
    bool BSTree<T>::IsEmpty() const {
        return this->_root == nullptr;
    }

    template<typename T>
    bool BSTree<T>::Insert(T value) {
        _node = _root;
        return this->_Insert(_node, value);
    }

    template<typename T>
    bool BSTree<T>::_Insert(Node<T>* root, T value){
        if(root != nullptr){
            if(root->key ==value) return false;
            else if(value < root->key){
                return _Insert(root->left, value);
            }else{
                return _Insert(root->right, value);
            }
        }else{
            Node<T>* newNode = new Node<T>(value);
            root = newNode;
            return true;
        }
    }

    template<typename T>
    void BSTree<T>::_Clear(Node<T>* root){
        if(root != nullptr){
            _Clear(root->left);
            _Clear(root->right);
            delete root;
        }
    }

    template<typename T>
    void BSTree<T>::Print()const{
        std::cout << "Print" << std::endl;
        this->_Print(_root);
    }

    template<typename T>
    void BSTree<T>::_Print(Node<T>* root)const{
        if(root != nullptr){
            std::cout << std::to_string(root->key) << " ";
            _Print(root->left);
            _Print(root->right);
        }else{
            std::cout << "Null ";
        }
    }




}
#endif