#include <iostream>
#include "includes/BinarySearchTree.h"
using namespace std;

int main(){
    Perikan::TREE::BinarySearchTree t;
    t.add(5);
    t.add(3);
    t.add(1);
    t.add(6);
    t.add(7);
    t.add(8);

    std::cout << t.to_string()<<std::endl;
    return 0;
}