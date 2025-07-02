#ifndef QXD_RBNODE
#define QXD_RBLNODE

namespace Perikan {
    namespace TREE {

        constexpr int RED = 1;;
        constexpr int BLACK = 0;;

        template <typename VALUE, typename KEY = int>
        struct RBNode : public Node<VALUE, KEY> {
            bool color; //0 black 1 red  // isRed
            RBNode<VALUE, KEY>* parent;

            RBNode(const KEY& k, const VALUE& v, bool c = true, RBNode<VALUE, KEY>* p = nullptr, RBNode<VALUE, KEY>* l = nullptr, RBNode<VALUE, KEY>* r = nullptr)
                : parent(p), color(c), Node<VALUE, KEY>(k, v, l, r) {}


            RBNode<VALUE, KEY>* Right()const {
                return static_cast<RBNode<VALUE, KEY>*>(this->right);
            }
            RBNode<VALUE, KEY>* Left()const {
                return static_cast<RBNode<VALUE, KEY>*>(this->left);
            }
        };

    }
}

#endif