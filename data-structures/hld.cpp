#include <bits/stdc++.h>
using namespace std;

const int MAXN = 101010;
const int LOGN = 20;

class segtree {
	
	public:
  
	struct node {
		int a = 0;
		int add = 0;

		template <typename M>
		void apply(int l, int r, const M v) {
			a += v;
			add += v;
		}
	};
  
	node unite(const node &a, const node &b) const {
		node res;
		res.a = a.a + b.a;
		return res;
	}
  
	inline void push(int x, int l, int r) {
		int mid = (l + r) >> 1;
		int z = x + ((mid - l + 1) << 1);
		// push from x into (x + 1) and z

		if (tree[x].add != 0) {
			tree[x + 1].apply(l, mid, tree[x].add);
			tree[z].apply(mid + 1, r, tree[x].add);
			tree[x].add = 0;
		}

	}
  
	//não mexer
	inline void pull(int x, int z) {
		tree[x] = unite(tree[x + 1], tree[z]);
	}

	int n;
	vector<node> tree;
	
	void build(int x, int l, int r) {
		if (l == r) {
		  return;
		}
		int y = (l + r) >> 1;
		int z = x + ((y - l + 1) << 1);
		build(x + 1, l, y);
		build(z, y + 1, r);
		pull(x, z);
	}
  
	template <typename M>
	void build(int x, int l, int r, const vector<M> &v) {
		if (l == r) {
			tree[x].apply(l, r, v[l]);
			return;
		}
		int y = (l + r) >> 1;
		int z = x + ((y - l + 1) << 1);
		build(x + 1, l, y, v);
		build(z, y + 1, r, v);
		pull(x, z);
	}
  
	node get(int x, int l, int r, int ll, int rr) {
		if (ll <= l && r <= rr) {
			return tree[x];
		}
		int y = (l + r) >> 1;
		int z = x + ((y - l + 1) << 1);
		push(x, l, r);
		node res{};
		if (rr <= y) {
			res = get(x + 1, l, y, ll, rr);
		} else {
			if (ll > y) {
				res = get(z, y + 1, r, ll, rr);
			} else {
				res = unite(get(x + 1, l, y, ll, rr), get(z, y + 1, r, ll, rr));
			}
		}
		pull(x, z);
		return res;
	}
  
	template <typename M>
	void modify(int x, int l, int r, int ll, int rr, const M v) {
		if (ll <= l && r <= rr) {
			tree[x].apply(l, r, v);
			return;
		}
		int y = (l + r) >> 1;
		int z = x + ((y - l + 1) << 1);
		push(x, l, r);
		if (ll <= y) modify(x + 1, l, y, ll, rr, v);
		if (rr > y) modify(z, y + 1, r, ll, rr, v);
		pull(x, z);
	}  
  	
	segtree(){}
	
	segtree(int _n) : n(_n) {
		assert(n > 0);
		tree.resize(2 * n - 1);
		build(0, 0, n - 1);
	}
  
	template <typename M>
	segtree(const vector<M> &v) {
		n = v.size();
		assert(n > 0);
		tree.resize(2 * n - 1);
		build(0, 0, n - 1, v);
	}
  
	node get(int ll, int rr) {
		assert(0 <= ll && ll <= rr && rr <= n - 1);
		return get(0, 0, n - 1, ll, rr);
	}
  
	node get(int p) {
		assert(0 <= p && p <= n - 1);
		return get(0, 0, n - 1, p, p);
	}
  
	template <typename M>
	void modify(int ll, int rr, const M v) {
		assert(0 <= ll && ll <= rr && rr <= n - 1);
		modify(0, 0, n - 1, ll, rr, v);
	}
  
};

int n, t = 0;
segtree st;
int sz[MAXN], par[MAXN][LOGN], h[MAXN];
int in[MAXN], out[MAXN], nxt[MAXN], rin[MAXN];
vector<int> g[MAXN];

void dfs_sz(int v){
	
	sz[v] = 1;
	
	for(auto& u : g[v]){
		if(u == par[v][0]) continue;
		par[u][0] = v;
		h[u] = h[v] + 1;
		dfs_sz(u);
		sz[v] += sz[u];
		if(sz[u] > sz[g[v][0]] || g[v][0] == par[v][0])
			swap(g[v][0], u);
	}
	return;
}

void dfs_hld(int v){
	
	in[v] = t++;
	rin[in[v]] = v;
	
	for(auto u : g[v]){
		if(u == par[v][0]) continue;
		nxt[u] = (u == g[v][0] ? nxt[v] : u);
		dfs_hld(u);
	}
	
	out[v] = t;
	
	return;
}

int getLCA(int u, int v){
	
	if(h[u] > h[v]) swap(u,v);
	int d = h[v] - h[u];
	
	for(int i = 0 ; i < LOGN ; i ++)
		if(d & (1<<i)) v = par[v][i];
	
	if(u == v) return v;
	
	for(int i = LOGN - 1 ; i >= 0 ; i --){
		if(par[u][i] != par[v][i]){
			u = par[u][i];
			v = par[v][i];
		}
	}
	
	return par[v][0];
}

int queryPath(int v, int u){
	
	if(h[v] < h[u]) swap(u,v);
	
	int val = 0;
	
	while(nxt[v] != nxt[u]){
		val += st.get(in[nxt[v]], in[v]).a;
		v = par[nxt[v]][0];
	}
	
	if(u != v)
		val += st.get(in[u] + 1, in[v]).a;
	
	return val;
}

void updatePath(int v, int u){
	
	if(h[v] < h[u]) swap(u,v);
	
	while(nxt[v] != nxt[u]){
		st.modify(in[nxt[v]], in[v], 1);
		v = par[nxt[v]][0];
	}
	
	if(u != v)
		st.modify(in[u] + 1, in[v], 1);
	
	return;
}

int main(){
	
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	
	int q;
	cin >> n >> q;
	
	for(int i = 0 ; i < n - 1 ; i ++){
		int a, b;
		cin >> a >> b;
		--a; --b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	
	dfs_sz(0);
	dfs_hld(0);
	
	for(int j = 1 ; j < LOGN ; j ++)
		for(int i = 0 ; i < n ; i ++)
			par[i][j] = par[par[i][j - 1]][j - 1];
	
	st = segtree(t + 10);
	
	while(q--){
		
		char type;
		cin >> type;
		
		if(type == 'P'){ // CHANGE
			
			int u, v;
			cin >> u >> v;
			--u; --v;
			
			int w = getLCA(u,v);
			
			updatePath(u,w);
			updatePath(v,w);
			
		} else { // QUERY
			
			int u, v;
			cin >> u >> v;
			--u; --v;
			
			int w = getLCA(u,v);
			int q1 = queryPath(u,w), q2 = queryPath(v,w);
			int ans = q1 + q2;
			
			cout << ans << "\n";
			
		}
	}
	
	return 0;
}