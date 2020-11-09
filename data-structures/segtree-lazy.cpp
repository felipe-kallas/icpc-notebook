#include <bits/stdc++.h>
using namespace std;

class segtree {
	
	public:
  
	struct node {
		long long a = 0;
		long long add = 0;

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


int main () {
	
	int n, m;
	cin >> n >> m;
	
	segtree st(n);
	
	while(m--) {
		int op;
		cin >> op;
		
		if(op == 1) {
			int l, r;
			long long v;
			cin >> l >> r >> v;
			st.modify(l, r-1, v);
		} else {
			int p;
			cin >> p;
			
			cout << st.get(p).a << endl;
		}
		
	}
	
}
