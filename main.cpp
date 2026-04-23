
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <cstddef>

using namespace std;

// Definition for a binary tree node
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    // Function to find the kth largest element in BST
    int kthLargest(TreeNode* root, int k) {
        count = k;
        result = -1;
        reverseInorder(root);
        return result;
    }
    
private:
    int count;
    int result;
    
    // Helper function to perform reverse inorder traversal
    // (right -> root -> left) to get values in descending order
    void reverseInorder(TreeNode* node) {
        if (node == nullptr || result != -1) return;
        
        // Traverse right subtree first (larger values)
        reverseInorder(node->right);
        
        // Visit current node
        count--;
        if (count == 0) {
            result = node->val;
            return;
        }
        
        // Traverse left subtree (smaller values)
        reverseInorder(node->left);
    }
};

// Function to build tree from level order array
TreeNode* buildTreeFromLevelOrder(const vector<int>& arr) {
    if (arr.empty() || arr[0] == -1) return nullptr;
    
    TreeNode* root = new TreeNode(arr[0]);
    vector<TreeNode*> queue;
    queue.push_back(root);
    
    int i = 1;
    while (i < arr.size() && !queue.empty()) {
        TreeNode* current = queue[0];
        queue.erase(queue.begin());
        
        // Left child
        if (i < arr.size() && arr[i] != -1 && arr[i] != 0) {
            current->left = new TreeNode(arr[i]);
            queue.push_back(current->left);
        }
        i++;
        
        // Right child
        if (i < arr.size() && arr[i] != -1 && arr[i] != 0) {
            current->right = new TreeNode(arr[i]);
            queue.push_back(current->right);
        }
        i++;
    }
    
    return root;
}

// Function to parse input array from string
vector<int> parseArray(const string& input) {
    vector<int> result;
    string temp = input;
    
    // Remove brackets
    temp.erase(remove(temp.begin(), temp.end(), '['), temp.end());
    temp.erase(remove(temp.begin(), temp.end(), ']'), temp.end());
    
    stringstream ss(temp);
    string item;
    while (getline(ss, item, ',')) {
        // Trim whitespace
        item.erase(0, item.find_first_not_of(" \t"));
        item.erase(item.find_last_not_of(" \t") + 1);
        
        if (item == "null" || item.empty()) {
            result.push_back(-1);  // Using -1 to represent null
        } else {
            try {
                result.push_back(stoi(item));
            } catch (const std::exception& e) {
                result.push_back(-1);
            }
        }
    }
    
    return result;
}

int main() {
    string input;
    getline(cin, input);
    
    // Extract root array and cnt from input
    // Input format: "root = [12, 5, 18, 2, 9, 15, 20], cnt = 4"
    size_t rootPos = input.find("root = ");
    size_t cntPos = input.find("cnt = ");
    
    if (rootPos == string::npos || cntPos == string::npos) {
        return 1;
    }
    
    // Extract root array string
    size_t rootStart = input.find('[', rootPos);
    size_t rootEnd = input.find(']', rootStart);
    string rootStr = input.substr(rootStart, rootEnd - rootStart + 1);
    
    // Extract cnt value
    string cntStr = input.substr(cntPos + 6);  // "cnt = " is 6 characters
    cntStr.erase(0, cntStr.find_first_not_of(" \t"));
    int cnt;
    try {
        cnt = stoi(cntStr);
    } catch (const std::exception& e) {
        return 1;
    }
    
    // Parse array and build tree
    vector<int> arr = parseArray(rootStr);
    TreeNode* root = buildTreeFromLevelOrder(arr);
    
    // Find kth largest
    Solution solution;
    int result = solution.kthLargest(root, cnt);
    
    // Output result
    cout << result << endl;
    
    return 0;
}
