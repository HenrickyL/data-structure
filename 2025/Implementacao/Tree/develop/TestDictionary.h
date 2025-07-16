#ifndef TEST_DICTIONARY_H
#define TEST_DICTIONARY_H

#include "../include/AVLDictionary.h"
#include <iostream>

class TestDictionary {
public:

	static void test1() {
		AVLDictionary dict;

		dict.add("sapo");
		dict.add("sapo");
		dict.add("sapo");
		dict.add("rato");
		dict.add("Rato");
		dict.add("gato");

		std::string t1 = "sapo";
		std::cout<< "constains `"<< t1 <<"`:" << (dict.constains(t1) ? "Y" : "N") << std::endl;
		std::string t2 = "henricky";
		std::cout << "constains `" << t2 << "`:" << (dict.constains(t2) ? "Y" : "N") << std::endl;

		std::cout << "Size: " << dict.size() << std::endl;
		std::cout << "count("<<t1<<"): " << dict.count(t1) << std::endl;


		std::cout << "OPERATORS" << std::endl;

		dict["galinha"] = 3;
		dict["sapo"] = 8;

		std::string key = "sapo";

		if (dict[key]) {
			std::cout << "A palavra `" << key << "` tem contagem: " << dict[key] << std::endl;
		}

		// Incrementa diretamente via operator[]
		dict["sapo"] = dict["sapo"] + 1;
		dict["novo"] += 1; // Testa inserção implícita + incremento direto

		std::cout << "Apos incremento, count(`" << key << "`): " << dict[key] << std::endl;
		std::cout << "Count(`novo`): " << dict["novo"] << std::endl;
		std::cout << "Count(`galinha`): " << dict["galinha"] << std::endl;


		std::cout << "Tamanho total: " << dict.size() << std::endl;

		std::cout << "count(" << t1 << "): " << dict.count(t1) << std::endl;

	}


};


#endif