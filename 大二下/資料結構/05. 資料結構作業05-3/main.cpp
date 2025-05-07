#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct data_init
{
    int point;
    vector<int> path;
};

int find_point(vector<data_init> &data, int point, vector<bool> &visited, int &count)
{
    vector<int> temp_path = data[point].path;
    for (int i = 0; i < temp_path.size(); i++)//把連到的點先設為false
    {
        visited[temp_path[i]] = false;
    }
    vector<int> not_catch; // 這個點沒有被抓到的點
    for (int i = 0; i < visited.size(); i++)
    {
        if (visited[i])
        {
            not_catch.push_back(i);
        }
    }

    // cout << "point:" << point << " not_catch: ";
    // for (int i = 0; i < not_catch.size(); i++)
    // {
    //     cout << not_catch[i] << " ";
    // }
    // cout << endl;

    vector<int> dic(data.size(), 0);// 記錄每個已有點的出現次數
    for (int i = 0; i < not_catch.size(); i++)
    {
        for (int j = 0; j < data[not_catch[i]].path.size(); j++)
        {
            if (visited[data[not_catch[i]].path[j]] == false)
            {
                dic[data[not_catch[i]].path[j]]++;
            }
        }
    }
    // cout << "dic: ";
    // for (int i = 0; i < dic.size(); i++)
    // {
    //     cout << "point" << i << ":" << dic[i] << " ";
    // }
    // cout << endl;

    // 0167
    for (int i = 0; i < temp_path.size(); i++)//依照dic排序
    {
        for (int j = 0; j < temp_path.size(); j++)
        {
            if (dic[temp_path[i]] > dic[temp_path[j]])
            {
                swap(temp_path[i], temp_path[j]);
            }
        }
    }
    // cout << "temp_path: ";
    // for (int i = 0; i < temp_path.size(); i++)
    // {
    //     cout << temp_path[i] << " ";
    // }
    // cout << endl;

    bool flag = false;
    for (int i = 0; i < temp_path.size(); i++)// 依照temp_path的順序，檢查not_catch裡面有沒有被抓到的點
    {
        flag = false;
        // cout<< "temp_path[i]:" << temp_path[i] << endl;
        for (int j = 0; j < not_catch.size(); j++)
        {
            // cout<< "not_catch[j]:" << not_catch[j] << endl;
            for (int k = 0; k < data[temp_path[i]].path.size(); k++)
            {
                if (data[temp_path[i]].path[k] == not_catch[j])
                {
                    not_catch.erase(not_catch.begin() + j);
                    flag = true;
                }
            }
        }
        if (flag)
            count++;
    }
    // cout << "count:" << count << endl;
    return not_catch.size();// 剩下的點數量
}

int main()
{
    while (true)
    {
        int n;
        cin >> n;
        if (n <= 0)
            break;
        vector<data_init> data;
        // 資料讀入
        int number = 0;
        for (int i = 0; i < n; i++)
        {
            data_init temp;
            temp.point = i;
            for (int j = 0; j < n; j++)
            {
                cin >> number;
                if (number == 1)
                {
                    temp.path.push_back(j);
                }
            }
            data.push_back(temp);
        }

        // for (int i = 0; i < n; i++)
        // {
        //     cout << data[i].point << ": ";
        //     for (int j = 0; j < data[i].path.size(); j++)
        //     {
        //         cout << data[i].path[j] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;

        int min = 0;
        int count = 1;
        for (int i = 0; i < n; i++)
        {
            
            vector<bool> visited(n, true);
            // cout << "now point:" << data[i].point << endl;
            visited[data[i].point] = false;
            int p_lest = find_point(data, data[i].point, visited, count);
            if (p_lest == 0)
            {// 如果沒有剩下的點，代表這個點是最少的
                // cout << "count:" << count << endl;
                if (count < min || min == 0)
                {
                    min = count;
                }
            }
            else
            {// 如果有剩下的點，代表剩下的需要額外去抓
                // cout<<" lest"<<p_lest<<endl;
                // cout << "count:" << count + p_lest << endl;
                count += p_lest;
                if (count < min || min == 0)
                {
                    min = count;
                }
            }
            count = 1;
        }
        cout << min << endl;
    }

    return 0;
}
