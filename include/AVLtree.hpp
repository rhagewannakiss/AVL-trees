#ifndef AVL_TREE_HPP_
#define AVL_TREE_HPP_

#include <cstddef>
#include <iostream>

namespace AVLTree {

template <typename KeyT, typename Comp>

class SearchTree {
private:
    struct Node {
        KeyT   key_;
        Node*  parent_;
        Node*  left_;
        Node*  right_;
        size_t height_;
        size_t size_;

        Node(KeyT k, Node* parent = nullptr)
            : key_(k)
            , parent_(parent)
            , left_(nullptr)
            , right_(nullptr)
            , height_(1)
            , size_(1)
            {}
    };

    Comp  comp_;
    using iterator = Node*;
    Node* root_;

public:
    SearchTree()
    : root_(nullptr)
    {}

    ~SearchTree() {
        clear_tree(root_);
    }

    iterator lower_bound(const KeyT key) const {
        Node* current = root_;
        Node* result = nullptr;

        while (current) {
            if (!comp_(current->key_, key)) {
                result = current;
                current = current->left_;
            } else {
                current = current->right_;
            }
        }
        return result;
    }

    iterator upper_bound(const KeyT key) const {
        Node* current = root_;
        Node* result = nullptr;

        while (current) {
            if (comp_(current->key_, key)) {
                result = current;
                current = current->left_;
            } else {
                current = current->right_;
            }
        }

        return result;
    }

    void insert_node(const KeyT& key) {
        root_ = insert_recursive(root_, nullptr, key);
    }

    void delete_node(const KeyT& key) {
        root_ = delete_recursive(root_, key);
    }

    void clear_tree(Node* node) {
        if (!node) {
            return;
        }

        clear_tree(node->left_);
        clear_tree(node->right_);

        delete(node);
    }

     size_t count_less(const KeyT& key) const {
        Node* current = root_;
        size_t cnt = 0;

        while (current) {
            if (comp_(key, current->key_)) {
                current = current->left_;
            } else if (comp_(current->key_, key)) {
                cnt += get_size(current->left_) + 1;
                current = current->right_;
            } else {
                cnt += get_size(current->left_);
                return cnt;
            }
        }
        return cnt;
    }

     int find_kth(int k) const {
        Node* current = root_;
        if (!current || k <= 0 || k > static_cast<int>(current->size_)) {
            return -1;
        }

        while (current) {
            size_t left_size = get_size(current->left_);
            if (left_size + 1 == static_cast<size_t>(k)) {
                return current->key_;
            } else if (left_size >= static_cast<size_t>(k)) {
                current = current->left_;
            } else {
                k -= (static_cast<int>(left_size) + 1);
                current = current->right_;
            }
        }
        return -1;
    }


private:
    Node* insert_recursive(Node* node, Node* parent, const KeyT key) {
        if (!node) {
            return new Node(key, parent);
        }
        if (comp_(key, node->key_)) {
            node->left_ = insert_recursive(node->left_, node, key);
        } else if (comp_(node->key_, key)){
            node->right_ = insert_recursive(node->right_, node,  key);
        } else {
#ifndef NDEBUG
            std::cerr << "Insert: Key " << key << " already exists in tree\n";
#endif //NDEBUG
            return node;
        }

        return balance(node);
    }

    Node* delete_recursive(Node* node, const KeyT key) {
        if (!node) {
#ifndef NDEBUG
            std::cerr << "Delete: Key " << key << " not found in tree\n";
#endif //NDEBUG
            return nullptr;
        }

        if (!root_) {
            return root_;
        }

        if (comp_(key, node->key_)) {
            node->left_ = delete_recursive(node->left_, key);
        } else if (comp_(node->key_, key)) {
            node->right_ = delete_recursive(node->right_, key);
        } else {
            if (!node->left_ || !node->right_) {
                Node* tmp = node->left_ ? node->left_ : node->right_;
                delete node;
                return tmp;
            } else {
                Node* min_node = find_min(node->right_);
                node->key_ = min_node->key_;
                node->right_ = delete_recursive(node->right_, min_node->key_);
                if (node->right_) {
                    node->right_->parent_ = node;
                }
            }
        }
        return balance(node);
    }

    Node* right_rotate(Node* node) {
        if (!node || !node->left_) {
            return node;
        }

        Node* left_child = node->left_;
        Node* right_subchild = left_child->right_;

        left_child->right_ = node;
        node->left_ = right_subchild;

        left_child->parent_ = node->parent_;
        node->parent_ = left_child;

        if (right_subchild) {
            right_subchild->parent_ = node;
        }

        fix_height(node);
        fix_height(left_child);

        return left_child;
    }

    Node* left_rotate(Node* node) {
        if (!node || !node->right_) {
            return node;
        }
        Node* right_child = node->right_;
        Node* left_subchild = right_child->left_;

        right_child->left_ = node;
        node->right_ = left_subchild;

        right_child->parent_ = node->parent_;
        node->parent_ = right_child;

        if (left_subchild) {
            left_subchild->parent_ = node;
        }

        fix_height(node);
        fix_height(right_child);

        return right_child;
    }

    Node* left_right_rotate(Node* node) {
        if (!node || !node->right_ || !node->left_) {
            return node;
        }

        node->left_ = left_rotate(node->left_);
        return right_rotate(node);
    }

    Node* right_left_rotate(Node* node) {
        if (!node || !node->left_ || !node->right_) {
            return node;
        }

        node->right_ = right_rotate(node->right_);
        return left_rotate(node);
    }

    size_t get_height(Node* node) const {
        return (node ? node->height_ : 0);
    }

    size_t get_size(Node* node) const {
        return (node ? node->size_ : 0);
    }

    void fix_height(Node* node) {
        if (!node) {
#ifndef NDEBUG
            std::cerr << "fix_height: Cannot fix height of null node\n";
#endif //NDEBUG
            return;
        }

        size_t height_left = get_height(node->left_);
        size_t height_right = get_height(node->right_);

        node->height_ = ((height_left > height_right) ? height_left : height_right) + 1;

        size_t size_left = get_size(node->left_);
        size_t size_right = get_size(node->right_);
        node->size_ = size_left + size_right + 1;
    }

    int balance_factor(Node* node) const {
        return node ? (static_cast<int>(get_height(node->left_)) - static_cast<int>(get_height(node->right_))) : 0;
    }

    Node* balance(Node* node) {
        if (!node) {
            return node;
        }
        fix_height(node);

        int blnc_fctr = balance_factor(node);
        if (blnc_fctr > 1) {
            if (balance_factor(node->left_) >= 0) {
                return right_rotate(node);
            } else {
                return left_right_rotate(node);
            }
        } else if (blnc_fctr < -1) {
            if (balance_factor(node->right_) <= 0) {
                return left_rotate(node);
            } else {
                return right_left_rotate(node);
            }
        }
        return node;
    }

    Node* find_min(Node* node) const {
        if (!node) {
            return nullptr;
        }
        while (node->left_) {
            node = node->left_;
        }
        return node;
    }

};

} //namespace AVLTree

#endif //AVL_TREE_HPP_