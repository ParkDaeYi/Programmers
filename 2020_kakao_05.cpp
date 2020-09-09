#include <string>
#include <vector>
using namespace std;

int N;
bool map[101][101][2];

bool chk(int y, int x) {
	return y >= 0 && x >= 0 && y <= N && x <= N;
}

bool ca0(int y, int x) {
	if (!y) return 1;
	if (chk(y - 1, x) && map[y - 1][x][0]) return 1;
	if (map[y][x][1] || map[y][x - 1][1]) return 1;
	return 0;
}

bool ca1(int y,int x) {
	if ((chk(y, x - 1) && map[y][x - 1][1]) && (chk(y, x + 1) && map[y][x + 1][1])) return 1;
	if (map[y - 1][x][0] || map[y - 1][x + 1][0]) return 1;
	return 0;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
	N = n;
	for (vector<int> v : build_frame) {
		int x = v[0], y = v[1];
		if (v[2]) {
			if (v[3]) {
				if (ca1(y, x)) map[y][x][1] = 1;
			}
			else {
				map[y][x][1] = 0;
				if ((map[y][x - 1][1] && !ca1(y, x - 1)) || (map[y][x + 1][1] && !ca1(y, x + 1))) {
					map[y][x][1] = 1;
					continue;
				}
				if ((map[y][x][0] && !ca0(y, x)) || (map[y][x + 1][0] && !ca0(y, x + 1))) {
					map[y][x][1] = 1;
					continue;
				}
			}
		}
		else {
			if (v[3]) {
				if (ca0(y, x)) map[y][x][0] = 1;
			}
			else {
				map[y][x][0] = 0;
				if (map[y + 1][x][0] && !ca0(y + 1, x)) {
					map[y][x][0] = 1;
					continue;
				}
				if ((map[y + 1][x][1] && !ca1(y + 1, x)) || (map[y + 1][x - 1][1] && !ca1(y + 1, x - 1))) {
					map[y][x][0] = 1;
					continue;
				}
			}
		}
	}
	vector<vector<int>> answer;
	for (int i = 0;i <= n;++i) {
		for (int j = 0;j <= n;++j) {
			if (map[j][i][0]) answer.push_back({ i,j,0 });
			if (map[j][i][1]) answer.push_back({ i,j,1 });
		}
	}
	return answer;
}