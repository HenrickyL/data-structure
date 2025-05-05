#include <iostream>
#include "include/AVLTree.h"
#include "include/BinarySearchTree.h"
#include "include/Set.h"


using namespace std;
#include<vector>
#include<sstream>
#include <cstdlib>
#include <limits>
#include<string>

class SetDisplay {
private:
    std::vector<Set*> sets;

    void displayMenu() {
        std::cout << "\n=== MENU PRINCIPAL ===" << std::endl;
        std::cout << "1. Criar novo conjunto" << std::endl;
        std::cout << "2. Inserir elemento em um conjunto" << std::endl;
        std::cout << "3. Remover elemento de um conjunto" << std::endl;
        std::cout << "4. Verificar se elemento existe" << std::endl;
        std::cout << "5. Mostrar conjunto" << std::endl;
        std::cout << "6. Operacoes binarias" << std::endl;
        std::cout << "7. Informacoes do conjunto" << std::endl;
        std::cout << "8. Limpar conjunto" << std::endl;
        std::cout << "9. Limpar Console" << std::endl;
        std::cout << "10. Trocar dois conjuntos" << std::endl;
        std::cout << "0. Sair" << std::endl;
        std::cout << "Escolha uma opcao: ";
    }

    void displayBinaryOperationsMenu() {
        std::cout << "\n=== OPERACOES BINARIAS ===" << std::endl;
        std::cout << "1. Uniao (A U B)" << std::endl;
        std::cout << "2. Interseccao (A ^ B)" << std::endl;
        std::cout << "3. Diferenca (A - B)" << std::endl;
        std::cout << "0. Voltar ao menu principal" << std::endl;
        std::cout << "Escolha uma opcao: ";
    }

    void displayInfoMenu() {
        std::cout << "\n=== INFORMACOES DO CONJUNTO ===" << std::endl;
        std::cout << "1. Menor elemento" << std::endl;
        std::cout << "2. Maior elemento" << std::endl;
        std::cout << "3. Tamanho do conjunto" << std::endl;
        std::cout << "4. Verificar se esta vazio" << std::endl;
        std::cout << "0. Voltar ao menu principal" << std::endl;
        std::cout << "Escolha uma opcao: ";
    }

    int escolherSet(const std::string& prompt = "Escolha o indice do conjunto") {
        if (sets.empty()) {
            std::cout << "Nenhum conjunto disponivel!" << std::endl;
            return -1;
        }

        std::cout << prompt << " (0 ate " << sets.size() - 1 << "): ";

        int idx;  // Mantemos como int para retornar -1 em caso de erro
        std::cin >> idx;

        // Verificação segura considerando a diferença de signed/unsigned
        if (std::cin.fail() || idx < 0 || static_cast<size_t>(idx) >= sets.size()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Indice invalido!" << std::endl;
            return -1;
        }

        return idx;
    }


    void waitClick() {
        std::cout << "\nPressione Enter para continuar...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();  // Espera o Enter
    }

    void clearConsole() {
        std::system("cls");
    }

public:

    ~SetDisplay() {
        for (Set* s : sets) {
            delete s;
        }
    }

