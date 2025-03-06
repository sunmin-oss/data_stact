#include <iostream>
#include <string>
#include <vector>
// #include <windows.h>
// #include <conio.h>
/*
可以使用
*/
using namespace std;

struct road_init
{
    int now[3] = {0, 0, 0};                // 當前位置
    int direction[6] = {0, 0, 0, 0, 0, 0}; // 朝向 0右 1前 2上 3左 4後 5下
};

vector<road_init> road;
void print_map_bool(vector<vector<vector<bool>>> map, int x, int y, int z)//列印布林地圖
{
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            for (int k = 0; k < z; k++)
            {
                cout << map[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}
void print_map(vector<vector<vector<int>>> map, int x, int y, int z, vector<road_init> road) // 印出地圖
{
    for (int i = 0; i < x; i++)
    {
        // cout << "第" << i + 1 << "層" << endl;
        for (int j = 0; j < y; j++)
        {
            for (int k = 0; k < z; k++)
            {
                if (map[i][j][k] == 1)
                {
                    cout << "1 ";
                }
                else
                {
                    bool is_road = false;
                    for (int l = 0; l < road.size(); l++)
                    {
                        if (road[l].now[0] == i && road[l].now[1] == j && road[l].now[2] == k)
                        {
                            cout << "\033[33m" << "2 " << "\033[0m";
                            is_road = true;
                            break;
                        }
                    }
                    if (!is_road)
                    {
                        cout << "0 ";
                    }
                }
            }
            cout << endl;
        }
        cout << endl;
    }
}

bool chack_point_dir(vector<vector<vector<int>>> map, int x, int y, int z, road_init &road) // 檢查點是否可走
{
    // cout<<"檢查點是否可走"<<endl;
    // cout<<"now: "<<road.now[0]<<" "<<road.now[1]<<" "<<road.now[2]<<endl;
    if (road.now[0] + 1 < x && map[road.now[0] + 1][road.now[1]][road.now[2]] == 0) // 往上一層
    {
        // cout<<"往上可以一步"<<endl;
        road.direction[2] = 1;
    }
    if (road.now[0] - 1 >= 0 && map[road.now[0] - 1][road.now[1]][road.now[2]] == 0) // 往下一層
    {
        // cout<<"往下可以一步"<<endl;
        road.direction[5] = 1;
    }

    if (road.now[1] + 1 < y && map[road.now[0]][road.now[1] + 1][road.now[2]] == 0) // 往後一步
    {
        // cout<<"往後可以一步"<<endl;
        road.direction[4] = 1;
    }
    if (road.now[1] - 1 >= 0 && map[road.now[0]][road.now[1] - 1][road.now[2]] == 0) // 往前一步
    {
        // cout<<"往前可以一步"<<endl;
        road.direction[1] = 1;
    }

    if (road.now[2] + 1 < z && map[road.now[0]][road.now[1]][road.now[2] + 1] == 0) // 往右一步
    {
        // cout<<"往右可以一步"<<endl;
        road.direction[0] = 1;
    }
    if (road.now[2] - 1 >= 0 && map[road.now[0]][road.now[1]][road.now[2] - 1] == 0) // 往左一步
    {
        // cout<<"往左可以一步"<<endl;
        road.direction[3] = 1;
    }
    if (road.direction[0] == 0 && road.direction[1] == 0 && road.direction[2] == 0 && road.direction[3] == 0 && road.direction[4] == 0 && road.direction[5] == 0)
    {
        // cout<<"無法走"<<endl;
        return false;
    }
    return true;
}

bool chack_point_passed(vector<vector<vector<int>>> map, vector<road_init> &road, int now[3],vector<vector<vector<bool>>> map_bool) // 檢查點是否走過
{
    return !map_bool[now[0]][now[1]][now[2]];//快多了
    //可以用 只是太慢
    // for (int i = 0; i < road.size(); i++)
    // {
    //     if (road[i].now[0] == now[0] && road[i].now[1] == now[1] && road[i].now[2] == now[2])
    //     {
    //         return false;
    //     }
    // }
    // return true;
}

void back_road(vector<road_init> &road, vector<vector<vector<bool>>> &map) // 回退
{
    // cout<<"回退"<<endl;
    for (int i = road.size() - 1; i >= 0; i--)
    {
        if (road[i].direction[0] == 1 || road[i].direction[1] == 1 || road[i].direction[2] == 1 || road[i].direction[3] == 1 || road[i].direction[4] == 1 || road[i].direction[5] == 1)
        {
            // cout << "回退到" << road[i].now[0] << " " << road[i].now[1] << " " << road[i].now[2] << endl;
            // cout<<road[i].direction[0]<<" "<<road[i].direction[1]<<" "<<road[i].direction[2]<<" "<<road[i].direction[3]<<" "<<road[i].direction[4]<<" "<<road[i].direction[5]<<endl;
            map[road[road.size() - 1].now[0]][road[road.size() - 1].now[1]][road[road.size() - 1].now[2]] = 0;
            break;
        }
        else
        {
            // cout<<"刪除"<<road[i].now[0]<<" "<<road[i].now[1]<<" "<<road[i].now[2]<<endl;
            map[road[road.size() - 1].now[0]][road[road.size() - 1].now[1]][road[road.size() - 1].now[2]] = 0;
            road.pop_back();
        }
    }
}

int main()
{
    // SetConsoleOutputCP(CP_UTF8);
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
        vector<vector<vector<bool>>> map_bool(x, vector<vector<bool>>(y, vector<bool>(z)));//三圍布林
        for (int i = 0; i < x; i++) // 讀取地圖
        {
            for (int j = 0; j < y; j++)
            {
                for (int k = 0; k < z; k++)
                {
                    cin >> map[i][j][k];
                    map_bool[i][j][k] = map[i][j][k];
                }
            }
        }
        cin >> start_x >> start_y >> start_z; // 起點
        cin >> end_x >> end_y >> end_z;       // 終點
        // print_map_bool(map_bool,x,y,z);

        // 路徑搜尋
        int start[3] = {start_x - 1, start_y, start_z}; // 起點
        int end[3] = {end_x - 1, end_y, end_z};         // 終點
        int now[3] = {start_x - 1, start_y, start_z};   // 層 高 寬 當前位置
        // print_map(map, x, y, z);
        road_init temp_roadl;
        temp_roadl.now[0] = start[0];
        temp_roadl.now[1] = start[1];
        temp_roadl.now[2] = start[2];
        road.push_back(temp_roadl);
        int count = 0;
        // print_map_bool(map_bool,x,y,z);
        if (chack_point_dir(map, x, y, z, road[road.size() - 1]))//一開始就無法移動
        {
            while (true)
            {
                // 朝向 0右 1前 2上 3左 4後 5下
                //如果到終點
                if (road[road.size() - 1].now[0] == end[0] && road[road.size() - 1].now[1] == end[1] && road[road.size() - 1].now[2] == end[2])
                {
                    // cout<<"終點"<<endl;
                    map_bool[road[road.size() - 1].now[0]][road[road.size() - 1].now[1]][road[road.size() - 1].now[2]] = 0;
                    road.pop_back();
                    count++;//路線+1
                    // cout<<count<<endl;
                    back_road(road, map_bool);//退回
                    now[0] = road[road.size() - 1].now[0];
                    now[1] = road[road.size() - 1].now[1];
                    now[2] = road[road.size() - 1].now[2];
                }
                else if (road[road.size() - 1].direction[0] == 1) // 可以向右
                {
                    // cout<<"右"<<endl;
                    road[road.size() - 1].direction[0] = 0; // 走過此方向
                    map_bool[road[road.size() - 1].now[0]][road[road.size() - 1].now[1]][road[road.size() - 1].now[2]] = 1;//阻黨走過路
                    now[2]++;//向右
                    if (chack_point_passed(map, road, now,map_bool)) // 檢查是否走過
                    {
                        road.push_back({now[0], now[1], now[2]});
                        chack_point_dir(map, x, y, z, road[road.size() - 1]);//檢查還能走的方向
                        map_bool[road[road.size() - 1].now[0]][road[road.size() - 1].now[1]][road[road.size() - 1].now[2]] = 1;//阻黨走過路
                        road[road.size() - 1].direction[3] = 0; // 走過此方向
                    }
                    else
                    {
                        now[2]--;
                    }
                }
                else if (road[road.size() - 1].direction[1] == 1) // 可以向前
                {
                    // cout<<"前"<<endl;
                    road[road.size() - 1].direction[1] = 0; // 走過
                    map_bool[road[road.size() - 1].now[0]][road[road.size() - 1].now[1]][road[road.size() - 1].now[2]] = 1;
                    now[1]--;
                    if (chack_point_passed(map, road, now,map_bool)) // 檢查是否走過
                    {
                        road.push_back({now[0], now[1], now[2]});
                        chack_point_dir(map, x, y, z, road[road.size() - 1]);
                        map_bool[road[road.size() - 1].now[0]][road[road.size() - 1].now[1]][road[road.size() - 1].now[2]] = 1;
                        road[road.size() - 1].direction[4] = 0; // 走過
                    }
                    else
                    {
                        now[1]++;
                    }
                }
                else if (road[road.size() - 1].direction[2] == 1) // 可以向上
                {
                    // cout<<"上"<<endl;
                    road[road.size() - 1].direction[2] = 0; // 走過
                    map_bool[road[road.size() - 1].now[0]][road[road.size() - 1].now[1]][road[road.size() - 1].now[2]] = 1;
                    now[0]++;
                    if (chack_point_passed(map, road, now,map_bool)) // 檢查是否走過
                    {
                        road.push_back({now[0], now[1], now[2]});
                        chack_point_dir(map, x, y, z, road[road.size() - 1]);
                        map_bool[road[road.size() - 1].now[0]][road[road.size() - 1].now[1]][road[road.size() - 1].now[2]] = 1;
                        road[road.size() - 1].direction[5] = 0; // 走過
                    }
                    else
                    {
                        now[0]--;
                    }
                }
                else if (road[road.size() - 1].direction[3] == 1) // 可以向左
                {
                    // cout<<"左"<<endl;
                    road[road.size() - 1].direction[3] = 0; // 走過
                    map_bool[road[road.size() - 1].now[0]][road[road.size() - 1].now[1]][road[road.size() - 1].now[2]] = 1;
                    now[2]--;
                    if (chack_point_passed(map, road, now,map_bool) )// 檢查是否走過
                    {
                        road.push_back({now[0], now[1], now[2]});
                        chack_point_dir(map, x, y, z, road[road.size() - 1]);
                        map_bool[road[road.size() - 1].now[0]][road[road.size() - 1].now[1]][road[road.size() - 1].now[2]] = 1;
                        road[road.size() - 1].direction[0] = 0; // 走過
                    }
                    else
                    {
                        now[2]++;
                    }
                }
                else if (road[road.size() - 1].direction[4] == 1) // 可以向後
                {
                    // cout<<"後"<<endl;
                    road[road.size() - 1].direction[4] = 0; // 走過
                    map_bool[road[road.size() - 1].now[0]][road[road.size() - 1].now[1]][road[road.size() - 1].now[2]] = 1;
                    now[1]++;
                    // cout<<now[0]<<" "<<now[1]<<" "<<now[2]<<endl;
                    if (chack_point_passed(map, road, now,map_bool)) // 檢查是否走過
                    {
                        road.push_back({now[0], now[1], now[2]});
                        chack_point_dir(map, x, y, z, road[road.size() - 1]);
                        map_bool[road[road.size() - 1].now[0]][road[road.size() - 1].now[1]][road[road.size() - 1].now[2]] = 1;
                        road[road.size() - 1].direction[1] = 0; // 走過
                    }
                    else
                    {
                        now[1]--;
                    }
                }
                else if (road[road.size() - 1].direction[5] == 1) // 可以向下
                {
                    // cout<<"下"<<endl;
                    road[road.size() - 1].direction[5] = 0; // 走過
                    map_bool[road[road.size() - 1].now[0]][road[road.size() - 1].now[1]][road[road.size() - 1].now[2]] = 1;
                    now[0]--;
                    if (chack_point_passed(map, road, now,map_bool)) // 檢查是否走過
                    {
                        road.push_back({now[0], now[1], now[2]});
                        chack_point_dir(map, x, y, z, road[road.size() - 1]);
                        map_bool[road[road.size() - 1].now[0]][road[road.size() - 1].now[1]][road[road.size() - 1].now[2]] = 1;
                        road[road.size() - 1].direction[2] = 0; // 走過
                    }
                    else
                    {
                        now[0]++;
                    }
                }
                else
                {
                    // cout<<"now"<<road[road.size() - 1].now[0]<<road[road.size() - 1].now[1]<<road[road.size() - 1].now[2]<<endl;
                    // cout<<"end"<<end[0]<<end[1]<<end[2]<<endl;
                    // if (road[road.size() - 1].now[0] == end[0] && road[road.size() - 1].now[1] == end[1] && road[road.size() - 1].now[2] == end[2])
                    // {
                    //     //這沒用懶得刪
                    //     // cout<<"終點"<<endl;
                    //     road.pop_back();
                    //     count++;
                    //     // cout<<count<<endl;
                    //     back_road(road, map_bool);
                    //     now[0] = road[road.size() - 1].now[0];
                    //     now[1] = road[road.size() - 1].now[1];
                    //     now[2] = road[road.size() - 1].now[2];
                    // }
                    // else//死路
                    // {
                        // cout<<"wjo"<<endl;
                        back_road(road, map_bool);
                        // cout<<"ekdi"<<road[road.size()-1].now[0]<<road[road.size()-1].now[1]<<road[road.size()-1].now[2]<<endl;
                        now[0] = road[road.size() - 1].now[0];
                        now[1] = road[road.size() - 1].now[1];
                        now[2] = road[road.size() - 1].now[2];
                    // }
                    if (road.size() <= 0)
                        break;
                    // cout<<"回退"<<endl;
                    // cout<<road[road.size()-1].now[0]<<" "<<road[road.size()-1].now[1]<<" "<<road[road.size()-1].now[2]<<endl;
                }

                // for (int i = 0; i < road.size(); i++)
                // {
                //     cout << "point " << road[i].now[0] << " " << road[i].now[1] << " " << road[i].now[2]
                //          << " dir:右" << road[i].direction[0] << "前" << road[i].direction[1] << "上" << road[i].direction[2] << "左" << road[i].direction[3] << "後" << road[i].direction[4]
                //          << "下" << road[i].direction[5] << endl;
                // }
                // print_map(map, x, y, z, road);
                // print_map_bool(map_bool, x, y, z);
                // cout<<count<<endl;
                // system("pause");
            }
            // cout << "end" << endl;
            cout << count << endl;
            road.clear();
        }
        else
        {
            cout << 0 << endl;
            road.clear();
        }
    }
}
