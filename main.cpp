#include <iostream>

class Node;

class Node {
public:
    enum {
        Black,
        Red
    };
    int key;
    Node* left;
    Node* right;
    Color color;
    Node() {
        color = Black;
        key = 0;
        left = nullptr;
        right = nullptr;
    }

    Node(int Key, Node* Left, Node* Right, Color color_) {
        key = Key;
        left = Left;
        right = Right;
        color = color_;
    }
};

class ColoredBinaryTree {
protected:
    void DestructorIterator (Node* n) {
        if (n != nullptr) {
            DestructorIterator(n->left);
            DestructorIterator(n->right);
            delete n;
        }
    }

    int GetBlackCount () {
        int ret;
        if (Head != nullptr) {
            ret = 0;
            Node* n = Head;
            while (n->left != nullptr && n->right != nullptr) {
                if (n->color == Node::Black) {
                    ret ++;
                }
                if (n->left != nullptr) {
                    n = n->left;
                    continue;
                }
                else if (n->right != nullptr){
                    n = n->right;
                }
            }
        }
        return ret;
    }

    bool CorrectIterator (Node* n, Node* parent, int black_count) {
        bool ret = true;
        if (n != nullptr) {
            if (n == Head || (n->left == nullptr && n->right == nullptr)) {
                ret = ret && n->color == Node::Black;
            }
            if (n->color == Node::Red && n != Head) {
                ret = ret && parent->color == Node::Black;
            }
            if (n->left == nullptr && n->right == nullptr) {
                ret = ret && black_count == GetBlackCount();
            }
            ret = ret && (n->left->key < n->key && n->key < n->right->key) ;
            if (n->color == Node::Black) {
                black_count++;
            }
            if (ret) {
                ret = ret && CorrectIterator(n->right, n, black_count);
            }
            if (ret) {
                ret = ret && CorrectIterator(n->left, n, black_count);
            }
        }
        return ret;
    }

public:
    Node* Head;

    bool isCorrect () {
        return CorrectIterator(Head, nullptr, 0);
    }

    ColoredBinaryTree() {
        Head = new Node();
    }

    ~ColoredBinaryTree() {
        DestructorIterator(Head);
        delete Head;
    }

};

int main() {
    int nodes_count = 0;
    int root_index = 0;
    int node_index = 0;
    int node_index_2 = 0;
    char color = '\0';
    std::cin >> nodes_count;
    if (nodes_count == 0) {
        std::cout << "YES\n";
        return 0;
    }
    std::cin >> root_index;
    Node nodes[nodes_count];
    for (int i = 0; i < nodes_count; ++i) {
        std::cin >> node_index;
        std::cin >> nodes[node_index - 1].key;
        std::cin >> node_index_2;
        if (std::cin.fail()) {
            nodes[node_index - 1].left = nullptr;
            std::cin.setstate(std::ios::failbit);
        }
        else {
            nodes[node_index - 1].left = &nodes[node_index_2 - 1];
        }
        if (std::cin.fail()) {
            nodes[node_index - 1].right = nullptr;
            std::cin.setstate(std::ios::failbit);
        }
        else {
            nodes[node_index - 1].right = &nodes[node_index_2 - 1];
        }
        std::cin >> color;
        switch (color) {
            case 'R' :
                nodes[node_index - 1].color = Node::Red;
                break;
            case 'B' :
                nodes[node_index - 1].color = Node::Red;
                break;
            default :
                std::cout << "NO\n";
                return 0;
        }
    }


    return 0;
}
