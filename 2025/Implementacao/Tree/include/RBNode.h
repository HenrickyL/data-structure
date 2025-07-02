#ifndef QXD_RBNODE
#define QXD_RBLNODE

namespace Perikan {
    namespace TREE {

        constexpr int RED = 1;;
        constexpr int BLACK = 0;;

        template <typename VALUE, typename KEY = int>
        struct RBNode : public Node<VALUE, KEY> {
            bool isRed; //0 black 1 red
            RBNode<VALUE, KEY>* father;

            RBNode(const KEY& k, const VALUE& v, bool c = true, RBNode<VALUE, KEY>* f = nullptr, RBNode<VALUE, KEY>* l = nullptr, RBNode<VALUE, KEY>* r = nullptr)
                : father(f), isRed(c), Node<VALUE, KEY>(k, v, l, r) {}


            RBNode<VALUE, KEY>* Right() {
                return static_cast<RBNode<VALUE, KEY>*>(this->right);
            }
            RBNode<VALUE, KEY>* Left() {
                return static_cast<RBNode<VALUE, KEY>*>(this->left);
            }
        };

    }
}

#endif