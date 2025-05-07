#include <iostream>
#include <string>
#include <vector>

using namespace std;
int add_eq(int &f, int &r, vector<int> &sq, int n, int data)
{
    r = (r + 1) % n;
    if (r == f)
    {
        // cout << "queue is full" << endl;
        return 0;
    }
    sq[r] = data;
    return 1;
}
int del_eq(int &f, int &r, vector<int> &sq, int n)
{
    if (f == r)
    {
        // cout << "queue is empty" << endl;
        return -1;
    }
    f = (f + 1) % n;
    return sq[f];
}
int max_path(vector<vector<int>> v, int n, int point_now, vector<int> sequence)
{
    vector<int> temp_v(n, 0); // 紀錄走過的節點
    int front = 0;
    int rear = n;
    add_eq(front, rear, sequence, n, point_now);
    temp_v[point_now] = 1;
    // for (int i = 0; i < n; i++)
    //     cout << sequence[i] << " ";
    // cout << endl;
    int max = 0;
    bool flag = false;
    while (true)
    {
        vector<int> temp_sequence(n, 0);//建立新的sequence
        int temp_front = 0;
        int temp_rear = n;
        flag = false;
        // cout << "FR " << front << " " << rear << endl;
        if (front == (rear + 1) % n)
        {
            // cout << "break" << endl;
            break;
        }

        while (front != rear)
        {
            point_now = del_eq(front, rear, sequence, n);//現在的節點
            // cout << "point_now:" << point_now << endl;
            // cout << "FR :" << front << " " << rear << endl;
            for (int j = 0; j < n; j++)
            {
                if (v[point_now][j] != 0 && temp_v[j] == 0)//如果有連接且沒走過
                {
                    // cout << "+" << j << endl;
                    temp_v[j] = 1;
                    flag = true;
                    add_eq(temp_front, temp_rear, temp_sequence, n, j);
                    // cout << "temp front:" << temp_front << " temp rear:" << temp_rear << endl;
                }
            }
        }
        if (flag == false)
        {
            break;
        }
        // cout << "FR end :" << temp_front << " " << temp_rear << endl;
        front = temp_front;
        rear = temp_rear;
        sequence = temp_sequence;//更新sequence
        // for(int i=0;i<n;i++)
        //     cout<<sequence[i]<<" ";
        // cout<<endl;
        if (flag == true)
        {
            max++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (temp_v[i] == 0)
        {
            // cout << "has not connected" << endl;
            return -1;
        }
    }
    // cout << "max:" << --max << endl;
    return max;
}

int main()
{
    int n;
    while (true)
    {
        vector<vector<int>> v; // 存所有
        vector<int> line_v;    // 存每個節點最遠路徑
        cin >> n;
        if (n == 0)
        {
            break;
        }
        for (int i = 0; i < n; i++)
        {
            line_v.push_back(0);
            vector<int> temp;
            for (int j = 0; j < n; j++)
            {
                int x;
                cin >> x;
                temp.push_back(x);
            }
            v.push_back(temp);
        }

        // for (int i = 0; i < n; i++)
        // {
        //     for (int j = 0; j < n; j++)
        //     {
        //         cout << v[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << "-----------------" << endl;
        for (int i = 0; i < n; i++)
        {
            vector<vector<int>> temp_v = v;
            vector<int> sequence(n, 0); // 紀錄走過的節點
            // cout << "i:" << i << "---------------" << endl;
            line_v[i] = max_path(temp_v, n, i, sequence); // v:所有節點的連接狀況 n:節點數 i:當前節點
            // if (line_v[i] < 0)
            // {
            //     cout << "disconnected" << endl;
            //     break;
            // }
            // else
            // {
            //     cout << line_v[i] << endl;
            // }
        }
        int min = line_v[0];
        for (int i = 0; i < n; i++)
        {
            if (line_v[i] < min && line_v[i] > 0)
            {
                min = line_v[i];
            }
        }
        for (int i = 0; i < n; i++)
        {
            if (line_v[i] < 0)
            {
                cout << "disconnected" ;
                break;
            }
            if(line_v[i]==min)
                cout << i << " ";
        }
        cout << endl;
    }
}
