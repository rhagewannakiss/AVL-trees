#include "AVLtree.hpp"

#include <iostream>

int main() {
    AVLTree::SearchTree<int, std::less<int>> tree;
    char cmd;

    while (std::cin >> cmd) {
        if (cmd == 'k') {
            int key;
            if (std::cin >> key) {
                tree.insert_node(key);
            } else {
                std::cout << "Wrong input!\n";
            }
        } else if (cmd == 'q') {
            int l, r;
            if (std::cin >> l >> r) {
                if (r > l) {
                    int count_r = tree.count_less_or_equal(r);
                    int count_l = tree.count_less_or_equal(l);
                    std::cout << (count_r - count_l) << " ";
                } else {
                    std::cout << "0 ";
                }
            }
        }
    }

    std::cout << '\n';
    return 0;
}