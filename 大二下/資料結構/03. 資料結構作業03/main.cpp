#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <sstream> // 用於 istringstream
#include <queue>
#include <map>
#include <functional> // 用於 function

using namespace std;
struct TreeNode
{
    string val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(""), left(nullptr), right(nullptr) {}
    TreeNode(string x) : val(x), left(nullptr), right(nullptr) {}
};

void clearTree(TreeNode *&root) // 清空樹
{
    if (root == NULL)
        return;

    clearTree(root->left);
    clearTree(root->right);
    delete root;
    root = NULL;
}
bool hasEmptyNodes(TreeNode *root)
{
    if (root == nullptr)
        return false;

    // 檢查當前節點
    if (root->val.empty())
        return true;

    // 遞迴檢查左右子樹
    return hasEmptyNodes(root->left) || hasEmptyNodes(root->right);
}
void post_order_helper(TreeNode *root, vector<string> &values) // 後序遍歷輔助函數
{
    if (root == NULL)
        return;

    // 先左子樹
    post_order_helper(root->left, values);

    // 再右子樹
    post_order_helper(root->right, values);

    // 最後是當前節點
    values.push_back(root->val);
}

void print_tree(TreeNode *root) // 後序遍歷輸出樹
{
    if (root == NULL)
        return;

    // 使用後序遍歷獲取所有節點值
    vector<string> values;
    post_order_helper(root, values);

    // 輸出節點值
    for (size_t i = 0; i < values.size(); i++)
    {
        cout << values[i];
        if (i < values.size() - 1)
            cout << " ";
    }
    cout << endl;
}

bool add_tree(TreeNode *&root, string data_num, string locat)
{
    if (root == NULL)
        return false; // 沒有根節點，無法添加

    TreeNode *current = root;

    for (int i = 0; i < locat.size(); i++)
    {
        if (locat[i] == 'L')
        {
            // 是最後一個字符
            if (i == locat.size() - 1)
            {
                if (current->left != nullptr)
                {
                    return false; // 位置已被占用
                }
                current->left = new TreeNode(data_num);
                return true;
            }

            // 不是最後一個字符，需要繼續往下
            if (current->left == nullptr)
            {
                // 原本應該報錯，但現在可以自動創建中間節點
                current->left = new TreeNode(""); // 使用默認值創建中間節點
            }
            current = current->left;
        }
        else if (locat[i] == 'R')
        {
            // 是最後一個字符
            if (i == locat.size() - 1)
            {
                if (current->right != nullptr)
                {
                    return false; // 位置已被占用
                }
                current->right = new TreeNode(data_num);
                return true;
            }

            // 不是最後一個字符，需要繼續往下
            if (current->right == nullptr)
            {
                // 原本應該報錯，但現在可以自動創建中間節點
                current->right = new TreeNode(""); // 使用默認值創建中間節點
            }
            current = current->right;
        }
        else
        {
            return false; // 非法字符
        }
    }

    return true; // 路徑為空的情況
}

// 輔助函數：獲取樹的高度
int getHeight(TreeNode *root)
{
    if (root == nullptr)
        return 0;
    return 1 + max(getHeight(root->left), getHeight(root->right));
}

