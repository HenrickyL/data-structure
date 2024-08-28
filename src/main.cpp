#include <iostream>
#include "BSTree.h"
using namespace std;

int main(){
    EDA::BSTree<int> tree;
    
    tree.Insert(5);
    tree.Insert(6);
    tree.Insert(2);
    tree.Insert(1);
    tree.Insert(3);
    tree.Insert(7);
    tree.Print();

    tree.Test(); // rotação a Esquerda
    tree.Print();


    const EDA::Node<int>* res = tree.Search(3);

    cout << endl;
    if(res != nullptr)
        cout << res->key << endl;
    else
        cout << "NULL" << endl;

    tree.Clear();
    tree.Print();

    return 0;
}