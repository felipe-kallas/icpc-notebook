#include <bits/stdc++.h>
using namespace std;

// Restrictions: A[i] * X <= B[i]
// Answer: X (Maximizing function C * X)

const long double EPS = 1e-9;

struct LPSolver {
	int m, n;
	vector <int> B, N;
	vector <vector <long double> > D;

	LPSolver(const vector <vector <long double> > & A, const vector <long double> & b, const vector <long double> & c) :
		m(b.size()), n(c.size()), N(n + 1), B(m), D(m + 2, vector <long double> (n + 2)) {
		for (int i = 0; i < m; ++i) for (int j = 0; j < n; j++) D[i][j] = A[i][j];
		for (int i = 0; i < m; ++i) { B[i] = n + i; D[i][n] = -1; D[i][n + 1] = b[i]; }
		for (int j = 0; j < n; ++j) { N[j] = j; D[m][j] = -c[j]; }
		N[n] = -1; D[m + 1][n] = 1;
	}

	void Pivot(int r, int s) {
		double inv = 1.0 / D[r][s];
		for (int i = 0; i < m + 2; ++i) if (i != r)
			for (int j = 0; j < n + 2; ++j) if (j != s)
				D[i][j] -= D[r][j] * D[i][s] * inv;
		for (int j = 0; j < n + 2; ++j) if (j != s) D[r][j] *= inv;
		for (int i = 0; i < m + 2; ++i) if (i != r) D[i][s] *= -inv;
		D[r][s] = inv;
		swap(B[r], N[s]);
	}

	bool Simplex(int phase) {
		int x = phase == 1 ? m + 1 : m;
		while (true) {
			int s = -1;
			for (int j = 0; j <= n; ++j) {
				if (phase == 2 && N[j] == -1) continue;
				if (s == -1 || D[x][j] < D[x][s] || D[x][j] == D[x][s] && N[j] < N[s]) s = j;
			}
			if (D[x][s] > -EPS) return true;
			int r = -1;
			for (int i = 0; i < m; ++i) {
				if (D[i][s] < EPS) continue;
				if (r == -1 || D[i][n + 1] / D[i][s] < D[r][n + 1] / D[r][s] ||
					(D[i][n + 1] / D[i][s]) == (D[r][n + 1] / D[r][s]) && B[i] < B[r]) r = i;
			}
			if (r == -1) return false;
			Pivot(r, s);
		}
	}

	long double Solve(vector <long double> & x) {
		int r = 0;
		for (int i = 1; i < m; i++) if (D[i][n + 1] < D[r][n + 1]) r = i;
		if (D[r][n + 1] < -EPS) {
			Pivot(r, n);
			if (!Simplex(1) || D[m + 1][n + 1] < -EPS) return -numeric_limits<long double>::infinity();
			for (int i = 0; i < m; i++) if (B[i] == -1) {
				int s = -1;
				for (int j = 0; j <= n; j++)
					if (s == -1 || D[i][j] < D[i][s] || D[i][j] == D[i][s] && N[j] < N[s]) s = j;
				Pivot(i, s);
			}
		}
		if (!Simplex(2)) return numeric_limits<long double>::infinity();
		x = vector <long double>(n);
		for (int i = 0; i < m; i++) if (B[i] < n) x[B[i]] = D[i][n + 1];
		return D[m][n + 1];
	}
};

int main() {

	const int m = 4;
	const int n = 3;
	long double _A[m][n] = {
		{ 6, -1, 0 },
		{ -1, -5, 0 },
		{ 1, 5, 1 },
		{ -1, -5, -1 }
	};
	long double _b[m] = { 10, -4, 5, -5 };
	long double _c[n] = { 1, -1, 0 };

	vector <vector <long double> > A(m);
	vector <long double> b(_b, _b + m);
	vector <long double> c(_c, _c + n);
	for (int i = 0; i < m; i++) A[i] = vector <long double>(_A[i], _A[i] + n);

	LPSolver solver(A, b, c);
	vector <long double> x;
	long double value = solver.Solve(x);

	cerr << "VALUE: " << value << endl; // VALUE: 1.29032
	cerr << "SOLUTION:"; // SOLUTION: 1.74194 0.451613 1
	for (size_t i = 0; i < x.size(); i++) cerr << " " << x[i];
	cerr << endl;
	
	return 0;
}
