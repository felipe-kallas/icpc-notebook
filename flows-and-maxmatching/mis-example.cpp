// Example of MIS
// Problem: SPOJ/DIVREL

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300;

vector<int> g[MAXN];	// Vertices from A numbered 0 to n - 1
int match[MAXN];		// Vertices from B numbered 0 to m - 1
bool vis[MAXN];

bool dfs(int u) {
	if (vis[u]) return false;
	vis[u] = true;

	for (int i = 0; i < g[u].size(); ++i) {
		int v = g[u][i];
		if (match[v] == -1) {
			match[v] = u;
			return true;
		}
	}

	for (int i = 0; i < g[u].size(); ++i) {
		int v = g[u][i];
		if (dfs(match[v])) {
			match[v] = u;
			return true;
		}
	}

	return false;
}

vector <int> start;
int kuhn(int n) {
	memset(match, -1, sizeof match);
	int ans = 0;

	for (int i = 0; i < n; ++i) {
		memset(vis, false, sizeof vis);
		if (dfs(i))
			ans++;
		else
			start.push_back (i);
	}

	return ans;
}

int v[MAXN];
set<int> elem;

bool visr[MAXN];

set <int> fin;

void re (int x) {
	if (vis[x]) return;
	vis[x] = true;

	for (int i = 0; i < g[x].size(); ++i) {
		int y = g[x][i];

		visr[y] = true;
		if (match[y] == -1) continue;
		re (match[y]);
	}
}

int main () {

	int n;
	cin >> n;

	for (int i = 0; i < n; ++i) {
		scanf("%d", v + i);
		if (elem.count (v[i])) {
			--i; --n;
		} else
			elem.insert (v[i]);
	}

	sort (v, v + n);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i == j) continue;
			if (v[i] % v[j] == 0) {
				g[i].push_back(j);
			}
		}
	}

	int ans = n - kuhn (n);

	memset (vis, false, sizeof vis);
	for (int i = 0; i < start.size(); ++i)
		re (start[i]);

	cout << ans << endl;

	for (int i = 0; i < n; ++i)
		if (!vis[i]) fin.insert (i);

	for (int i = 0; i < n; ++i)
		if (visr[i]) fin.insert (i);

	for (int i = 0; i < n; ++i)
		if (!fin.count (i)) printf ("%d ", v[i]);

	cout << endl;

	return 0;
}