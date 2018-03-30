#include <algorithm>
#include <cassert>
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
find(TreeNode *parent, TreeNode *root, int key) {
    if (root == nullptr) {
        return {nullptr, nullptr};
    }
    if (key < root->val) {
        return find(root, root->left, key);
    }
    if (key > root->val) {
        return find(root, root->right, key);
    }
    return {root, parent};
//    while (true) {
//        if (root == nullptr) {
//            return {nullptr, nullptr};
//        }
//        if (key < root->val) {
//            parent = root;
//            root = root->left;
//            continue;
//        }
//        if (key > root->val) {
//            parent = root;
//            root = root->right;
//            continue;
//        }
//        return {root, parent};
//    }
}

static TreeNode *find_min(TreeNode *root) {
    TreeNode *min = root;
    while (min->left != nullptr) {
        min = min->left;
    }
    return min;
}

static TreeNode *
replace_in_parent(TreeNode *root, TreeNode *node, TreeNode *parent,
                  TreeNode *replacement) {
    if (parent == nullptr) {
        return replacement;
    }
    if (parent->left == node) {
        parent->left = replacement;
    } else {
        parent->right = replacement;
    }
    return root;
}

class Solution {
public:
    TreeNode *deleteNode(TreeNode *root, int key) {
        auto pair = find(nullptr, root, key);
        auto node = pair.first;
        if (node == nullptr) {
            return root;
        }
        if (node->left != nullptr && node->right != nullptr) {
            TreeNode *chosen = find_min(node->right);
            node->val = chosen->val;
            node->right = deleteNode(node->right, chosen->val);
            return root;
        }
        auto parent = pair.second;
        if (node->left != nullptr) {
            root = replace_in_parent(root, node, parent, node->left);
            node->left = nullptr;
        } else if (node->right != nullptr) {
            root = replace_in_parent(root, node, parent, node->right);
            node->right = nullptr;
        } else {
            root = replace_in_parent(root, node, parent, nullptr);
        }
        delete node;
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
    return "[" + output.substr(0, output.length() - 2) + "]";
}

static void test(const std::string &in, int key, const std::string &expected) {
    auto root = stringToTreeNode(in);
    auto ret = Solution().deleteNode(root, key);
    std::string out = treeNodeToString(ret);
    delete ret;
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

        auto ret = Solution().deleteNode(root, key);

        std::string out = treeNodeToString(ret);
        delete ret;
        std::cout << out << std::endl;
    }
    return 0;
}
