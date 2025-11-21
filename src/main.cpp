#include <iostream>
#include "AVLtree.hpp"
int main() {
    AVLTree::SearchTree<int, std::less<int>> tree;
    char cmd;

    while (std::cin >> cmd) {
        if (cmd == 'k') {  //insertion
            int x;
            if (!(std::cin >> x)) {
                std::cerr << "Wrong input!\n";
                break;
            }
            tree.insert_node(x);

        } else if (cmd == 'm') {  //find k-th smallest number
            int k;
            if (std::cin >> k) {
                std::cout << tree.find_kth(k) << " \n";
            } else {
                std::cerr << "Wrong input!\n";
                break;
            }
        } else if (cmd == 'n') { //find amount of numbers smaller than n
            int n;
            if (std::cin >> n) {
                std::cout << tree.count_less(n) << " \n";
            } else {
                std::cerr << "Wrong input!\n";
                break;
            }
        } else if (cmd == 's') {
            std::cout << "Stopped.\n";
            break;
        } else {
            std::cout << "Unknown input. Please enter k, n, m or an integer\n";
            break;
        }
    }

    std::cout << '\n';
    return 0;
}

/*
Домашняя работа  HWT
Со стандартного ввода придят ключи (каждый ключ это целое число, все ключи разные) и запросы двух видов.
Запрос (m) на поиск k-ого наименьшего элемента.Запрос (n) на поиск количества элементов, меньших, чем заданный.
Вход: k 8 k 2 k -1 m 1 m 2 n 3
Результат: -1 2 2
Ключи могут быть как угодно перемешаны с запросами. Чтобы успешно пройти тесты, вы должны продумать такую балансировку дерева, чтобы оба вида запросов работали с логарифмической сложностью.
*/