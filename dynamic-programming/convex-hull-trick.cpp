const long long isQuery= -(1LL << 62);

struct Line {
	long long m, b; int id;
	Line (long long _m, long long _b, int _id) : m(_m), b(_b), id(_id) {}
	mutable multiset<Line>::iterator it, e;
	const Line* succ () const {
		return next (it) == e ? 0 : & * next(it);
	}
	bool operator< (const Line & rhs) const {
		if (rhs.b != isQuery) return m < rhs.m;
		const Line* s = succ();
		if (!s) return 0;
		long long x = rhs.m;
		return b - s -> b < (s -> m - m) * x;
		// se der overflow, substitua a linha de cima por
		// return b-s->b<double(s->m-m)*double(x);
	}
};

struct DynamicHull : public multiset <Line> {
	bool bad (iterator y) {
		auto z = next (y);
		if (y == begin ()) {
			if (z == end()) return 0;
			return y -> m == z -> m && y -> b <= z -> b;
		}
		auto x = prev (y);
		if (z == end ()) return y -> m == x -> m && y -> b <= x -> b;
		return 1.0L * (x -> b - y -> b) * (z -> m - y -> m) >= 1.0L * (y -> b - z -> b) * (y -> m - x -> m);
	}
	void insertLine (long long m, long long b, int id) {
		auto y = insert ( {m, b, id} );
		y -> it = y;
		y -> e = end ();
		if (bad (y)) { erase (y); return; }
		while ( next (y) != end () && bad (next (y)) ) erase (next (y));
		while ( y != begin () && bad (prev (y)) ) erase (prev (y));
	}
	pair <long long, int> getMax (long long x) {
		auto l = *lower_bound( {x, isQuery, 0} );
		return { l.m * x + l.b, l.id };
	}
};

