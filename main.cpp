
#include &lt;vector&gt;
#include &lt;iostream&gt;
#include &lt;algorithm&gt;
#include &lt;sstream&gt;
#include &lt;string&gt;

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
        vector&lt;int&gt; values;
        inorderTraversal(root, values);
        
        // Sort in descending order to get kth largest
        sort(values.begin(), values.end(), greater&lt;int&gt;());
        
        // Return kth largest (k-1 index since 0-based)
        return values[k-1];
    }
    
private:
    // Helper function to perform inorder traversal and collect values
    void inorderTraversal(TreeNode* node, vector&lt;int&gt;&amp; values) {
        if (node == nullptr) return;
        
        values.push_back(node-&gt;val);
        inorderTraversal(node-&gt;left, values);
        inorderTraversal(node-&gt;right, values);
    }
};

// Function to build tree from level order array
TreeNode* buildTreeFromLevelOrder(const vector&lt;int&gt;&amp; arr) {
    if (arr.empty() || arr[0] == -1) return nullptr;
    
    TreeNode* root = new TreeNode(arr[0]);
    vector&lt;TreeNode*&gt; queue;
    queue.push_back(root);
    
    int i = 1;
    while (i &lt; arr.size()) {
        TreeNode* current = queue[0];
        queue.erase(queue.begin());
        
        // Left child
        if (i &lt; arr.size() &amp;&amp; arr[i] != -1) {
            current-&gt;left = new TreeNode(arr[i]);
            queue.push_back(current-&gt;left);
        }
        i++;
        
        // Right child
        if (i &lt; arr.size() &amp;&amp; arr[i] != -1) {
            current-&gt;right = new TreeNode(arr[i]);
            queue.push_back(current-&gt;right);
        }
        i++;
    }
    
    return root;
}

// Function to parse input array from string
vector&lt;int&gt; parseArray(const string&amp; input) {
    vector&lt;int&gt; result;
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
            result.push_back(stoi(item));
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
    int cnt = stoi(cntStr);
    
    // Parse array and build tree
    vector&lt;int&gt; arr = parseArray(rootStr);
    TreeNode* root = buildTreeFromLevelOrder(arr);
    
    // Find kth largest
    Solution solution;
    int result = solution.kthLargest(root, cnt);
    
    // Output result
    cout &lt;&lt; result &lt;&lt; endl;
    
    return 0;
}
