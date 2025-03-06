#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <conio.h>

using namespace std;
/*
    找到出口
    退回上一路口
*/
struct road_init
{
    int sideroad = 0;
    int x; // 層
    int y; // 高
    int z; // 寬
};

int chack_end(vector<vector<vector<int>>> &map, int &now_x, int &now_y, int &now_z, int end_x, int end_y, int end_z, vector<road_init> &road, int &road_count);
int check_sideroad(const vector<vector<vector<int>>> &map, int x, int y, int z, int now_x, int now_y, int now_z);
void print_map(const vector<vector<vector<int>>> &map, int x, int y, int z, int start_x, int start_y, int start_z, int end_x, int end_y, int end_z);

vector<road_init> road;

int main()
{
    int x = 0, y = 0, z = 0;
    int start_x = 0, start_y = 0, start_z = 0;
    int end_x = 0, end_y = 0, end_z = 0;
    while (true)
    {
        cin >> x >> y >> z; // 層 高 寬
        if (x == 0 && y == 0 && z == 0)
        {
            break;
        }
        vector<vector<vector<int>>> map(x, vector<vector<int>>(y, vector<int>(z))); // 三維陣列
        for (int i = 0; i < x; i++)                                                 // 讀取地圖
        {
            for (int j = 0; j < y; j++)
            {
                for (int k = 0; k < z; k++)
                {
                    cin >> map[i][j][k];
                }
            }
        }
        cin >> start_x >> start_y >> start_z; // 起點
        cin >> end_x >> end_y >> end_z;       // 終點

        int start[3] = {start_x - 1, start_y, start_z};
        int end[3] = {end_x - 1, end_y, end_z};
        int now[3] = {start_x - 1, start_y, start_z}; // 層 高 寬

        int road_count = 0; // 路徑數量
        // cout << "start:" << start[0] << " " << start[1] << " " << start[2] << endl;
        // cout << "end:" << end[0] << " " << end[1] << " " << end[2] << endl;
        // cout << "now:" << now[0] << " " << now[1] << " " << now[2] << endl;
        map[now[0]][now[1]][now[2]] = 2;
        road.push_back({check_sideroad(map, x, y, z, now[0], now[1], now[2]), now[0], now[1], now[2]});
        // cout<<"start sider:"<<road[0].sideroad<<endl;
        while (true)
        {
            if (now[2] + 1 < z && map[now[0]][now[1]][now[2] + 1] == 0) // 向右
            {
                now[2]++;
                road.push_back({check_sideroad(map, x, y, z, now[0], now[1], now[2]), now[0], now[1], now[2]});
                map[now[0]][now[1]][now[2]] = 2;
                chack_end(map, now[0], now[1], now[2], end_x - 1, end_y, end_z, road, road_count);
            }
            else if (now[1] + 1 < y && map[now[0]][now[1] + 1][now[2]] == 0) // 向前
            {
                now[1]++;
                road.push_back({check_sideroad(map, x, y, z, now[0], now[1], now[2]), now[0], now[1], now[2]});
                map[now[0]][now[1]][now[2]] = 2;
                chack_end(map, now[0], now[1], now[2], end_x - 1, end_y, end_z, road, road_count);
            }
            else if (now[0] + 1 < x && map[now[0] + 1][now[1]][now[2]] == 0) // 上樓
            {
                now[0]++;
                road.push_back({check_sideroad(map, x, y, z, now[0], now[1], now[2]), now[0], now[1], now[2]});
                map[now[0]][now[1]][now[2]] = 2;
                chack_end(map, now[0], now[1], now[2], end_x - 1, end_y, end_z, road, road_count);
            }
            else if (now[2] - 1 >= 0 && map[now[0]][now[1]][now[2] - 1] == 0) // 向左
            {
                now[2]--;
                road.push_back({check_sideroad(map, x, y, z, now[0], now[1], now[2]), now[0], now[1], now[2]});
                map[now[0]][now[1]][now[2]] = 2;
                chack_end(map, now[0], now[1], now[2], end_x - 1, end_y, end_z, road, road_count);
            }
            else if (now[1] - 1 >= 0 && map[now[0]][now[1] - 1][now[2]] == 0) // 向後
            {
                now[1]--;
                road.push_back({check_sideroad(map, x, y, z, now[0], now[1], now[2]), now[0], now[1], now[2]});
                map[now[0]][now[1]][now[2]] = 2;
                chack_end(map, now[0], now[1], now[2], end_x - 1, end_y, end_z, road, road_count);
            }
            else if (now[0] - 1 >= 0 && map[now[0] - 1][now[1]][now[2]] == 0) // 下樓
            {
                now[0]--;
                road.push_back({check_sideroad(map, x, y, z, now[0], now[1], now[2]), now[0], now[1], now[2]});
                map[now[0]][now[1]][now[2]] = 2;
                chack_end(map, now[0], now[1], now[2], end_x - 1, end_y, end_z, road, road_count);
            }
            else
            {
                // cout<<road.size()<<endl;
                if (road.size() == 1)
                {
                    // cout << "no road" << endl;
                    cout << road_count << endl;
                    break;
                }
                else
                {
                    if (map[now[0]][now[1]][now[2]] == 2)
                    {
                        map[now[0]][now[1]][now[2]] = 0;
                        road.pop_back();
                        now[0] = road[road.size() - 1].x;
                        now[1] = road[road.size() - 1].y;
                        now[2] = road[road.size() - 1].z;
                        cout << "come back to " << now[0] << " " << now[1] << " " << now[2] << endl;
                    }
                    else
                    {
                        map[now[0]][now[1]][now[2]] = 1;
                        road.pop_back();
                        now[0] = road[road.size() - 1].x;
                        now[1] = road[road.size() - 1].y;
                        now[2] = road[road.size() - 1].z;
                        cout << "come back to " << now[0] << " " << now[1] << " " << now[2] << endl;
                    }
                }
            }
            // for(int i = 0; i < road.size(); i++)
            // {
            //     cout<<"road "<<i<<" "<<road[i].sideroad<<endl;
            // }
            print_map(map, x, y, z, start_x, start_y, start_z, end_x, end_y, end_z);
            // for (int i = 0; i < road.size(); i++)
            // {
            //     cout << "road " << i << " " << road[i].sideroad <<"("<< road[i].x <<","<<road[i].y <<","<<road[i].z<<")"<< endl;
            // }
            cout << road[road.size() - 1].sideroad << endl;
            system("pause");
        }

        // print_map(map, x, y, z, start_x, start_y, start_z, end_x, end_y, end_z);
    }
}

