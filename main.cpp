#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;

// Definition for a binary tree node
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    unordered_map<int, int> depth;  // value -> depth
    unordered_map<int, int> parent; // value -> parent value
    
    // Build tree from preorder traversal and record depth and parent info
    TreeNode* buildTree(vector<int>& preorder, int& index, int currentDepth, int parentVal) {
        if (index >= preorder.size() || preorder[index] == -1) {
            index++;
            return nullptr;
        }
        
        int val = preorder[index++];
        TreeNode* node = new TreeNode(val);
        
        // Record depth and parent for this node
        depth[val] = currentDepth;
        parent[val] = parentVal;
        
        // Build left and right subtrees
        node->left = buildTree(preorder, index, currentDepth + 1, val);
        node->right = buildTree(preorder, index, currentDepth + 1, val);
        
        return node;
    }
    
    // Clean up tree to prevent memory leaks
    void deleteTree(TreeNode* root) {
        if (root == nullptr) return;
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
    
public:
    // Check if two nodes are cousins (same depth, different parents)
    bool areCousins(int x, int y) {
        return (depth[x] == depth[y]) && (parent[x] != parent[y]);
    }
    
    // Main function to process the input and solve the problem
    void solve() {
        int q;
        cin >> q;
        
        // Read query pairs
        vector<pair<int, int>> queries(q);
        for (int i = 0; i < q; i++) {
            cin >> queries[i].first >> queries[i].second;
        }
        
        // Read preorder traversal
        string line;
        cin.ignore(); // Ignore newline after last query
        getline(cin, line);
        
        // Parse preorder traversal
        vector<int> preorder;
        stringstream ss(line);
        int val;
        while (ss >> val) {
            preorder.push_back(val);
        }
        
        // Build tree and record depth/parent info
        int index = 0;
        TreeNode* root = buildTree(preorder, index, 0, -1); // Root has no parent
        
        // Process queries
        for (int i = 0; i < q; i++) {
            int x = queries[i].first;
            int y = queries[i].second;
            cout << (areCousins(x, y) ? 1 : 0) << endl;
        }
        
        // Clean up
        deleteTree(root);
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}