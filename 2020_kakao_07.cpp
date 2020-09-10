#include <vector>
#include <iostream>
#include <queue>
#pragma warning(disable:4996)
using namespace std;

int n;
int dy[4] = { 0,1,0,-1 };   // 시계 방향
int dx[4] = { 1,0,-1,0 };
int rty[4] = { -1,1,1,-1 }; // 시계 방향
int rtx[4] = { 1,1,-1,-1 };
bool visit[100][100][4];
struct Point {
    int y, x, dir, t;
    Point(int y, int x, int dir, int t) :y(y), x(x), dir(dir), t(t) {}
};
// L 을 기준으로 품
//  L -- R  dir: 0    L   dir:1   R
//                    |           |
//  R -- L  dir: 2    R           L   dir: 3

bool chk(int ly, int lx, int ry, int rx) {
    if (ly < 0 || lx < 0 || ly >= n || lx >= n) return 0;
    if (ry < 0 || rx < 0 || ry >= n || rx >= n) return 0;
    return 1;
}

int solution(vector<vector<int>> board) {
    n = board.size();
    queue<Point> q;
    q.push(Point(0, 0, 0, 0));
    // visit 경우에도 L을 기준으로 체크
    visit[0][0][0] = 1;
    while (!q.empty()) {
        int ly = q.front().y, lx = q.front().x, dir = q.front().dir, t = q.front().t;
        q.pop();
        // R의 좌표는 현재 L의 좌표와 dir로 정해짐
        int ry = ly + dy[dir], rx = lx + dx[dir];
        if ((ly == n - 1 && lx == n - 1) || (ry == n - 1 && rx == n - 1)) return t;
        // 상하좌우
        for (int i = 0;i < 4;++i) {
            int nly = ly + dy[i], nlx = lx + dx[i];
            int nry = ry + dy[i], nrx = rx + dx[i];
            if (!chk(nly, nlx, nry, nrx)) continue;
            if (board[nly][nlx] || board[nry][nrx]) continue;
            if (visit[nly][nlx][dir]) continue;
            visit[nly][nlx][dir] = 1;
            q.push(Point(nly, nlx, dir, t + 1));
        }
        // L을 기준으로 시계/반시계 방향으로 회전
        for (int i = 1;i < 4;i += 2) {
            int ndir = (dir + i) % 4;
            int nry = ly + dy[ndir], nrx = lx + dx[ndir];
            int cy, cx; // 회전 여부를 확인하는 용도
            if (i == 1) {
                // 시계 방향
                // L + {(1,1), (1,-1), (-1,-1), (-1,1)}
                cy = ly + rty[ndir];
                cx = lx + rtx[ndir];
            }
            else {
                // 반시계 방향
                // L + {(-1,1), (1,1), (1,-1), (-1,-1)}
                cy = ly + rty[dir];
                cx = lx + rtx[dir];
            }
            if (!chk(nry, nrx, cy, cx)) continue;
            if (board[nry][nrx] || board[cy][cx]) continue; // 회전 여부
            if (visit[ly][lx][ndir]) continue;  // 방문 여부
            visit[ly][lx][ndir] = 1;
            // L을 기준으로 하기 때문에 ly, lx 를 q에 삽입
            q.push(Point(ly, lx, ndir, t + 1));
        }
        // R을 기준으로 시계/반시계 방향으로 회전
        // R 의 경우 dir + 2 한 상태로 하면 됨
        // 나머진 L 과 동일
        dir = (dir + 2) % 4;
        for (int i = 1;i < 4;i += 2) {
            int ndir = (dir + i) % 4;
            int nly = ry + dy[ndir], nlx = rx + dx[ndir];
            int cy, cx;
            if (i == 1) {
                cy = ry + rty[ndir];
                cx = rx + rtx[ndir];
            }
            else {
                cy = ry + rty[dir];
                cx = rx + rtx[dir];
            }
            if (!chk(nly, nlx, cy, cx)) continue;
            if (board[nly][nlx] || board[cy][cx]) continue;
            // dir에 + 2를 했으므로 다시 돌림
            // 왜냐면 L을 기준으로 풀고 있으니까
            ndir = (ndir + 2) % 4;
            if (visit[nly][nlx][ndir]) continue;
            visit[nly][nlx][ndir] = 1;
            q.push(Point(nly, nlx, ndir, t + 1));
        }
    }
}