int chack_end(vector<vector<vector<int>>> &map, int &now_x, int &now_y, int &now_z, int end_x, int end_y, int end_z, vector<road_init> &road, int &road_count)
{
    cout << "end:" << end_x << " " << end_y << " " << end_z << endl;
    cout << "now:" << now_x << " " << now_y << " " << now_z << endl;
    if (now_x == end_x && now_y == end_y && now_z == end_z) // 到達終點
    {
        cout << "come to end" << endl;
        map[now_x][now_y][now_z] = 0; // 終點
        road.pop_back();              // 移除終點
        now_x = road[road.size() - 1].x;
        now_y = road[road.size() - 1].y;
        now_z = road[road.size() - 1].z;
        while (road.size() > 0) // 退回上一路口
        {
            if (road[road.size() - 1].sideroad >= 2)
            {
                cout << "come back to " << now_x << " " << now_y << " " << now_z << endl;
                now_x = road[road.size() - 1].x;
                now_y = road[road.size() - 1].y;
                now_z = road[road.size() - 1].z;
                break;
            }
            else
            {
                map[now_x][now_y][now_z] = 1; // 走過的地方擋起來
                road.pop_back();
                now_x = road[road.size() - 1].x;
                now_y = road[road.size() - 1].y;
                now_z = road[road.size() - 1].z;
            }
        }
        cout << "come back to " << now_x << " " << now_y << " " << now_z << endl;
        road_count++;

        return 1;
    }
    else
        return 0;
}

int check_sideroad(const vector<vector<vector<int>>> &map, int x, int y, int z, int now_x, int now_y, int now_z)
{
    int side_road = 0;
    if (now_x - 1 >= 0 && map[now_x - 1][now_y][now_z] == 0)
    {
        side_road++;
    }
    if (now_x + 1 < x && map[now_x + 1][now_y][now_z] == 0)
    {
        side_road++;
    }
    if (now_y - 1 >= 0 && map[now_x][now_y - 1][now_z] == 0)
    {
        side_road++;
    }
    if (now_y + 1 < y && map[now_x][now_y + 1][now_z] == 0)
    {
        side_road++;
    }
    if (now_z - 1 >= 0 && map[now_x][now_y][now_z - 1] == 0)
    {
        side_road++;
    }
    if (now_z + 1 < z && map[now_x][now_y][now_z + 1] == 0)
    {
        side_road++;
    }
    return side_road;
}

// 印出地圖的函式
void print_map(const vector<vector<vector<int>>> &map, int x, int y, int z, int start_x, int start_y, int start_z, int end_x, int end_y, int end_z)
{
    cout << "start: " << start_x << " " << start_y << " " << start_z << endl;
    cout << "end: " << end_x << " " << end_y << " " << end_z << endl;

    for (int i = 0; i < x; i++)
    {
        // cout << "layer " << i + 1 << endl;
        for (int j = 0; j < y; j++)
        {
            // cout  << j;
            for (int k = 0; k < z; k++)
            {
                if (map[i][j][k] == 2)
                {
                    cout << "\033[33m" << "2" << "\033[0m" << " ";
                }
                else
                    cout << map[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}