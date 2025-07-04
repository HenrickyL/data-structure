#ifndef TEST_HASH_H
#define TEST_HASH_H

#include<iostream>
#include<string>
#include "../include/ChainedHashTable.h"

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

	}


};
#endif // !TEST_HASH_H
