# Código de Árvore

```cpp
// include/Node.h
 template<typename T>
    struct Node{
        T key;
        int height=0;        
        Node<T>* left;
        Node<T>* right;

        Node(T _value_, int _height, Node<T>* _left = nullptr, 
            Node<T>* _right = nullptr)
        {
            key = _value_;
            left = _left;
            right = _right; 
            height = _height;
        }
    };
```


```cpp
template<typename T>
class BSTree{
    protected:
        Node<T>* _root = nullptr;

        Node<T>* _Clear(Node<T>* root);
        void _Print(Node<T>* root)const;
        virtual Node<T>* _Insert(Node<T>* root, T value);
        virtual void _Remove(Node<T>* root, T value);
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
```


```cpp
template<typename T>
class AVL : public BSTree<T>{
protected:
    virtual Node<T>* _Insert(Node<T>* root, T value) override;

    Node<T>* _FixupNode(Node<T>* node, T key);
public:
    int Balance(Node<T>* node);

};
``` 



```cpp
// main.cpp
#include <iostream>
#include "AVL.h"
using namespace std;

int main(){
    EDA::AVL<int> tree;
    
    tree.Insert(5);
    tree.Insert(7);
    tree.Insert(11);
    tree.Insert(17);
    tree.Insert(4);
    tree.Insert(6);
    tree.Insert(2);
    tree.Insert(1);
    tree.Insert(22);
    tree.Insert(3);
    tree.Insert(50);
    tree.Print();

    cout << endl;
    return 0;
}
```

```
7 4 2 1 # # 3 # # 5 # 6 # # 17 11 # # 22 # 50 # #
```