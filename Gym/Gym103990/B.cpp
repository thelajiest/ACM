#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
template <class Info, class Tag>
struct LazySegmentTree {
	/*
	    Info: apply,operator +
	    Tag: apply
	    all operations obey [l,r)
	*/
	const int n;
	vector<Info> info;
	vector<Tag> tag;
	LazySegmentTree(int n) : n(n), info(4 << __lg(n)), tag(4 << __lg(n)) {}
	LazySegmentTree(vector<Info> init) : LazySegmentTree(init.size()) {
		function<void(int, int, int)> build = [&](int p, int l, int r) {
			if (r - l == 1) {
				info[p] = init[l];
				return;
			}
			int m = (l + r) / 2;
			build(2 * p, l, m);
			build(2 * p + 1, m, r);
			pull(p);
		};
		build(1, 0, n);
	}
	void pull(int p) { info[p] = info[2 * p] + info[2 * p + 1]; }
	void apply(int p, const Tag &v) {
		info[p].apply(v);
		tag[p].apply(v);
	}
	void push(int p) {
		apply(2 * p, tag[p]);
		apply(2 * p + 1, tag[p]);
		tag[p] = Tag();
	}
	void modify(int p, int l, int r, int x, const Info &v) {
		if (r - l == 1) {
			info[p] = v;
			return;
		}
		int m = (l + r) / 2;
		push(p);
		if (x < m) {
			modify(2 * p, l, m, x, v);
		} else {
			modify(2 * p + 1, m, r, x, v);
		}
		pull(p);
	}
	void modify(int p, const Info &v) { modify(1, 0, n, p, v); }
	Info rangeQuery(int p, int l, int r, int x, int y) {
		if (l >= y || r <= x) {
			return Info();
		}
		if (l >= x && r <= y) {
			return info[p];
		}
		int m = (l + r) / 2;
		push(p);
		return rangeQuery(2 * p, l, m, x, y) +
		       rangeQuery(2 * p + 1, m, r, x, y);
	}
	Info rangeQuery(int l, int r) { return rangeQuery(1, 0, n, l, r); }
	void rangeApply(int p, int l, int r, int x, int y, const Tag &v) {
		if (l >= y || r <= x) {
			return;
		}
		if (l >= x && r <= y) {
			apply(p, v);
			return;
		}
		int m = (l + r) / 2;
		push(p);
		rangeApply(2 * p, l, m, x, y, v);
		rangeApply(2 * p + 1, m, r, x, y, v);
		pull(p);
	}
	void rangeApply(int l, int r, const Tag &v) {
		return rangeApply(1, 0, n, l, r, v);
	}
};

constexpr int danger = -1E9 - 1;
struct Tag {
	i64 inc = 0;
	i64 all = danger;
	void apply(const Tag& a) {
		if (a.all != danger) {all = a.all; inc = a.inc;}
		else {inc += a.inc;}
		return;
	}
};

struct Info {
	i64 sum = 0;
	i64 isum = 0;
	i64 l = -1, r = -1;
	void apply(const Tag& a) {
		if (a.all != danger) {
			sum = 1LL * (r - l + 1) * a.all;
			isum = 1LL * (l + r) * (r - l + 1) / 2;
			isum *= 1LL * a.all;
		}
		sum += 1LL * (r - l + 1) * a.inc;
		isum += 1LL * a.inc * 1LL * (r - l + 1) * (l + r) / 2;

		return ;
	}
};
Info operator+(const Info& a, const Info& b) {
	if (a.l == -1) return b;
	if (b.l == -1) return a;

	Info merge;
	merge.sum = a.sum + b.sum;
	merge.isum = a.isum + b.isum;
	merge.l = a.l;
	merge.r = b.r;
	return merge;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, q;
	cin >> n >> q;
	vector<Info> init(n + 1);

	for (int i = 1; i <= n; i++) {
		cin >> init[i].sum;
		init[i].isum = i * init[i].sum;
		init[i].l = init[i].r = i ;
	}
	LazySegmentTree<Info, Tag> st(init);

	while (q--) {
		int op;
		cin >> op;
		if (op == 1) {
			int l, r, x;
			cin >> l >> r >> x;
			r++;
			st.rangeApply(l, r, Tag{x, danger});
		}
		if (op == 2) {
			int l, r, x;
			cin >> l >> r >> x;
			r++;
			st.rangeApply(l, r, Tag{0, x});
		}
		if (op == 3) {
			int l, r;
			cin >> l >> r;
			r++;
			auto now = st.rangeQuery(l, r);
			i64 isum = now.isum - 1LL * now.sum * (l - 1);
			if (isum == 0 && now.sum == 0) {
				cout << "Yes\n";
				continue;
			}

			if (isum != 0 && now.sum == 0) {
				cout << "No\n";
				continue;
			}

			if (isum % now.sum == 0) {
				int g = isum / now.sum;
				int m = r - l ;
				if (1 <= g && g <= m) cout << "Yes\n";
				else cout << "No\n";
			} else cout << "No\n";
		}
	}
	return 0;
}