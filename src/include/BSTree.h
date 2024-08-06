#ifndef UT_BS_TREE_H
#define UT_BS_TREE_H


#include <iostream>
#include <string>
#include "Node.h"

#include <queue>

namespace EDA{
    // template<typename T>
    // struct Node;


    //Binary Search Tree
    template<typename T>
    class BSTree{
        protected:
            Node<T>* _root = nullptr;

            Node<T>* _Clear(Node<T>* root);
            void _Print(Node<T>* root)const;


            virtual Node<T>* _Insert(Node<T>* root, T value);
            // Breadth First Search
            Node<T>* _BFS(Node<T>* root, T value) const;
            Node<T>* _DFS(Node<T>* root, T value) const;
            Node<T>* _Search(Node<T>* root, T value) const;


        public:
            ~BSTree();
            bool IsEmpty() const;
            void Print()const;
            const Node<T>* Search(T value) const;

            void Clear();


            void Insert(T item);
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
    void BSTree<T>::Insert(T value) {
        _root = this->_Insert(_root, value);
    }

    template<typename T>
    Node<T>* BSTree<T>::_Insert(Node<T>* root, T value){
        if(root != nullptr){
            // if(root->key ==value) return root;
            if(value < root->key){
                root->left = _Insert(root->left, value);
                root->left->feather = root;
                
            }else{
                root->right = _Insert(root->right, value);
                root->right->feather = root;
            }
            return root;
        }else{
            Node<T>* newNode = new Node<T>(value);
            return newNode;
        }
    }

    template<typename T>
    void BSTree<T>::Clear(){
        _root = _Clear(_root);
    }


    template<typename T>
    Node<T>* BSTree<T>::_Clear(Node<T>* root){
        if(root != nullptr){
            root->left = _Clear(root->left);
            root->right = _Clear(root->right);
            delete root;
        }
        return nullptr;
    }

    template<typename T>
    void BSTree<T>::Print() const {
        if(_root == nullptr){
            std::cout << "\nNull" <<std::endl;
        }
        this->_Print(_root);
    }

    template<typename T>
    void BSTree<T>::_Print(Node<T>* root)const{
        if(root != nullptr){
            std::cout << std::to_string(root->key) << " ";
            _Print(root->left);
            _Print(root->right);
        }
        else std::cout << "#" << " ";
    }

    template<typename T>
    Node<T>* BSTree<T>::_BFS(Node<T>* root, T value) const{
        Node<T>* node  = root;
        Node<T>* father  = nullptr;

        std::queue<Node<T>*> frontier;
        frontier.push(node);

        while(!frontier.empty()){
            node = frontier.front();
            frontier.pop();

            if(node->key == value){
                return node;
            }else{
                if(node->left)
                    frontier.push(node->left);
                if(node->right)
                    frontier.push(node->right);
            }
        }
        return nullptr;
    }
    template<typename T>
    Node<T>* BSTree<T>::_DFS(Node<T>* root, T value) const{
        if(root != nullptr){
            if(root->key == value) return root;
            else{
                Node<T>* node;
                node = _DFS(root->left, value);
                return node != nullptr ? node :  _DFS(root->right, value);
            }

        }else{
            return nullptr;
        }
    }

    template<typename T>
    Node<T>* BSTree<T>::_Search(Node<T>* root, T value) const{
        if(root != nullptr){
            if(root->key == value) return root;
            else{
                std::cout << root->key << ">";
                if(value < root->key ){
                    std::cout << "E ";
                    return _Search(root->left, value);
                }else{
                    std::cout << "D ";
                    return _Search(root->right, value);
                }
            }
        }else{
            return nullptr;
        }
    }

    template<typename T>
    const Node<T>* BSTree<T>::Search(T value) const{
        return _Search(_root, value);
    }


}
#endif