void print_tree_diagram(TreeNode *root) // 輸出樹狀圖
{
    if (root == nullptr)
    {
        cout << "Empty tree" << endl;
        return;
    }

    // 獲取樹的深度
    int height = getHeight(root);

    // 計算每個節點的位置
    map<TreeNode *, pair<int, int>> positions;
    int maxWidth = 0;
    int minWidth = 0;

    function<void(TreeNode *, int, int)> calcPositions = [&](TreeNode *node, int depth, int pos)
    {
        if (node == nullptr)
            return;

        positions[node] = {depth, pos};
        maxWidth = max(maxWidth, pos);
        minWidth = min(minWidth, pos);

        // 遞迴計算子節點位置
        calcPositions(node->left, depth + 1, pos - (1 << (height - depth - 1)));
        calcPositions(node->right, depth + 1, pos + (1 << (height - depth - 1)));
    };

    calcPositions(root, 0, 0); // 從位置0開始

    // 調整所有位置以確保沒有負數，並添加額外margin
    int margin = 2; // 增加邊距，確保最左側的數字能完整顯示
    if (minWidth < 0)
    {
        int offset = -minWidth + margin;
        for (auto &p : positions)
        {
            p.second.second += offset;
        }
        maxWidth += offset;
    }
    else
    {
        // 即使沒有負數位置，也添加邊距
        for (auto &p : positions)
        {
            p.second.second += margin;
        }
        maxWidth += margin;
    }

    // 創建字符圖形，增加額外寬度以確保所有節點都能顯示
    int totalDepth = height * 2 - 1;
    vector<string> lines(totalDepth, string((maxWidth + margin + 1) * 2, ' '));

    // 填充節點和連接線
    for (const auto &p : positions)
    {
        TreeNode *node = p.first;
        int depth = p.second.first;
        int column = p.second.second;

        // 放置節點值，調整startPos計算確保數字不會被截斷
        string nodeValue = node->val; // 不需要to_string
        int startPos = 2 * column - (nodeValue.length() - 1) / 2;

        // 確保startPos不會為負
        startPos = max(0, startPos);

        // 確保替換操作不會越界
        if (startPos + nodeValue.length() <= lines[depth * 2].length())
        {
            lines[depth * 2].replace(startPos, nodeValue.length(), nodeValue);
        }
        else
        {
            lines[depth * 2].replace(0, lines[depth * 2].length(), nodeValue);
        }

        // 放置連接線
        if (node->left != nullptr)
        {
            int leftChildColumn = positions[node->left].second;
            int leftChildStartPos = 2 * leftChildColumn + 1;
            int linePos = 2 * column + 1;
            for (int i = leftChildStartPos; i < linePos; i++)
            {
                lines[depth * 2 + 1][i] = '_';
            }
        }
        if (node->right != nullptr)
        {
            int rightChildColumn = positions[node->right].second;
            int rightChildEndPos = 2 * rightChildColumn;
            int linePos = 2 * column + 1;
            for (int i = linePos + 1; i < rightChildEndPos; i++)
            {
                lines[depth * 2 + 1][i] = '_';
            }
        }
    }

    // 輸出樹狀圖
    for (const auto &line : lines)
    {
        cout << line << endl;
    }
}

int main()
{
    TreeNode *root = NULL;
    while (true)
    {
        // 清空前一次的樹
        clearTree(root);
        root = NULL;
        vector<string> input_data;
        string line;
        getline(cin, line);

        // 處理可能的開頭空行或空白
        if (line.empty())
        {
            getline(cin, line);
        }

        // 如果只包含 "()，則跳出
        if (line == "()")
        {
            break;
        }

        // 將一行拆分為多個節點資訊
        istringstream iss(line);
        string token;
        while (iss >> token)
        {
            if (token == "()")
            {
                break; // 讀到結束標記
            }
            input_data.push_back(token);
        }

        if (input_data.size() == 0)
            break;

        // 構建樹
        // 在主函數中，替換原來的樹構建邏輯
        bool valid_tree = true;

        // 1. 先收集所有節點信息
        vector<pair<string, string>> nodes;
        vector<pair<string, string>> rootNodes;

        for (int i = 0; i < input_data.size(); i++)
        {
            // 檢查輸入格式
            string data = input_data[i];
            size_t pos = data.find(',');

            // 確認格式為 (x,y)
            if (pos == string::npos || data[0] != '(' || data[data.size() - 1] != ')')
            {
                valid_tree = false;
                break;
            }

            string data_num = data.substr(1, pos - 1);
            string locat = data.substr(pos + 1, data.size() - pos - 2);

            // 檢查路徑字符是否合法
            for (char c : locat)
            {
                if (c != 'L' && c != 'R')
                {
                    valid_tree = false;
                    break;
                }
            }
            if (!valid_tree)
                break;

            // 分類節點：根節點或普通節點
            if (locat.empty())
            {
                rootNodes.push_back({data_num, locat});
            }
            else
            {
                nodes.push_back({data_num, locat});
            }
        }

        // 2. 檢查根節點數量
        if (rootNodes.size() != 1)
        {
            valid_tree = false;
        }

        // 3. 如果格式驗證通過，按照層級順序創建樹
        if (valid_tree)
        {
            // 創建根節點
            root = new TreeNode(rootNodes[0].first);

            // 按照路徑長度排序其他節點
            sort(nodes.begin(), nodes.end(), [](const pair<string, string> &a, const pair<string, string> &b)
                 { return a.second.length() < b.second.length(); });

            // 逐個嘗試添加節點
            for (const auto &node : nodes)
            {
                if (!add_tree(root, node.first, node.second))
                {
                    valid_tree = false;
                    break;
                }
            }
        }

        // 在 main 函數中修改最後的輸出部分
        if (valid_tree)
        {
            // 在輸出前檢查是否有空值節點
            if (hasEmptyNodes(root))
            {
                cout << "wrong data" << endl;
            }
            else
            {
                print_tree(root);
                print_tree_diagram(root); // 如果只需輸出後序遍歷結果，可以注釋此行
            }
        }
        else
        {
            cout << "wrong data" << endl;
        }
    }
}