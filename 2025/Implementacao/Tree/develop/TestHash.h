#ifndef TEST_HASH_H
#define TEST_HASH_H

#include<iostream>
#include<string>
#include "../include/ChainedHashTable.h"
#include "../include/OpenAddressHashTable.h"


using namespace Perikan::Hash;

class TestHash {

private:

    struct Bolinha {
        std::string cor;
        float raio;

        bool operator==(const Bolinha& other) const {
            return cor == other.cor && raio == other.raio;
        }
    };

    struct HashBolinha {
        size_t operator()(const Bolinha& ball) const {
            auto number1 = std::hash<std::string>()(ball.cor);
            auto number2 = std::hash<float>()(ball.raio);
            return number1 ^ number2;
        }
    };


public:

	static void ChainedHash() {
        // -------------------------------------------------------------------------------------
    // Teste 1: inserindo muitos elementos numa tabela hash
        std::cout << "ChainedHashTable -------------\n";

       ChainedHashTable<float, int> tabela(5, 0.75);

        std::cout << "tamanho inicial da tabela = " << tabela.bucket_count() << std::endl;

        size_t current_bucket_count = tabela.bucket_count();

        for (int i = 0; i < 5000; ++i) {
            float key = i / 2.0f;
            int value = i;
            tabela[key] = value;
            if (tabela.bucket_count() != current_bucket_count) {
                current_bucket_count = tabela.bucket_count();
                std::cout << "tabela aumentou, novo tamanho = " << current_bucket_count << std::endl;
            }

        }

        tabela.clear();

        // -----------------------------------------------------------------------------------
        // Teste 2: reservando espaco previo
        ChainedHashTable<std::string, int> novaTabela(5, 0.5);
        novaTabela.reserve(100);
        std::cout << "novaTabela.bucket_count = " << novaTabela.bucket_count() << std::endl;

        // ----------------------------------------------------------------------------------
        // Teste 3: criando uma tabela hash onde as chaves sao bolinhas
        ChainedHashTable<Bolinha, int, HashBolinha> tabBolinha(13, 0.8);

        tabBolinha.add({ "azul", 0.4 }, 23);

        std::cout << "numero de bolinhas na tabela de bolinhas = " << tabBolinha.size() << std::endl;
        std::cout << "----------------------------------\n";
	}

    static void OpenAddressHash() {
        std::cout << "OpenAddressHashTable -------------\n";
        std::cout << "Teste 1: Inserindo muitos elementos na OpenAddressHashTable\n";

        Perikan::Hash::OpenAddressHashTable<float, int> tabela(5, 0.75f);

        size_t current_capacity = tabela.capacity();
        std::cout << "Capacidade inicial: " << current_capacity << "\n";

        for (int i = 0; i < 5000; ++i) {
            float key = i / 2.0f;
            int value = i;

            bool inserted = tabela.add(key, value);
            if (!inserted) {
                // chave já existia, atualiza pelo operator[]
                tabela[key] = value;
            }

            if (tabela.capacity() != current_capacity) {
                current_capacity = tabela.capacity();
                std::cout << "Tabela rehashou, nova capacidade = " << current_capacity << "\n";
            }
        }

        std::cout << "Tamanho apos insercoes: " << tabela.size() << "\n";

        // Testa contains
        float testKey = 10.0f;
        std::cout << "Contem chave " << testKey << "? " << (tabela.contains(testKey) ? "Sim" : "Nao") << "\n";

        // Testa acesso com at()
        try {
            int val = tabela.at(testKey);
            std::cout << "Valor da chave " << testKey << " = " << val << "\n";
        }
        catch (const std::out_of_range& e) {
            std::cout << e.what() << "\n";
        }

        // Remove uma chave
        bool removed = tabela.remove(testKey);
        std::cout << "Removeu chave " << testKey << "? " << (removed ? "Sim" : "Nao") << "\n";

        std::cout << "Contem chave " << testKey << " após remoção? " << (tabela.contains(testKey) ? "Sim" : "Nao") << "\n";

        // Testa clear
        tabela.clear();
        std::cout << "Tamanho apos clear: " << tabela.size() << "\n";

        // Teste com Bolinha e HashBolinha
        Perikan::Hash::OpenAddressHashTable<Bolinha, int, HashBolinha> tabBolinha(13, 0.8f);

        Bolinha b1{ "azul", 0.4f };
        tabBolinha.add(b1, 23);

        std::cout << "Número de bolinhas na tabela: " << tabBolinha.size() << "\n";
        std::cout << "Contem bolinha azul? " << (tabBolinha.contains(b1) ? "Sim" : "Nao") << "\n";

        std::cout << "----------------------------------\n";
    }


};
#endif // !TEST_HASH_H
