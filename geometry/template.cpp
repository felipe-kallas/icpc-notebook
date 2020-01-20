#include <bits/stdc++.h>
using namespace std;

struct Point {
	double x, y;

	Point () {}
	Point (double _x, double _y) {
		x = _x; y = _y;
	}

	Point operator+ (const Point & p) const { return Point (x + p.x, y + p.y); }
	Point operator- (const Point & p) const { return Point (x - p.x, y - p.y); }
	double operator^ (const Point & p) const { return x * p.y - y * p.x; }
	double operator* (const Point & p) const { return x * p.x + y * p.y; }
	double operator~ () const { return x * x + y * y; }

	double distanceToSegment2 (const Point s1, const Point s2) const {
		Point c = *this;
		if ( 	((s2 - s1) * (c - s1)) <= 0.0 ||
				((s1 - s2) * (c - s2)) <= 0.0) {
			return min(~(s1 - c), ~(s2 - c));
		} else {
			double area = (s2 - s1) ^ (c - s1);
			return (area * area) / (~(s2 - s1));
		}
	}
};

struct Line {
	double a, b, c;

	Line () {}
	Line (double _a, double _b, double _c) {
		a = _a; b = _b; c = _c;
	}

	Line (Point p, Point q) {
		a = p.y - q.y;
		b = q.x - p.x;
		c = p.x * q.y - q.x * p.y;
	}

	bool parallel (const Line & l) { return (a * l.b == l.a * b); }
	Line perpendicular (Point p) { return Line (-b, a, b * p.x - a * p.y); }

	Point intersect (const Line & l) {
		if (this -> parallel (l) ) return Point (-HUGE_VAL, -HUGE_VAL);
		else {
			double det = a * l.b - l.a * b;
			double x = (b * l.c - l.b * c) / det;
			double y = (c * l.a - l.c * a) / det;
			return Point (x, y);
		}
	}

};

struct Circle {
	Point o;
	double r;

	Circle () {}
	Circle (Point _o, double _r) {
		o = _o; r = _r;
	}

	Circle (Point a, Point b, Point c) {
		Line ab = Line (a, b);
		Line bc = Line (b, c);
		Point mAB = Point ((a.x + b.x) * 0.5, (a.y + b.y) * 0.5);
		Point mBC = Point ((b.x + c.x) * 0.5, (b.y + c.y) * 0.5);
		ab = ab.perpendicular (mAB);
		bc = bc.perpendicular (mBC);

		if (ab.parallel (bc)) {
			o = Point (-HUGE_VAL, -HUGE_VAL);
			r = -1.0;
		} else {
			o = ab.intersect (bc);
			r = ~(o - a);
		}

	}

	double getIntersectionArea (Circle c) {
		double d = ~(o - c.o);
		if (d >= r + c.r) return 0.0;
		else if (c.r >= d + r) return pi * r * r;
		else if (r >= d + c.r) return pi * c.r * c.r;
		else {
			// Algum dia eu terimno essa parte
		}
	}

};