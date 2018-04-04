#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <queue>
#include <sstream>
#include <string>

struct TreeNode {
    int val;
    std::unique_ptr<TreeNode> left;
    std::unique_ptr<TreeNode> right;

    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

static std::pair<TreeNode *, TreeNode *>
find(TreeNode *parent, TreeNode *root, int key) {
    if (root == nullptr) {
        return {nullptr, nullptr};
    }
    if (key < root->val) {
        return find(root, root->left.get(), key);
    }
    if (key > root->val) {
        return find(root, root->right.get(), key);
    }
    return {root, parent};
//    while (true) {
//        if (root == nullptr) {
//            return {nullptr, nullptr};
//        }
//        if (key < root->val) {
//            parent = root;
//            root = root->left.get();
//            continue;
//        }
//        if (key > root->val) {
//            parent = root;
//            root = root->right.get();
//            continue;
//        }
//        return {root, parent};
//    }
}

static std::unique_ptr<TreeNode> &find(std::unique_ptr<TreeNode> &root, int key) {
    if (root == nullptr) {
        return root;
    }
    if (key < root->val) {
        return find(root->left, key);
    }
    if (key > root->val) {
        return find(root->right, key);
    }
    return root;
}

static std::unique_ptr<TreeNode> *find_min(std::unique_ptr<TreeNode> *root) {
    auto min = root;
    while ((*min)->left != nullptr) {
        min = &(*min)->left;
    }
    return min;
}

class Solution {
public:
    void deleteNode(std::unique_ptr<TreeNode> &root, int key) {
        auto &node = find(root, key);
        if (node == nullptr) {
            return;
        }
        if (node->left != nullptr && node->right != nullptr) {
            auto chosen = find_min(&node->right);
            node->val = (*chosen)->val;
            deleteNode(node->right, (*chosen)->val);
            return;
        }
        if (node->left != nullptr) {
            node = std::move(node->left);
        } else if (node->right != nullptr) {
            node = std::move(node->right);
        } else {
            node = nullptr;
        }
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

static std::unique_ptr<TreeNode> stringToTreeNode(std::string input) {
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
    auto root = std::make_unique<TreeNode>(stoi(item));
    std::queue<TreeNode *> nodeQueue;
    nodeQueue.push(root.get());

    while (true) {
        TreeNode *node = nodeQueue.front();
        nodeQueue.pop();

        if (!getline(ss, item, ',')) {
            break;
        }

        trimLeftTrailingSpaces(item);
        if (item != "null") {
            int leftNumber = stoi(item);
            node->left = std::make_unique<TreeNode>(leftNumber);
            nodeQueue.push(node->left.get());
        }

        if (!getline(ss, item, ',')) {
            break;
        }

        trimLeftTrailingSpaces(item);
        if (item != "null") {
            int rightNumber = stoi(item);
            node->right = std::make_unique<TreeNode>(rightNumber);
            nodeQueue.push(node->right.get());
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
        q.push(node->left.get());
        q.push(node->right.get());
    }
    return "[" + output.substr(0, output.length() - 2) + "]";
}

static void test(const std::string &in, int key, const std::string &expected) {
    auto root = stringToTreeNode(in);
    Solution().deleteNode(root, key);
    std::string out = treeNodeToString(root.get());
    assert(out == expected);
}

int main() {
    test("[5,3,6,2,4,null,7]", 3,
         "[5, 4, 6, 2, null, null, 7, null, null, null, null]");
    test("[1,null,2]", 1, "[2, null, null]");
    test("[0]", 0, "[]");

    std::string line;
    while (getline(std::cin, line)) {
        auto root = stringToTreeNode(line);
        getline(std::cin, line);
        int key = stringToInteger(line);
        Solution().deleteNode(root, key);
        std::string out = treeNodeToString(root.get());
        std::cout << out << std::endl;
    }
    return 0;
}
