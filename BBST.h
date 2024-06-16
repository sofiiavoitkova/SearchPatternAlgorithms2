#ifndef BBST_H
#define BBST_H

class AVLTree {
private:
    struct AVLNode {
        std::string str;
        int height;
        AVLNode* left;
        AVLNode* right;
        AVLNode(const std::string& s) : str(s), height(1), left(nullptr), right(nullptr) {}
    };
    AVLNode* root;
    int subtree_height(AVLNode* node);
    void update_height(AVLNode* node);
    int get_balance(AVLNode* node);
    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);
    AVLNode* insert(AVLNode* root, const std::string& word);
    bool check(AVLNode* root);

public:
    AVLTree();
    void insert(const std::string& word);
    bool search(const std::string& s) const;
    bool check();
    void loadDictionary(const std::string& filename);
};

AVLTree::AVLTree() : root(nullptr) {}

int AVLTree::subtree_height(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    } else {
        return node->height;
    }
}

int AVLTree::get_balance(AVLNode* node) {
    return subtree_height(node->left) - subtree_height(node->right);
}

void AVLTree::update_height(AVLNode* node) {
    node->height = 1 + std::max(subtree_height(node->left), subtree_height(node->right));
}

AVLTree::AVLNode* AVLTree::rightRotate(AVLNode* y) {
    if (!y ||!(y->left)) {
        return y;
    }

    AVLNode* x = y->left;
    AVLNode* z = x->right;

    x->right = y;
    y->left = z;

    update_height(y);
    update_height(x);

    return x;
}

AVLTree::AVLNode* AVLTree::leftRotate(AVLNode* x) {
    if (!x || !(x->right)) {
        return x;
    }

    AVLNode* y = x->right;
    AVLNode* z = y->left;

    y->left = x;
    x->right = z;

    update_height(x);
    update_height(y);

    return y;
}

AVLTree::AVLNode* AVLTree::insert(AVLNode* root, const std::string& word) {
    if (!root) {
        AVLNode* newNode = new AVLNode(word);
        newNode->str = word;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

    if (word < root->str) {
        root->left = insert(root->left, word);
    } else {
        root->right = insert(root->right, word);
    }

    update_height(root);
    int balance = get_balance(root);

    if (balance > 1) {
        if (word < root->left->str) {
            return rightRotate(root);
        } else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    } else if (balance < -1) {
        if (word > root->right->str) {
            return leftRotate(root);
        } else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    return root;
}

void AVLTree::insert(const std::string& word) {
    root = insert(root, word);
}

bool AVLTree::search(const std::string& s) const {
    AVLNode* ptr = root;

    while (ptr != nullptr) {
        if (s == ptr->str) {
            return true;
        } else if (s < ptr->str) {
            ptr = ptr->left;
        } else {
            ptr = ptr->right;
        }
    }

    return false;
}

bool AVLTree::check(AVLNode* root) {
    if (root == nullptr) {
        return true;
    }

    bool leftSubtreeValid = check(root->left);
    bool rightSubtreeValid = check(root->right);

    int bal = get_balance(root);
    if (bal < -1 || bal > 1) {
        return false;
    }

    return leftSubtreeValid && rightSubtreeValid;
}

bool AVLTree::check() {
    return check(root);
}

void AVLTree::loadDictionary(const std::string& filename) {
    std::ifstream file(filename);
    std::string word;
    if (file.is_open()) {
        while (file >> word) {
            insert(word);
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

#endif // BBST_H
