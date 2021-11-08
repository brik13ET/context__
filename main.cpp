#include <iostream>

class Node {
public:
    enum Color { Black, Red };
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
    void destructorIterator(Node* n) {
        if (n != nullptr) {
            destructorIterator(n->left);
            destructorIterator(n->right);
            delete n;
        }
    }

    bool isEqualBlackLengthIterator(Node* n, int *count) {
        if (n == nullptr) {
            (*count)++;
            return true;
        }
        int left_count = 0;
        int right_count = 0;
        bool is_left_equal;
        bool is_right_equal;
        is_left_equal = isEqualBlackLengthIterator(n->left, &left_count);
        if (is_left_equal) {
            is_right_equal = isEqualBlackLengthIterator(n->right, &right_count);
        }
        if (left_count == right_count && n->color == Node::Black) {
            (*count) = left_count + 1;
        } else if (left_count == right_count && n->color != Node::Black) {
            (*count) = left_count;
        }

        return is_left_equal && is_right_equal && left_count == right_count;
    }

    bool isEqualBlackLength(Node* n) {
        int count = 0;
        return isEqualBlackLengthIterator(n, &count);
    }

    bool correctIterator(Node* n, Node* parent) {
        bool ret = true;
        if (n != nullptr) {
            ret = n->left == nullptr || n->left->key < n->key;
            if (ret) {
                ret = n->right == nullptr || n->right->key > n->key;
            }
            if (ret) {
                ret = isEqualBlackLength(n);
            }
            if (ret && n->color == Node::Red) {
                ret = parent != nullptr && parent->color == Node::Black;
            }
            if (ret) {
                bool l;
                bool r = false;
                l = correctIterator(n->left, n);
                if (l) {
                    r = correctIterator(n->right, n);
                }
                return r && l;
            }
        }
        return ret;
    }

public:
    Node* Head;

    bool isCorrect() {
        return correctIterator(Head, nullptr);
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
    Node* nodes = new Node[nodes_count];
    for (int index_of_arr = 0; index_of_arr < nodes_count; ++index_of_arr) {
        std::cin >> node_index;
        std::cin >> nodes[node_index - 1].key;
        std::cin >> input;
        if (input == "null") {
            nodes[node_index - 1].left = nullptr;
        } else {
            nodes[node_index - 1].left = &nodes[std::stoi(input) - 1];
        }
        std::cin >> input;
        if (input == "null") {
            nodes[node_index - 1].right = nullptr;
        } else {
            nodes[node_index - 1].right = &nodes[std::stoi(input) - 1];
        }
        std::cin >> color;
        switch (color) {
            case 'R':
                nodes[node_index - 1].color = Node::Red;
                break;
            case 'B':
                nodes[node_index - 1].color = Node::Black;
                break;
            default:
                std::cout << "NO\n";
                return 0;
        }
    }
    ColoredBinaryTree tree;
    tree.Head = &nodes[root_index - 1];
    if (tree.isCorrect()) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }
    delete[] nodes;
    return 0;
}
