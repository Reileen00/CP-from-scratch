#include <bits/stdc++.h>
using namespace std;

const int xrr[5] = {1, 0, -1, 0,0};
const int yrr[5] = {0, 1, 0, -1,0};

vector<vector<bool>> vis;

void dfs(int x, int y, vector<vector<char>> &str, int m, int n) {
    if (x < 0 || y < 0 || x >= m || y >= n) return;
    if (vis[x][y] || str[x][y] == '#' || str[x][y] == 'L') return;

    vis[x][y] = true;

    int count = 0, dx = -1, dy = -1;

    for(int i = 0; i < 4; i++) {
        int newx = x + xrr[i];
        int newy = y + yrr[i];
        if(newx >= 0 && newx < m && newy >= 0 && newy < n) {
            if(str[newx][newy] == '.') {
                count++;
                dx = newx;
                dy = newy;
            }
        }
    }

    if(count == 1) {
        str[dx][dy] = '+';
        dfs(dx, dy, str, m, n);
    }
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        int m, n;
        cin >> m >> n;

        vector<vector<char>> str(m, vector<char>(n));
        vis = vector<vector<bool>>(m, vector<bool>(n, false));

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                cin >> str[i][j];
            }
        }

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(str[i][j] == 'L') {
                    for(int x = 0; x < 5; x++) {
                        int nx = i + xrr[x];
                        int ny = j + yrr[x];
                        if(nx >= 0 && nx < m && ny >= 0 && ny < n) {
                            dfs(nx, ny, str, m, n);
                        }
                    }
                }
            }
        }

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                cout << str[i][j];
            }
            cout << endl;
        }
    }

    return 0;
}
