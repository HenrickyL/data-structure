#ifndef SET_DISPLAY_H
#define SET_DISPLAY_H

#include <iostream>
#include "../include/AVLTree.h"
#include "../include/BinarySearchTree.h"
#include "../include/Set.h"


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
            }
            catch (const std::exception& e) {
                std::cout << "Erro: " << e.what() << std::endl;
                waitClick();
                continue;
            }
        } while (opcao != 0);
    }
};

#endif