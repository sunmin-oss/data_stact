#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print_map(const vector<vector<vector< int > > > &map, int x, int y, int z, int start_x, int start_y, int start_z, int end_x, int end_y, int end_z);

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
        vector<vector<vector< int > > > map(x, vector<vector< int > >(y, vector<int>(z))); // 三維陣列
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

        // 輸出地圖
        // print_map(map, x, y, z, start_x, start_y, start_z, end_x, end_y, end_z);

        /*
            路線搜尋
            每走一步檢查前後左右上下六個方向
            如果沒路退回上一步
            都可以走優先向右走
            如果走到終點印出路徑 並把路徑數+1 退回上一步走其他方向

        */
        int start[3] = {start_x - 1, start_y, start_z};
        int end[3] = {end_x - 1, end_y, end_z};
        int now[3] = {start_x - 1, start_y, start_z}; // 層 高 寬
        struct road_init
        {
            int x; // 層
            int y; // 高
            int z; // 寬
        };
        vector<road_init> road;
        int road_count = 0;
        cout << "\nstart:" << start[0] << " " << start[1] << " " << start[2] << endl;
        cout << "end:" << end[0] << " " << end[1] << " " << end[2] << endl;
        cout << "now:" << now[0] << " " << now[1] << " " << now[2] << endl;
        bool is_end = false;
        while(true)
        {
            if(now[0] == end[0] && now[1] == end[1] && now[2] == end[2])
            {
                is_end = true;
                break;
            }
            else if(now[2]+1 < z && map[now[0]][now[1]][now[2]+1] == 0)// 向右
            {
                now[2]++;
                road.push_back( { now[0], now[1], now[2] } );
            }
            else if(now[0]+1 < x && map[now[0]+1][now[1]][now[2]] == 0)// 上樓
            {
                now[0]++;
                road.push_back({now[0], now[1], now[2]});
            }
            else if(now[1]+1 < y && map[now[0]][now[1]+1][now[2]] == 0)// 向前
            {
                now[1]++;
                road.push_back({now[0], now[1], now[2]});
            }
            else if(now[2]-1 >= 0 && map[now[0]][now[1]][now[2]-1] == 0)// 向左
            {
                now[2]--;
                road.push_back({now[0], now[1], now[2]});
            }
            else if(now[0]-1 >= 0 && map[now[0]-1][now[1]][now[2]] == 0)// 下樓
            {
                now[0]--;
                road.push_back({now[0], now[1], now[2]});
            }
            else if(now[1]-1 >= 0 && map[now[0]][now[1]-1][now[2]] == 0)// 向後
            {
                now[1]--;
                road.push_back({now[0], now[1], now[2]});
            }
            else
            {
                if(road.size() == 0)
                {
                    cout << "no road" << endl;
                    break;
                }
                now[0] = road[road.size()-1].x;
                now[1] = road[road.size()-1].y;
                now[2] = road[road.size()-1].z;
                road.pop_back();
            }
            print_map(map, x, y, z, start_x, start_y, start_z, end_x, end_y, end_z);
            
        }

        print_map(map, x, y, z, start_x, start_y, start_z, end_x, end_y, end_z);
    }
}

// 印出地圖的函式
void print_map(const vector<vector<vector<int>>> &map, int x, int y, int z, int start_x, int start_y, int start_z, int end_x, int end_y, int end_z)
{
    cout << "start: " << start_x << " " << start_y << " " << start_z << endl;
    cout << "end: " << end_x << " " << end_y << " " << end_z << endl;
    for (int i = 0; i < x; i++)
    {
        cout << "layer " << i + 1 << endl;
        for (int j = 0; j < y; j++)
        {
            cout  << j;
            for (int k = 0; k < z; k++)
            {
                cout << map[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}