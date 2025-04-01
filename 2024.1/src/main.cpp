#include <iostream>
#include "PriorityQueue.h"
#include "AVL.h"

using namespace std;


void testAVL(){
    EDA::AVL<int> tree;

    int v[] = {50, 30, 70, 20, 40, 60, 80, 10};
    int n = 8;
    for(int i=0; i<n ; i++){
        tree.Insert(v[i]);

    }
    tree.Print();

    tree.Remove(4);
    tree.Print();

    cout << endl;
}

void testPQueue(){
    EDA::PriorityQueue<int> p(false);
    p.Enqueue(2);
    p.Enqueue(5);
    p.Enqueue(3);
    p.Enqueue(1);
    p.Print();
    int x = p.First();
    std::cout << x << std::endl;
    p.Dequeue();
    x = p.First();
    std::cout << x << std::endl;
    p.Print();
}


int main(){
    // testAVL();
    testPQueue();
    return 0;
}