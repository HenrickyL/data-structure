#ifndef NODE_H
#define NODE_H

#include <sstream>

namespace Perikan {namespace TREE {

template <typename VALUE, typename KEY = int>
struct Node {
    KEY key;
    VALUE value;
    Node<VALUE, KEY>* left;
    Node<VALUE, KEY>* right;
    

    Node(const KEY& k, const VALUE& v, Node<VALUE, KEY>* l = nullptr, Node<VALUE, KEY>* r = nullptr)
        : key(k), value(v), left(l), right(r) {
    }

    std::string to_string() const {
        std::ostringstream oss;
        oss << "(" << key <<", " << value << ")";
        return oss.str();
    }

};

}}
/**

* PADDING
    - KEY key;                      //int ->4
    - VALUE value;                  //int ->4
    - Node<VALUE, KEY>* left;       //struct ->8 (int + int)
    - Node<VALUE, KEY>* right;      //struct ->8 (int + int)
    - int height;                   //int ->4
    --------------------------------------------------------
                                    //  28 -> padding => 32

**/
#endif