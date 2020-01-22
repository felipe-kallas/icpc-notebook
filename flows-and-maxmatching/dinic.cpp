// Dinic

// Complexity: O (V ^ 2 * E)
//
// Special Cases:
// Unit Capacities: O (min (V ^ 2/3, E ^ 1/2) * E)
// Bipartite Matching: O (sqrt (V) * E)
const int MAXV = 512;

struct Edge {
	int to, cap;
	Edge(int a, int b) { to = a; cap = b; }
};

vector<int> adj[MAXV];
vector<Edge> edges;
int ptr[MAXV], dinic_dist[MAXV];

inline void addEdge(int u, int v, int cap) {
	adj[u].push_back(edges.size());
	edges.push_back(Edge(v, cap));
	adj[v].push_back(edges.size());
	edges.push_back(Edge(u, 0));
}

bool dinic_bfs(int _s, int _t) {
	memset(dinic_dist, -1, sizeof dinic_dist);
	dinic_dist[_s] = 0;
	queue<int> q;
	q.push(_s);

	while (!q.empty() && dinic_dist[_t] == -1) {
		int v = q.front();
		q.pop();
		for (int a = 0; a < adj[v].size(); ++a) {
			int ind = adj[v][a];
			int nxt = edges[ind].to;
			if (dinic_dist[nxt] == -1 && edges[ind].cap) {
				dinic_dist[nxt] = dinic_dist[v] + 1;
				q.push(nxt);
			}
		}
	}

	return dinic_dist[_t] != -1;
}

int dinic_dfs(int v, int _t, int flow) {
	if (v == _t) return flow;
	for (int &a = ptr[v]; a < (int) adj[v].size(); ++a) {
		int ind = adj[v][a];
		int nxt = edges[ind].to;
		if (dinic_dist[nxt] == dinic_dist[v] + 1 && edges[ind].cap) {
			int got = dinic_dfs(nxt, _t, min(flow, edges[ind].cap));
			if (got) {
				edges[ind].cap -= got;
				edges[ind ^ 1].cap += got;
				return got;
			}
		}
	}

	return 0;
}

int dinic(int _s, int _t) {
	int ret = 0, got;
	while (dinic_bfs(_s, _t)) {
		memset(ptr, 0, sizeof ptr);
		while ((got = dinic_dfs(_s, _t, 0x3F3F3F3F))) ret += got;
	}

	return ret;
}

inline void dinic_clear() {
	for (int a = 0; a < MAXV; ++a) adj[a].clear();
	edges.clear();
}