    void run() {
        int opcao;
        do {
            displayMenu();
            std::cin >> opcao;
            clearConsole();

            try {
                switch (opcao) {
                case 1: { // Criar novo conjunto
                    std::string name = "Set " + std::to_string(sets.size());
                    sets.push_back(new Set(name));
                    std::cout << "Conjunto criado com indice " << sets.size() - 1 << std::endl;
                    break;
                }
                case 2: { // Inserir
                    int idx = escolherSet();
                    if (idx != -1) {
                        int escolha;
                        std::cout << "1. Inserir um valor\n2. Inserir varios valores\nEscolha: ";
                        std::cin >> escolha;

                        if (escolha == 1) {
                            int val;
                            std::cout << "Elemento a inserir: ";
                            std::cin >> val;
                            sets[idx]->insert(val);
                        }
                        else if (escolha == 2) {
                            std::cout << "Digite os valores separados por espaco (fim com -999): ";
                            int val;
                            while (std::cin >> val && val != -999) {
                                try {
                                    sets[idx]->insert(val);
                                }
                                catch (const std::exception& e) {
                                    std::cout << "Erro ao inserir " << val << ": " << e.what() << std::endl;
                                }
                            }
                            std::cin.clear(); // limpa estado de erro
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }
                        else {
                            std::cout << "Opcao invalida." << std::endl;
                        }
                    }
                    break;
                }
                case 3: { // Remover
                    int idx = escolherSet();
                    if (idx != -1) {
                        int val;
                        std::cout << "Elemento a remover: ";
                        std::cin >> val;
                        sets[idx]->erase(val);
                    }
                    break;
                }
                case 4: { // Verificar existencia
                    int idx = escolherSet();
                    if (idx != -1) {
                        int val;
                        std::cout << "Elemento a verificar: ";
                        std::cin >> val;
                        std::cout << (sets[idx]->contains(val) ? "Existe" : "Nao existe") << std::endl;
                    }
                    break;
                }
                case 5: { // Mostrar
                    int idx = escolherSet();
                    if (idx != -1)
                        sets[idx]->print();
                    break;
                }
                case 6: { // Operações binárias
                    int op;
                    do {
                        displayBinaryOperationsMenu();
                        std::cin >> op;
                        clearConsole();

                        if (op == 0) break;

                        int a = escolherSet("Escolha o conjunto A");
                        int b = escolherSet("Escolha o conjunto B");

                        if (a != -1 && b != -1) {
                            Set result("Result");
                            switch (op) {
                            case 1: Set::unionSet(*sets[a], *sets[b], result); break;
                            case 2: Set::intersection(*sets[a], *sets[b], result); break;
                            case 3: Set::difference(*sets[a], *sets[b], result); break;
                            default: std::cout << "Opcao invalida!" << std::endl; continue;
                            }
                            result.print();
                        }
                    } while (op != 0);
                    break;
                }
                case 7: { // Informações
                    int op;
                    do {
                        displayInfoMenu();
                        std::cin >> op;
                        if (op == 0) break;

                        int idx = escolherSet();
                        if (idx != -1) {
                            switch (op) {
                            case 1: std::cout << "Menor: " << sets[idx]->minimum() << std::endl; break;
                            case 2: std::cout << "Maior: " << sets[idx]->maximum() << std::endl; break;
                            case 3: std::cout << "Tamanho: " << sets[idx]->size() << std::endl; break;
                            case 4: std::cout << (sets[idx]->empty() ? "Vazio" : "Nao vazio") << std::endl; break;
                            default: std::cout << "Opcao invalida!" << std::endl; break;
                            }
                        }
                    } while (op != 0);
                    break;
                }
                case 8: { // Limpar
                    int idx = escolherSet();
                    if (idx != -1) {
                        sets[idx]->clear();
                        std::cout << "Conjunto limpo." << std::endl;
                    }
                    break;
                }
                case 9: {
                    clearConsole();
                    break;
                }
                case 10: { // Trocar dois conjuntos
                    int a = escolherSet("Escolha o indice do primeiro conjunto");
                    int b = escolherSet("Escolha o indice do segundo conjunto");

                    if (a != -1 && b != -1) {
                        sets[a]->swap(*sets[b]);
                        std::cout << "Conjuntos " << a << " e " << b << " foram trocados com sucesso." << std::endl;
                    }
                    else {
                        std::cout << "Indices invalidos." << std::endl;
                    }
                    break;
                }
                case 0:
                    std::cout << "Saindo..." << std::endl;
                    break;
                default:
                    std::cout << "Opcao invalida!" << std::endl;
                    break;
                }
            }catch (const std::exception& e) {
                std::cout << "Erro: " << e.what() << std::endl;
                waitClick();
                continue;
            }
        } while (opcao != 0);
    }
};

void TestSet() {
    SetDisplay display;
    display.run();
}



//void TestAVL() {
//    Perikan::TREE::AVLTree<int> t;
//    int n = 11;
//    int v[11] = { 5, 7, 11, 17, 4, 6, 2, 1, 22, 3, 50 };
//    for (int i = 0; i < n; i++) {
//        t.add(v[i]);
//    }
//    
//    std::cout << t.to_string() << std::endl;
//
//    t.remove(4);
//    std::cout << t.to_string() << std::endl;
//}

//void TestRemove() {
//    Perikan::TREE::BinarySearchTree<int> t;
//    t.add(5);
//    t.add(3);
//    t.add(2);
//    t.add(4);
//    t.add(8);
//    t.add(7);
//    t.add(6);
//    t.add(9);
//    std::cout << t.to_string() << std::endl;
//    int removeKey = 5;
//    t.remove(removeKey);
//    std::cout << "Remove: " << removeKey << std::endl;
//    std::cout << t.to_string() << std::endl;
//}

