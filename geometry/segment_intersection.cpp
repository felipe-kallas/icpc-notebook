#include <bits/stdc++.h>
using namespace std;

const int INF = 112345;

struct Point {
	long long x, y;
	int id;
	
	Point () {}
	Point (long long _x, long long _y) {
		x = _x; y = _y;
	}
 
	Point operator+ (const Point & p) const { return Point (x + p.x, y + p.y); }
	Point operator- (const Point & p) const { return Point (x - p.x, y - p.y); }
	
	long long operator^ (const Point & p) const { return x * p.y - y * p.x; }
	long long operator* (const Point & p) const { return x * p.x + y * p.y; }
	Point operator* (const double & d) const { return Point(x * d, y * d); }
	long long operator~ () const { return x * x + y * y; }
 
	bool operator< (const Point & p) const { return make_pair (x, y) < make_pair (p.x, p.y); }
	bool operator== (const Point & p) const { return make_pair (x, y) == make_pair (p.x, p.y); }
	bool operator!= (const Point & p) const { return make_pair (x, y) != make_pair (p.x, p.y); }
	bool operator<= (const Point & p) const { return make_pair (x, y) <= make_pair (p.x, p.y); }
 
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

bool isInside(Point p, Point p2, Point a, Point b) {
 
	if( ((p2-p)^(a-p)) == 0 && ((p2-p)^(b-p)) == 0 ) {
		if(p <= a && a <= p2 && p <= b && b <= p2) return true;
		else return false;
	} else {
		return false;
	}
 
}

void showAns (Point a, Point b) {
	assert(a < b);
	printf("%lld.000000 %lld.000000\n", a.x, a.y);
	printf("%lld.000000 %lld.000000\n", b.x, b.y);
}

void getSeg(Point p, Point p2, Point q, Point q2) {

	if(q < p) {
		swap(p, q);
		swap(p2, q2);
	}

	if(isInside(p, p2, q, q2)) {
		showAns(q, q2);
		return;
	}
	if(isInside(q, q2, p, p2)) {
		showAns(p, p2);
		return;
	}

	if(p2 == q) {
		printf("%lld.000000 %lld.000000\n", p2.x, p2.y);
	} else {
		showAns(q, p2);
	}

}


bool intersect(Point p, Point p2, Point q, Point q2) {

	Point r = p2 - p;
	Point s = q2 - q;
	long long rxs = r ^ s;
	long long qpxr = (q-p) ^ r;

	if (rxs == 0 && qpxr == 0) {

		if((0 <= (q-p)*r && (q-p)*r <= r*r) || (0 <= (p-q)*s && (p-q)*s <= s*s)) {
			//OVERLAPPING
			getSeg(p, p2, q, q2);
			return true;
		}

		//DISJOINT
		return false;
	}

	if (rxs == 0 && qpxr != 0) {
		//PARALLEL
		return false;
	}

	double t = double((q-p) ^ s) / double(rxs);
	double u = double((q-p) ^ r) / double(rxs);

	if(rxs != 0 && (0 <= t && t <= 1) && (0 <= u && u <= 1)) {
		//NORMAL INTERSECTION
		printf("%.6lf %.6lf\n", p.x + t * r.x, p.y + t * r.y);
		return true;
	}
	//NO INTERSECTION
	return false;

}


int main() {

    Point a, b, c, d;
    cin >> a >> b >> c >> d;
    //cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;

	if(b < a) swap(a, b);
	if(d < c) swap(c, d);
 
	if (a == b && b == c && c == d)
		printf("%lld.000000 %lld.000000\n", a.x, a.y);
 
	if (a == b && c == d && a != c)
		printf("Empty\n");
 
	if (a == b && c != d) {
		if(isInside(c, d, a, a)) printf("%lld.000000 %lld.000000\n", a.x, a.y);
		else printf("Empty\n");
	}
 
	if (c == d && a != b) {
		if(isInside(a, b, c, c)) printf("%lld.000000 %lld.000000\n", c.x, c.y);
		else printf("Empty\n");
	}
 
	if(a != b && c != d)
		if(!intersect(a, b, c, d)) printf("Empty\n");

    return 0;
}
