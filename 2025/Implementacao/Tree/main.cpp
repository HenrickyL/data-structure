#include<iostream>
//#include "include/BinarySearchTree.h"
//#include "develop/TestTree.h"
//#include "develop/TestHash.h"
//#include "develop/TestDictionary.h"

#include "develop/TestPriorityQueue.h"



int main(int argc, char* argv[]) {
    try {
        /*TestTree::Node_();
        TestTree::BST();
        TestTree::AVL();
        TestTree::RB();*/

        /*TestHash::ChainedHash();
        TestHash::OpenAddressHash();*/
        //int argc = 4;
        //const char* argv[] = {  // Adicione 'const' aqui
        //    "program.exe",
        //    "all",
        //    "books/dom-casmurro.txt",
        //    "--benchmark"
        //};
        //
        //
        //TestDictionary::Run(argc, const_cast<char**>(argv));
        //TestDictionary::Run(argc, argv);

        /*TestDictionary::testRB();
        TestDictionary::testAVL();
        TestDictionary::testOAHT();
        TestDictionary::testCHT();*/

        TestPriorityQueue::test();
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}