//void Test() {
//    Perikan::TREE::BinarySearchTree<int> t;
//
//    //std::cout << "Max key: " << t.max() << std::endl;
//
//    t.add(5);
//    t.add(2);
//    t.add(1);
//    t.add(3);
//
//    t.add(8);
//    t.add(6, 11);
//    t.add(9);
//    t.add(7);
//
//    t.printOrdered();
//
//    std::cout << "KeyMin: " << t.keyMinimum() << std::endl;
//    std::cout << "KeyMax: " << t.keyMaximum() << std::endl;
//
//    int keyBase = 6;
//    std::cout << "BaseKey: " << keyBase << std::endl;
//    std::cout << "Successor: " << t.keySuccessor(6) << std::endl;
//    std::cout << "Predecessor: " << t.keyPredecessor(6) << std::endl;
//
//
//
//    t.print();
//    std::cout << "Count:  " << t.size() << std::endl;
//    std::cout << "Count Leafs: " << t.countLeafs() << std::endl;
//    std::cout << "Count Intern Leafs: " << t.countInterNodes() << std::endl;
//    std::cout << "Max key: " << t.max() << std::endl;
//
//    int removeKey = 8;
//    t.remove(removeKey);
//    std::cout << "Remove: "<< removeKey << std::endl;
//    std::cout << t.to_string() << std::endl;
//
//
//    int key = 3;
//    std::cout << "Finding key [" << key << "] ..." << std::endl;
//    int findKey = t.findByValue(11);
//    std::cout << "Finding value in key [" << findKey << "] ..." << std::endl;
//    bool exist = t.find(key);
//    std::cout << "Node: " << exist << std::endl;
//
//
//
//    t.removeLeafs();
//    std::cout << t.to_string() << std::endl;
//    std::cout << "Count Leafs: " << t.countLeafs() << std::endl;
//    t.clear();
//    std::cout << "Count: " << t.size() << std::endl;
//}

//void test1(){
//    int nLines;
//    std::cin >> nLines;
//    std::cin.ignore();
//
//    std::vector<Perikan::TREE::BinarySearchTree<int>*> trees;
//
//    for (int i=0; i < nLines; i++) {
//        int qtd;
//        std::cin >> qtd;
//        Perikan::TREE::BinarySearchTree<int>* t = new Perikan::TREE::BinarySearchTree<int>();
//
//        for (int j = 0; j < qtd; j++) {
//            int x;
//            std::cin >> x;
//            t->add(x);
//        }
//
//        trees.push_back(t);
//    }
//
//    for (int i = 0; i < trees.size(); i++) {
//        Perikan::TREE::BinarySearchTree<int>* t = trees[i];
//        std::cout << "Case " << i+1 << ":" << std::endl;
//        t->printPreOrder();
//        t->printInOrder();
//        t->printPosOrder();
//        delete t;
//    }
//}
//
//void test2() {
//    int nLines;
//    std::cin >> nLines;
//    std::cin.ignore();
//
//    std::vector<Perikan::TREE::BinarySearchTree<int>*> trees;
//
//    for (int i = 0; i < nLines; i++) {
//        int qtd;
//        std::cin >> qtd;
//        Perikan::TREE::BinarySearchTree<int>* t = new Perikan::TREE::BinarySearchTree<int>();
//
//        for (int j = 0; j < qtd; j++) {
//            int x;
//            std::cin >> x;
//            t->add(x);
//        }
//
//        trees.push_back(t);
//    }
//
//    for (int i = 0; i < trees.size(); i++) {
//        Perikan::TREE::BinarySearchTree<int>* t = trees[i];
//        std::string s = i == 0 ? "" : "\n";
//        std::cout << s<<"Case " << i + 1 << ":" << std::endl;
//        t->printBFS();
//        delete t;
//    }
//}
//
//void test3() {
//    int key;
//    string line;
//    Perikan::TREE::BinarySearchTree<int> tree;
//
//    getline(cin, line);
//    stringstream ss(line);
//
//    while (ss >> key) {
//        tree.add(key);
//    }
//
//    cout << tree.height() << " " << tree.size() << endl;
//}


int main() {
    try {
        //Test();
        //test1();
        //test2();
        //test3();
        //TestRemove(); 
        //TestAVL();
        TestSet();
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}
