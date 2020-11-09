// Union Find / Disjoint Set Union (DSU)
// Time Complexity: O(log* n)
// Memo Complexity: O(n)

const int MAXN = 112345;

int cnt;	// Amount of connected components
int id[MAXN], sz[MAXN];

void setup (int n) {
	cnt = n;
	for (int i = 0; i < n; ++i) {
		id[i] = i;
		sz[i] = 1;
	}
}

// Returns id of set that contains p
int find (int p) {
	int root = p;
	while (root != id[root])
		root = id[root];
	
	while (p != root) {
		int newp = id[p];
		id[p] = root;
		p = newp;
	}

	return root;
}

// Merges sets containing x and y
void merge (int x, int y) {
	int i = find(x);
	int j = find(y);
	if (i == j) return;

	if (sz[i] > sz[j])
		swap(i, j);  
		
	id[i] = j;
	sz[j] += sz[i];
	--cnt;
}
