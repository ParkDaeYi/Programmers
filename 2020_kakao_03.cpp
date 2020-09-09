#include <string>
#include <vector>

using namespace std;

void rotate(vector<vector<int>>& key) {
	vector<vector<int>> tmp = key;
	int n = key.size();
	for (int i = 0;i < n;++i) for (int j = 0;j < n;++j) key[i][j] = tmp[n - j - 1][i];
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
	int n = key.size(), m = lock.size();
	int sz = m + (n - 1) * 2, cnt = 0;
	vector<vector<int>> map(sz, vector<int>(sz, 0));
	int s = n - 1, e = n + m - 1;
	for (int i = s, x = 0;x < m;++i, ++x) for (int j = s, y = 0;y < m;++j, ++y) {
		map[i][j] = lock[x][y];
		if (!lock[x][y]) cnt++;
	}
	for (int i = 0;i < 4;++i) {
		for (int j = 0;j <= sz - n;++j) {
			for (int k = 0;k <= sz - n;++k) {
				int tmp = 0;
				for (int l = 0;l < n;++l) {
					if (l + j < s || l + j >= e) continue;
					for (int c = 0;c < n;++c) {
						if (c + k < s || c + k >= e) continue;
						if (!key[l][c]) continue;
						if (!map[l + j][c + k]) tmp++;
						else tmp--;
					}
				}
				if (tmp == cnt) return 1;
			}
		}
		rotate(key);
	}
	return 0;
}