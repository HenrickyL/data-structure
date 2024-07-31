#include <iostream>
#include "BSTree.h"
using namespace std;

int main(){
    EDA::BSTree<int> tree;
    
    tree.Insert(5);
    tree.Insert(6);
    tree.Insert(1);


    tree.Print();
    tree.Clear();
    tree.Print();

    return 0;
}