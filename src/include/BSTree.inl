
template<typename T>
bool BSTree<T>::IsEmpty() const {
    return this->_root == nullptr;
}

template<typename T>
bool BSTree<T>::Insert(T value) {
    return this->_Insert(_root, value);
}

template<typename T>
bool BSTree<T>::_Insert(Node<T>* root, T value){
    if(root != nullptr){
        return false;
    }else{
        Node<T>* newNode = new Node<T>(value);
        root = newNode;
        return true;
    }
}
