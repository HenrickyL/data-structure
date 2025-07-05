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

	}


};


#endif