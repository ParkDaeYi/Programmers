#include <iostream>
#include <string>
#include <vector>
#include <memory.h>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Trie {
private:
	Trie* nxt[26];
	bool term;
	unordered_map<int, int> sz;
public:
	Trie() :term(0) {
		memset(nxt, 0, sizeof(nxt));
	}
	void insert(const char* key, int n) {
		if (*key == '\0') term = 1;
		else {
			int cur = *key - 'a';
			sz[n - 1] += 1;
			if (nxt[cur] == NULL) nxt[cur] = new Trie();
			nxt[cur]->insert(key + 1, n);
		}
	}
	int find(const char* key, int n) {
		if (*key == '\0') return term;
		int ret = 0;
		if (*key == '?') ret += sz[n - 1];
		else {
			int cur = *key - 'a';
			if (!nxt[cur]) return 0;
			ret = nxt[cur]->find(key + 1, n);
		}
		return ret;
	}
};

vector<int> solution(vector<string> words, vector<string> queries) {

	Trie* root_b = new Trie();
	Trie* root_e = new Trie();
	for (string str : words) {
		string tmp = str;
		root_b->insert(&tmp[0], tmp.length());
		reverse(tmp.begin(), tmp.end());
		root_e->insert(&tmp[0], tmp.length());
	}

	vector<int> ret; int cnt = 0;
	for (string str : queries) {
		string tmp = str;
		if (str[0] == '?') {
			reverse(tmp.begin(), tmp.end());
			ret.push_back(root_e->find(&tmp[0], tmp.length()));
		}
		else ret.push_back(root_b->find(&tmp[0], tmp.length()));
	}

	return ret;
}