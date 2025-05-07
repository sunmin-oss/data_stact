#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct point_init
{
    int point;                      // 此點的編號
    int point_weight;               // 此點的權重
    bool connected = false;         // 是否有連接
    vector<int> point_neigh_weight; // 此點到鄰近點的路徑權重
};

struct point_info_init // 紀路權重 以及上一個點的編號
{
    int weight = INT16_MAX; // 紀錄路徑權重
    int point = NULL;       // 紀錄上個點的編號
};

bool not_point(const vector<bool> visited, const vector<point_init> point) // 判斷是否為點
{
    for (int i = 0; i < point.size(); i++)
    {
        // cout<<"visited: " << visited[i] << " point: " << point[i].point << "connected: " << point[i].connected << endl; // 輸出是否有連接
        // system("pause"); // 暫停
        if (point[i].connected == true && visited[i] == false) // 如果有連接且沒有訪問過
        {
            return false; // 還不能節數
        }
    }
    return true; // 可以結束
}

int find_next_point(const vector<point_info_init> point_info, const vector<bool> visited) // 找到下一個點
{
    int min_weight = INT16_MAX; // 設定最小路徑權重
    int next_point = -1;        // 設定下一個點
    for (int i = 0; i < point_info.size(); i++)
    {
        if (visited[i] == false && point_info[i].weight < min_weight) // 如果沒有訪問過且路徑權重小於最小路徑權重
        {
            min_weight = point_info[i].weight; // 更新最小路徑權重
            next_point = i;                    // 更新下一個點
        }
    }
    return next_point;
}

int main()
{
    int n;
    while (true)
    {
        cin >> n;
        if (n <= 0)
            break;
        vector<point_init> point(n);
        for (int i = 0; i <= n; i++)
        {
            bool No_connection = false;
            for (int j = 0; j < n; j++)
            {
                if (i == 0) // 第一次輸入每個點的權重
                {
                    point[j].point = j;           // 設定點的編號
                    cin >> point[j].point_weight; // 設定點的權重
                }
                else
                {
                    int weight;
                    cin >> weight; // 設定點的權重
                    if (weight > 0)
                    {
                        point[i - 1].point_neigh_weight.push_back(weight); // 設定點到鄰近點的路徑權重
                        No_connection = true;                              // 設定有連接
                    }
                    else
                    {
                        point[i - 1].point_neigh_weight.push_back(0); // 設定點到鄰近點的路徑權重
                    }
                }
            }
            if (No_connection == false) // 如果沒有連接
            {
                point[i - 1].connected = false; // 設定沒有連接
            }
            else
            {
                point[i - 1].connected = true; // 設定有連接
            }
        }

        int start_point;
        cin >> start_point; // 設定起始點

        // cout << "start_point: " << start_point << endl; // 輸出起始點
        // for (int i = 0; i < n; i++)
        // {
        //     cout << point[i].point << " ";                                             // 輸出點的編號
        //     cout << "point weight: " << point[i].point_weight << " connectde weight:"; // 輸出點的權重
        //     for (int j = 0; j < point[i].point_neigh_weight.size(); j++)
        //     {
        //         cout << point[i].point_neigh_weight[j] << " "; // 輸出點到鄰近點的路徑權重
        //     }
        //     cout << " connected: " << point[i].connected; // 輸出是否有連接
        //     cout << endl;
        // }
        // cout << endl;

        // 使用 Dijkstra 演算法計算start_point到其他點的最短路徑
        vector<point_info_init> point_info(n); // 紀錄路徑權重 以及上一個點的編號
        vector<bool> visited(n, false);        // 紀錄每個點是否已經訪問過
        int next_point = start_point;          // 設定下一個點
        point_info[start_point].weight = 0;    // 設定起始點的路徑權重為0
        point_info[start_point].point = -1;    // 起始點的上一個點為-1

        while (not_point(visited, point) == false) // 如果還有點沒有訪問過
        {
            // cout << "next_point: " << next_point << endl; // 輸出下一個點
            for (int i = 0; i < point[next_point].point_neigh_weight.size(); i++)
            {
                if (point[next_point].point_neigh_weight[i] > 0 && visited[i] == false) // 如果有連接且沒有訪問過
                {
                    int weight = point_info[next_point].weight + point[next_point].point_neigh_weight[i] + point[next_point].point_weight; // 計算路徑權重==目前的路徑權重+鄰近點的路徑權重+點的權重
                    if (weight < point_info[i].weight)                                                                                     // 如果路徑權重小於目前的路徑權重
                    {
                        point_info[i].weight = weight;    // 更新路徑權重
                        point_info[i].point = next_point; // 更新上一個點
                    }
                }
            }
            visited[next_point] = true;                        // 設定已經訪問過
            next_point = find_next_point(point_info, visited); // 找到下一個點
            if (next_point == -1)                              // 如果沒有下一個點
            {
                break; // 結束
            }
            // for (int i = 0; i < point_info.size(); i++)
            // {
            //     cout << "point: " << point[i].point << " weight: " << point_info[i].weight << " point: " << point_info[i].point << endl; // 輸出點的編號、路徑權重、上一個點的編號
            // }
            // system("pause"); // 暫停
        }

        // for (int i = 0; i < n; i++)
        // {
        //     if (point_info[i].weight == INT16_MAX) // 如果路徑權重為最大值
        //     {
        //         cout << "point: " << point[i].point << "infinity" << endl; //
        //     }
        //     else
        //     {
        //         if (point_info[i].point == -1) // 如果上一個點為-1
        //         {
        //             cout << "point: " << point[i].point << " weight: " << point_info[i].weight << " point: " << point_info[i].point << endl; // 輸出點的編號、路徑權重、上一個點的編號
        //         }
        //         else
        //             cout << "point: " << point[i].point << " weight: " << point_info[i].weight - point[start_point].point_weight << " point: " << point_info[i].point << endl; // 輸出點的編號、路徑權重、上一個點的編號
        //     }
        // }
        for (int i = 0; i < n; i++)
        {
            if (point_info[i].weight == INT16_MAX) // 如果路徑權重為最大值
            {
                cout << "infinity "; //
            }
            else
            {
                if (point_info[i].point == -1) // 如果上一個點為-1
                {
                    cout << point_info[i].weight << " "; // 輸出點的編號、路徑權重、上一個點的編號
                }
                else
                    cout << point_info[i].weight - point[start_point].point_weight << " "; // 輸出點的編號、路徑權重、上一個點的編號
            }
        }
        cout << endl;
    }
}
