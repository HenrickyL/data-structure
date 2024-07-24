#include <iostream>
#include "Node.h"
using namespace std;

int main(){
    EDA::Node<int> n;
    n.value = 10;
    std::cout << "Hello, World! " << n.value << std::endl;
    return 0;
}