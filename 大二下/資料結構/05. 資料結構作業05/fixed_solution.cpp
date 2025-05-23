#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
/*
---------------------------------------------------------------------------------------
|                                                                                      |
|                                                                                      |
|     這段程式碼的功能是從給定的鄰接矩陣中找出一個樹結構，並計算樹中分支度大於1的節點數       |
|                                                                                      |
|                                                                                      |
----------------------------------------------------------------------------------------

*/
struct Edge {
    int from, to;
};

// 並查集函數
int find(vector<int>& parent, int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent, parent[x]);
}

void unite(vector<int>& parent, int x, int y) {
    parent[find(parent, x)] = find(parent, y);
}

// 檢查是否為生成樹
bool isTree(const vector<Edge>& edges, int n) {
    // 必須有 n-1 條邊
    if (edges.size() != n - 1) return false;

    // 檢查是否連通且無環
    vector<int> parent(n);
    for (int i = 0; i < n; i++) parent[i] = i;

    for (auto& e : edges) {
        int x = find(parent, e.from), y = find(parent, e.to);
        if (x == y) return false; // 有環
        unite(parent, e.from, e.to);
    }

    // 檢查是否連通
    int root = find(parent, 0);
    for (int i = 1; i < n; i++)
        if (find(parent, i) != root) return false;

    return true;
}

// 計算樹中分支度大於1的節點數
int countBranchNodes(const vector<Edge>& edges, int n) {
    vector<int> degree(n, 0);
    for (auto& e : edges) {
        degree[e.from]++;
        degree[e.to]++;
    }

    int count = 0;
    for (int i = 0; i < n; i++)
        if (degree[i] > 1) count++;

    return count;
}

int main() {
    while (true) {
        int n;
        cin >> n;
        if (n <= 0) break;
        
        // 讀取鄰接矩陣
        vector<vector<int>> adj(n, vector<int>(n));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> adj[i][j];
        
        // 收集所有邊
        vector<Edge> allEdges;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (adj[i][j])
                    allEdges.push_back({i, j});
        
        int m = allEdges.size();
        int minBranchNodes = n; // 最大不超過n
        
        // 枚舉所有可能的n-1條邊的組合
        vector<bool> selected(m, false);
        fill(selected.begin(), selected.begin() + (n - 1), true);
        
        do {
            vector<Edge> tree;
            for (int i = 0; i < m; i++)
                if (selected[i])
                    tree.push_back(allEdges[i]);
            
            if (isTree(tree, n)) {
                int branchNodes = countBranchNodes(tree, n);
                minBranchNodes = min(minBranchNodes, branchNodes);
            }
        } while (prev_permutation(selected.begin(), selected.end()));
        
        cout << minBranchNodes << endl;
    }
    
    return 0;
}
