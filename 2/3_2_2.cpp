//3_2_2 task Pavel Pivkin
#include <iostream>
#define data_t long

template<typename T>
struct Node { 
    T           key;
    Node<T>     *left;
    Node<T>     *right;
    //Node<T>     *parent; 
    
    Node(T key_) {
        this -> key = key_;
        this -> left = NULL;
        this -> right = NULL;
    }
};


template<typename T>
class BinaryTree {
    private:
        Node<T> *root;
        void Insert(const T &key_, Node<T>*& node);
        void PreOrderTraverse(const Node<T> *node) const;
        void Visit(const Node<T> *node) const;
        void DeleteTree(Node<T> *node);
    public:
        BinaryTree<T>() { root = NULL; }
        ~BinaryTree() {
            DeleteTree(root);
         }
        void Add(const T &key_);
        void Pre_order();
        void Print() const;
        
};


int main() {
    BinaryTree<data_t> binaryTree;        
    size_t N;
    std::cin >> N;
    for (int i = 0; i < N; i++) {
        data_t key;
        std::cin >> key;
        binaryTree.Add(key);
    }
    binaryTree.Print();
    return 0;
}

template<typename T>
void BinaryTree<T>::Add(const T &key_) {
    this -> Insert(key_, root);
}
    
template<typename T>
void BinaryTree<T>::Insert(const T &key_, Node<T>*& node) {
    if (node == NULL) {
        node = new Node<T>(key_);
        return;
    } 
    if (node -> key <= key_) {
        Insert(key_, node -> right);
    } else {
        Insert(key_, node -> left); 
    }   
}

template<typename T>
void BinaryTree<T>::PreOrderTraverse(const Node<T> *node) const {
    if (node == NULL) {
        return;
    }
    Visit(node);
    PreOrderTraverse(node -> left);
    PreOrderTraverse(node -> right);
}

template<typename T>
void BinaryTree<T>::Visit(const Node<T> *node) const {
    std::cout << node -> key << " ";
}

template<typename T>
void BinaryTree<T>::Print() const {
    PreOrderTraverse(root);
}

template<typename T>
void BinaryTree<T>::DeleteTree(Node<T> *node) {
    if (node != NULL) {
        return;
    } else {
        DeleteTree(node -> right);
        DeleteTree(node -> left);
        delete node;
    }
}
