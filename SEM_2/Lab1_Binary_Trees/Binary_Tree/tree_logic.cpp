#include "tree_logic.h"

TreeNode* createNode(int value) {
    TreeNode* node = new TreeNode;
    node->value = value;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

TreeNode* insertNode(TreeNode* root, int value) {
    if (!root) return createNode(value);

    if (value < root->value) {
        root->left = insertNode(root->left, value);
    } else if (value > root->value) {
        root->right = insertNode(root->right, value);
    }
    return root;
}

TreeNode* findMin(TreeNode* node) {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

TreeNode* deleteNode(TreeNode* root, int value) {
    if (!root) return root;

    if (value < root->value) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->value) {
        root->right = deleteNode(root->right, value);
    } else {
        if (!root->left) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }
        TreeNode* temp = findMin(root->right);
        root->value = temp->value;
        root->right = deleteNode(root->right, temp->value);
    }
    return root;
}

void storeBSTNodes(TreeNode* root, std::vector<int>& nodes) {
    if (!root) return;
    storeBSTNodes(root->left, nodes);
    nodes.push_back(root->value);
    storeBSTNodes(root->right, nodes);
}

TreeNode* buildBalancedTree(const std::vector<int>& nodes, int start, int end) {
    if (start > end) return nullptr;
    int mid = (start + end) / 2;
    TreeNode* root = createNode(nodes[mid]);
    root->left = buildBalancedTree(nodes, start, mid - 1);
    root->right = buildBalancedTree(nodes, mid + 1, end);
    return root;
}

void clearTree(TreeNode*& root) {
    if (!root) return;
    clearTree(root->left);
    clearTree(root->right);
    delete root;
    root = nullptr;
}


void preOrderTraversal(TreeNode* root, std::vector<int>& result) {
    if (!root) return;
    result.push_back(root->value);
    preOrderTraversal(root->left, result);
    preOrderTraversal(root->right, result);
}

void postOrderTraversal(TreeNode* root, std::vector<int>& result) {
    if (!root) return;
    postOrderTraversal(root->left, result);
    postOrderTraversal(root->right, result);
    result.push_back(root->value);
}

int countNodes(TreeNode* root) {
    // рекурсивный подсчет количества узлов
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

void preOrderTraversal(TreeNode* root, int* arr, int& index) {
    if (!root) return;
    arr[index++] = root->value; // Корень
    preOrderTraversal(root->left, arr, index); // Левое
    preOrderTraversal(root->right, arr, index); // Правое
}

void storeBSTNodes(TreeNode* root, int* arr, int& index) {
    // симметричный обход
    if (!root) return;
    storeBSTNodes(root->left, arr, index); // Левое
    arr[index++] = root->value; // Корень
    storeBSTNodes(root->right, arr, index); // Правое
}

void postOrderTraversal(TreeNode* root, int* arr, int& index) {
    if (!root) return;
    postOrderTraversal(root->left, arr, index); // Левое
    postOrderTraversal(root->right, arr, index); // Правое
    arr[index++] = root->value; // Корень
}


TreeNode* buildBalancedTree(const int* arr, int start, int end) {
    // построение дерева
    if (start > end) return nullptr;

    int mid = (start + end) / 2;
    TreeNode* root = createNode(arr[mid]);

    root->left = buildBalancedTree(arr, start, mid - 1);
    root->right = buildBalancedTree(arr, mid + 1, end);

    return root;
}

TreeNode* balanceTree(TreeNode* root) {
    // балансировка дерева
    int n = countNodes(root);
    if (n == 0) return nullptr;
    int* arr = new int[n];
    int index = 0;

    storeBSTNodes(root, arr, index);

    clearTree(root);
    TreeNode* newRoot = buildBalancedTree(arr, 0, n - 1);
    delete[] arr;

    return newRoot;
}

TreeNode* findMax(TreeNode* node) {
    // Поиск максимального элемента
    while (node && node->right != nullptr) {
        node = node->right;
    }
    return node;
}