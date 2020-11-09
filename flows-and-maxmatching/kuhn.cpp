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

int kuhn(int n) {
	memset(match, -1, sizeof match);
	int ans = 0;

	for (int i = 0; i < n; ++i) {
		memset(vis, false, sizeof vis);
		if (dfs(i)) ans++;
	}

	return ans;
}
