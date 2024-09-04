#include <iostream>
#include "AVL.h"
using namespace std;

int main(){
    EDA::AVL<int> tree;
    
    // tree.Insert(5);
    // tree.Insert(6);
    // tree.Insert(2);
    // tree.Insert(1);
    // tree.Insert(3);
    // tree.Insert(7);
    // tree.Print();


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


    cout << "Rotate:" << endl;
    // tree.Test(); // rotação a Esquerda
    tree.Print();
    cout << endl;

    return 0;
}