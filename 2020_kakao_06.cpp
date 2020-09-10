#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(int n, vector<int> weak, vector<int> dist) {
    // next_permutation 을 쓰기 위해 정렬
    // ==> 가능한 모든 dist의 순서에서 거리를 측정해야 하기 때문
	sort(dist.begin(), dist.end());
	int w = weak.size(), answer = 1e9, d = dist.size();
	for (int i = 0; i < w; ++i) {
		do {
			int idx = 0, j = 0;
			for (; j < d; ++j) {
				int len = weak[idx] + dist[j];
                // 현재 weak에서 한 사람이 파악할 수 있는 갯수 측정
                // ==> 지금 weak는 무조건 파악할 수 있다는 뜻(weak에서 시작하니까)
				while (idx < w && len >= weak[idx])
					++idx;
				if (idx == w) break;
			}
			if (idx == w) answer = min(answer, j);
		} while (next_permutation(dist.begin(), dist.end()));
        // 모든 경우를 보기 위해
        // weak 를 한 칸씩 당김
		int tmp = weak[0] + n;
		for (int i = 1; i < w; ++i) weak[i - 1] = weak[i];
		weak[w - 1] = tmp;
	}
	return answer == 1e9 ? -1 : answer + 1;
}