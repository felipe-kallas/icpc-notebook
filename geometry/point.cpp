#include <bits/stdc++.h>
using namespace std;

template <typename M>
struct Point {
	M x, y;
	int id;
	
	Point () {}
	Point (M _x, M _y) {
		x = _x; y = _y;
	}
 
	Point operator+ (const Point & p) const { return Point (x + p.x, y + p.y); }
	Point operator- (const Point & p) const { return Point (x - p.x, y - p.y); }
	
	M operator^ (const Point & p) const { return x * p.y - y * p.x; }
	M operator* (const Point & p) const { return x * p.x + y * p.y; }
	Point operator* (const double & d) const { return Point(x * d, y * d); }
	M operator~ () const { return x * x + y * y; }
 
	bool operator< (const Point & p) const { return make_pair (y, x) < make_pair (p.y, p.x); }
	bool operator== (const Point & p) const { return make_pair (y, x) == make_pair (p.y, p.x); }
 
	double distanceToSegment2 (const Point s1, const Point s2) const {
		Point c = *this;
		if ( ((s2 - s1) * (c - s1)) <= 0.0 || ((s1 - s2) * (c - s2)) <= 0.0) {
			return min(~(s1 - c), ~(s2 - c));
		} else {
			long long area = (s2 - s1) ^ (c - s1);
			return (area * area) / (~(s2 - s1));
		}
	}
	
	friend istream & operator >> (istream & in, Point & p) {
		in >> p.x >> p.y;
		return in;
	} 
	
	friend ostream & operator << (ostream & out, Point & p) {
		out << "(" << p.x << " " << p.y << ")"; 
		return out;
	}
	
};
 
const int MAXN = 212345;
 
int n;
Point<long long> points[MAXN];
 
int m;
Point<long long> ch[MAXN];
 
bool cmp (const Point<long long> p, const Point<long long> q) {
	long long cross = (p - points[0]) ^ (q - points[0]);
	if (cross != 0) return cross > 0;
	return ~(p - points[0]) < ~(q - points[0]);
}
 
void convexHull () {
	for (int i = 1; i < n; ++i) {
		if (points[i] < points[0])
			swap (points[i], points[0]);
	}
 
	sort (points + 1, points + n, cmp);
 
	ch[m++] = points[0];
	ch[m++] = points[1];
 
	for (int i = 2; i < n; ++i) {
		while (m >= 2 && ( (ch[m - 1] - ch[m - 2]) ^ (points[i] - ch[m - 1]) ) <= 0)
			--m;
		ch[m++] = points[i];
	}
}
 
int main () {
 
	cin >> n;
 
	for (int i = 0; i < n; ++i) {
		//scanf ("%lld %lld", &points[i].x, &points[i].y);
		cin >> points[i];
		points[i].id = i + 1;
	}
 
	convexHull ();
 
	cout << m << endl;
	for (int i = 0; i < m; ++i) {
		printf ("%d%c", ch[i].id, " \n"[i + 1 == m]);
		//cout << ch[i] << endl;
	}
 
	double per = 0;
	long long area = 0;
	for (int i = 1; i <= m; ++i)
		per += sqrt (~(ch[i % m] - ch[i - 1]) );
 
	for (int i = 1; i < m - 1; ++i)
		area += (ch[i] - ch[0]) ^ (ch[i + 1] - ch[0]);
 
	cout << fixed << setprecision (12) << per << endl;
	cout << area / 2LL;
	if (area & 1LL)
		cout << ".5";
	cout << endl;
 
	return 0;
}

