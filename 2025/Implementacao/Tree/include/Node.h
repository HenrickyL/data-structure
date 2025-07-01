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
    

    Node(const KEY& k, const VALUE& v, const Node<VALUE, KEY>* l = nullptr, const Node<VALUE, KEY>* r = nullptr)
        : key(k), value(v), left(nullptr), right(nullptr) {
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


#ifndef QXD_AVLNODE
#define QXD_AVLNODE


namespace Perikan {
    namespace TREE {

        template <typename VALUE, typename KEY = int>
        struct AVLNode : public Node<VALUE, KEY> {
            int height;

            AVLNode(const KEY& k, const VALUE& v, int h = 1, AVLNode* l = nullptr, AVLNode* r = nullptr)
                : height(h),Node<VALUE, KEY>(k, v,l,r) {}


            AVLNode<VALUE, KEY>* Right() {
                return static_cast<AVLNode<VALUE, KEY>*>(this->right);
            }
            AVLNode<VALUE, KEY>* Left() {
                return static_cast<AVLNode<VALUE, KEY>*>(this->left);
            }
        };

    }
}

#endif



