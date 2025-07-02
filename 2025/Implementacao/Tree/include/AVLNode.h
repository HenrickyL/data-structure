#ifndef QXD_AVLNODE
#define QXD_AVLNODE


namespace Perikan {
    namespace TREE {

        template <typename VALUE, typename KEY = int>
        struct AVLNode : public Node<VALUE, KEY> {
            int height;

            AVLNode(const KEY& k, const VALUE& v, int h = 1, AVLNode* l = nullptr, AVLNode* r = nullptr)
                : height(h), Node<VALUE, KEY>(k, v, l, r) {}


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