#include <iostream>
#include <string>

class Node {
public:
    enum Color {
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

    static bool isEqualLeafBlackCount(Node* n, int &count) {
        if (n == nullptr) {
            return true;
        }
        if (n->color == Node::Black) {
            count++;
        }
        if (isLeaf(n)) {
            return true;
        }
        int l_count = 0;
        int r_count = 0;
        bool l_res;
        bool r_res;
        l_res = isEqualLeafBlackCount(n->left, l_count);
        r_res = isEqualLeafBlackCount(n->right, r_count);
        return (l_res && r_res && (l_count == r_count) );
    }

    static bool isLeaf (Node* n) {
        return n != nullptr && n->left == nullptr && n->right == nullptr;
    }

    bool CorrectIterator (Node* n, Node* parent, int black_count) {
        bool ret = true;
        if (n != nullptr) {
            if (ret && (n->left != nullptr)) {
                ret = n->left->key < n->key;
            }
            if (ret && (n->right != nullptr)) {
                ret = n->key < n->right->key;
            }

            if ( n == Head || isLeaf(n) ) {
                ret = n->color == Node::Black;
            }

            if (ret && (n->color == Node::Red && n != Head)) {
                ret = parent->color == Node::Black;
            }

            if (ret && !isLeaf(n) ) {
                int count;
                ret = isEqualLeafBlackCount(n, count);
            }

            if (ret) {
                ret = CorrectIterator(n->right, n, black_count);
            }
            if (ret) {
                ret = CorrectIterator(n->left, n, black_count);
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
        Head = nullptr;
    }

};

int main() {
    int nodes_count = 0;
    int root_index = 0;
    int node_index = 0;
    char color = '\0';
    std::string input;
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
        std::cin >> input;
        if (input == "null") {
            nodes[node_index - 1].left = nullptr;
        }
        else {
            nodes[node_index - 1].left = &nodes[std::stoi(input) - 1];
        }
        std::cin >> input;
        if (input == "null") {
            nodes[node_index - 1].right = nullptr;
        }
        else {
            nodes[node_index - 1].right = &nodes[std::stoi(input) - 1];
        }
        std::cin >> color;
        switch (color) {
            case 'R' :
                nodes[node_index - 1].color = Node::Red;
                break;
            case 'B' :
                nodes[node_index - 1].color = Node::Black;
                break;
            default :
                std::cout << "NO\n";
                return 0;
        }
    }

    ColoredBinaryTree tree;
    tree.Head = &nodes[root_index - 1];
    if (tree.isCorrect()) {
        std::cout << "YES";
    }
    else {
        std::cout << "NO";
    }
    return 0;
}
