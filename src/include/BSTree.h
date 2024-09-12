#ifndef UT_BS_TREE_H
#define UT_BS_TREE_H


#include "Node.h"
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>

namespace EDA{
    //Binary Search Tree
    template<typename T>
    class BSTree{
        protected:
            Node<T>* _root = nullptr;

            Node<T>* _Clear(Node<T>* root);
            void _Print(Node<T>* root)const;
            virtual Node<T>* _Insert(Node<T>* root, T value);
            virtual Node<T>* _Remove(Node<T>* root, T value);
            // Breadth First Search
            Node<T>* _BFS(Node<T>* root, T value) const;
            // Depth First Search
            Node<T>* _DFS(Node<T>* root, T value) const;
            Node<T>* _Search(Node<T>* root, T value) const;
            Node<T>* _RightRotate(Node<T>* p);
            Node<T>* _LeftRotate(Node<T>* p);

            Node<T>* _DoubleRotateRight(Node<T>* p);
            Node<T>* _DoubleRotateLeft(Node<T>* p);

            

        public:
            ~BSTree();
            bool IsEmpty() const;
            void Print()const;
            const Node<T>* Search(T value) const;
            int Height(Node<T>* node) const;
            void Clear();

            void Insert(T item);
            void Remove(T value);
            void Test();
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
                
            }else{
                root->right = _Insert(root->right, value);
            }
            return root;
        }else{
            return new Node<T>(value, 1);
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
        std::cout << std::endl;
        if(_root == nullptr){
            std::cout << "Null" <<std::endl;
        }
        this->_Print(_root);
        std::cout << "\n";
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
    template<typename T> 
    int BSTree<T>::Height(Node<T>* node) const{
        return node == nullptr ? 0 : node->height;
    }

    template<typename T>
    Node<T>* BSTree<T>::_Remove(Node<T>* root, T value){
        throw std::logic_error("Função não implementada");
    }

    template<typename T>
    void BSTree<T>::Remove(T value){
        _root = _Remove(_root, value);
    }
    template<typename T>
    Node<T>* BSTree<T>::_RightRotate(Node<T>* p){
        Node<T>* u = p->left;
        p->left = u->right;
        u->right = p;
        p->height = 1 + std::max(this->Height(p->left), this->Height(p->right));
        u->height = 1 + std::max(this->Height(u->left), this->Height(u->right));
        return u;
    }

    template<typename T>
    Node<T>* BSTree<T>::_LeftRotate(Node<T>* p){
        Node<T>* u = p->right;
        p->right = u->left;
        u->left = p;
        p->height = 1 + std::max(Height(p->left), Height(p->right));
        u->height = 1 + std::max(Height(u->left), Height(u->right));
        return u;
    }

    template<typename T>
    void BSTree<T>::Test(){
        _root = _DoubleRotateRight(_root);
    }

    template<typename T>
    Node<T>* BSTree<T>::_DoubleRotateRight(Node<T>* p){
        p->left = this->_LeftRotate(p->left);
        return _RightRotate(p);
    }
    template<typename T>
    Node<T>* BSTree<T>::_DoubleRotateLeft(Node<T>* p){
        p->right = this->_RightRotate(p->right);
        return _LeftRotate(p);
    }

}
#endif