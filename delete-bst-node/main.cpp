#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    ~TreeNode() {
        delete left;
        delete right;
    }
};

static std::pair<TreeNode *, TreeNode *>
find(TreeNode *root, TreeNode *parent, int key) {
    if (root == nullptr) {
        return {nullptr, nullptr};
    }
    if (key == root->val) {
        return {root, parent};
    }
    if (key < root->val) {
        return find(root->left, root, key);
    }
    return find(root->right, root, key);
}

static void add(TreeNode *root, TreeNode *node) {
    if (node == nullptr) {
        return;
    }
    if (root->left == nullptr && node->val < root->val) {
        root->left = node;
        return;
    }
    if (root->right == nullptr && node->val > root->val) {
        root->right = node;
        return;
    }
    if (node->val < root->val) {
        add(root->left, node);
        return;
    }
    add(root->right, node);
}

class Solution {
public:
    TreeNode *deleteNode(TreeNode *root, int key) {
        auto pair = find(root, nullptr, key);
        auto node = pair.first;
        auto parent = pair.second;
        if (node == nullptr) {
            return root;
        }
        if (node->left == nullptr && node->right == nullptr) {
            if (parent == nullptr) {
                delete node;
                return nullptr;
            }
            if (parent->left == node) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
            delete node;
            return root;
        }
        TreeNode *chosen = node->left == nullptr ? node->right : node->left;
        node->val = chosen->val;
        if (node->left != nullptr) {
            node->left = chosen->left;
            add(node, chosen->right);
        } else {
            node->right = chosen->right;
            add(node, chosen->left);
        }
        chosen->left = nullptr;
        chosen->right = nullptr;
        delete chosen;
        return root;
    }
};

static void trimLeftTrailingSpaces(std::string &input) {
    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return isspace(ch) == 0;
    }));
}

static void trimRightTrailingSpaces(std::string &input) {
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return isspace(ch) == 0;
    }).base(), input.end());
}

static TreeNode *stringToTreeNode(std::string input) {
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    if (input.empty()) {
        return nullptr;
    }

    std::string item;
    std::stringstream ss;
    ss.str(input);

    getline(ss, item, ',');
    auto root = new TreeNode(stoi(item));
    std::queue<TreeNode *> nodeQueue;
    nodeQueue.push(root);

    while (true) {
        TreeNode *node = nodeQueue.front();
        nodeQueue.pop();

        if (!getline(ss, item, ',')) {
            break;
        }

        trimLeftTrailingSpaces(item);
        if (item != "null") {
            int leftNumber = stoi(item);
            node->left = new TreeNode(leftNumber);
            nodeQueue.push(node->left);
        }

        if (!getline(ss, item, ',')) {
            break;
        }

        trimLeftTrailingSpaces(item);
        if (item != "null") {
            int rightNumber = stoi(item);
            node->right = new TreeNode(rightNumber);
            nodeQueue.push(node->right);
        }
    }
    return root;
}

static int stringToInteger(const std::string &input) {
    return stoi(input);
}

static std::string treeNodeToString(TreeNode *root) {
    if (root == nullptr) {
        return "[]";
    }

    std::string output = "";
    std::queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode *node = q.front();
        q.pop();

        if (node == nullptr) {
            output += "null, ";
            continue;
        }

        output += std::to_string(node->val) + ", ";
        q.push(node->left);
        q.push(node->right);
    }
    delete root;
    return "[" + output.substr(0, output.length() - 2) + "]";
}

int main() {
    std::string line;
    while (getline(std::cin, line)) {
        TreeNode *root = stringToTreeNode(line);
        getline(std::cin, line);
        int key = stringToInteger(line);

        TreeNode *ret = Solution().deleteNode(root, key);

        std::string out = treeNodeToString(ret);
        std::cout << out << std::endl;
    }
    return 0;
}
