// #include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
using namespace std;
/*
    絲路問題
    先從最少邊的節點開始
    一個一個節點檢查
    使用酒桶排序法 紀錄
    節點是否有連接過
    所有節點都檢查一次

    ex:
    7
         0 1 2 3 4 5 6
     0   0 1 1 1 0 0 0
     1   1 0 0 0 1 1 1
     2   1 0 0 0 1 1 1
     3   1 0 0 0 1 1 1
     4   0 1 1 1 0 1 1
     5   0 1 1 1 1 0 1
     6   0 1 1 1 1 1 0
    排序前
    第0節點:邊數為3: 1 2 3
    第1節點:邊數為4: 0 4 5 6
    第2節點:邊數為4: 0 4 5 6
    第3節點:邊數為4: 0 4 5 6
    第4節點:邊數為5: 1 2 3 5 6
    第5節點:邊數為5: 1 2 3 4 6
    第6節點:邊數為5: 1 2 3 4 5
    排序後
    第0節點:邊數為3: 1 2 3
    第1節點:邊數為4: 0 4 5 6
    第2節點:邊數為4: 0 4 5 6
    第3節點:邊數為4: 0 4 5 6
    第4節點:邊數為5: 1 2 3 5 6
    第5節點:邊數為5: 1 2 3 4 6
    第6節點:邊數為5: 1 2 3 4 5

    從第0節點開始檢查 連結1 2 3 節點 下個節點為4 第4節點連結1 2 3 5 6 節點 故最多為2
      0 1 2 3 4 5 6
    0 0 1 1 1 0 0 0
    4 0 1 1 1 0 1 1
    從第1節點開始檢查 連結0 4 5 6 節點 下個節點為2 第2節點連結0 4 5 6 節點 下個節點為3 第3節點連結0 4 5 6 節點
      0 1 2 3 4 5 6
    1 1 0 0 0 1 1 1
    2 1 0 0 0 1 1 1
    3 1 0 0 0 1 1 1
    從第2節點開始檢查 連結0 4 5 6 節點 下個節點為3 第3節點連結0 4 5 6 節點 下個節點為1 第1節點連結0 4 5 6 節點
      0 1 2 3 4 5 6
    2 1 0 0 0 1 1 1
    3 1 0 0 0 1 1 1
    1 1 0 0 0 1 1 1
    從第3節點開始檢查 連結0 4 5 6 節點 下個節點為1 第1節點連結0 4 5 6 節點 下個節點為2 第2節點連結0 4 5 6 節點
      0 1 2 3 4 5 6
    3 1 0 0 0 1 1 1
    1 1 0 0 0 1 1 1
    2 1 0 0 0 1 1 1
    從第4節點開始檢查 連結1 2 3 5 6 節點 下個節點為0 第0節點連結1 2 3 節點 下個節點為4 第4節點連結1 2 3 5 6 節點
      0 1 2 3 4 5 6
    4 0 1 1 1 0 1 1
    0 0 1 1 1 0 0 0
    從第5節點開始檢查 連結1 2 3 4 6 節點 下個節點為0 第0節點連結1 2 3 節點 下個節點為4 第4節點連結1 2 3 5 6 節點
      0 1 2 3 4 5 6
    5 0 1 1 1 1 0 1
    0 0 1 1 1 0 0 0
    從第6節點開始檢查 連結1 2 3 4 5 節點 下個節點為0 第0節點連結1 2 3 節點 下個節點為4 第4節點連結1 2 3 5 6 節點
      0 1 2 3 4 5 6
    6 0 1 1 1 1 1 0
    0 0 1 1 1 0 0 0
 */
struct arr_init
{
    int a;                // 第幾個節點
    int line;             // 有幾條線
    vector<int> line_num; // 連接的線
    vector<int> arr;
};
vector<arr_init> v;
int main()
{
    int n = 0;
    while (n >= 0)
    {
        cin >> n;
        if (n < 0)
        {
            break;
        }
        // 輸入矩陣
        for (int i = 0; i < n; i++)
        {
            arr_init temp;
            temp.a = i;
            temp.line = 0;
            for (int j = 0; j < n; j++)
            {
                int num;
                cin >> num;
                if (num == 1)
                {
                    temp.line += 1;
                    temp.line_num.push_back(j);
                }
                temp.arr.push_back(num);
            }
            v.push_back(temp);
        }

        // 排序邊最少的先做
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (v[i].line < v[j].line)
                {
                    swap(v[i], v[j]);
                }
            }
        }
        // 輸出矩陣
        // for (int i = 0; i < n; i++)
        // {
        //     cout << v[i].a << ":" << v[i].line << ": ";
        //     for (int j = 0; j < v[i].line; j++)
        //     {
        //         cout << v[i].line_num[j] << " ";
        //     }
        //     cout << endl;
        // }
        // 尋找最多節點數

        int max = 0;
        vector<int> bucket;
        for (int i = 0; i < n; i++) // 創建酒桶
        {
            bucket.push_back(0);
        }

        for (int i = 0; i < n; i++)
        {
            int index = 0;
            for (int j = i; j < n + i; j++)
            {
                index = j % n;
                if (bucket[v[index].a] == 0) // 檢查是否已有節點
                {
                    for (int k = 0; k < v[index].line; k++)
                    { // 將節點的連接線標記
                        bucket[v[index].line_num[k]] = 1;
                    }
                }
            }
            int count = 0;
            // 數節點
            for (int j = 0; j < n; j++)
            {
                if (bucket[j] == 0)
                {
                    count += 1;
                }
            }
            if (count > max)
            {
                max = count;
            }
        }

        cout << max << endl;
        v.clear();
    }
}
