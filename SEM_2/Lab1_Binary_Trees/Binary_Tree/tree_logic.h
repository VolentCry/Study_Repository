#ifndef TREE_LOGIC_H
#define TREE_LOGIC_H

#include <vector>

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* createNode(int value);
TreeNode* insertNode(TreeNode* root, int value);
TreeNode* findMin(TreeNode* node);
TreeNode* deleteNode(TreeNode* root, int value);

void storeBSTNodes(TreeNode* root, int* arr, int& index);
TreeNode* buildBalancedTree(const std::vector<int>& nodes, int start, int end);
void clearTree(TreeNode*& root);
TreeNode* balanceTree(TreeNode* root);

// подсчёт узлов
int countNodes(TreeNode* root);
TreeNode* buildBalancedTree(const int* arr, int start, int end);

void preOrderTraversal(TreeNode* root, int* arr, int& index);
void postOrderTraversal(TreeNode* root, int* arr, int& index);

#endif // TREE_LOGIC_H