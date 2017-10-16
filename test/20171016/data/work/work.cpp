#include <bits/stdc++.h>

int n, m;

struct Cus {
	int s, t;
	
	Cus() {}
	Cus(int s, int t): s(s), t(t) {}
	
	bool operator < (const Cus &rhs) const {
		return s < rhs.s;
	}
	
	void scan() {
		scanf("%d%d", &s, &t);
	}
} cus[300005];

namespace Heap {
	int pool[300005], tot;
	
	void init() {
		tot = 0;
	}
	
	void push(int x) {
		pool[++tot] = x;
		std::push_heap(pool + 1, pool + tot + 1, std::greater<int>());
	}
	
	void pop() {
		std::pop_heap(pool + 1, pool + tot + 1, std::greater<int>());
		--tot;
	}
	
	int top() {
		return pool[1];
	}
	
	bool empty() {
		return tot == 0;
	}
}

std::string filename("work");

int main(int argc, char *argv[]) {
	assert(argc >= 1);
	filename += argv[1];
	freopen((filename + ".in").c_str(), "r", stdin);
	freopen((filename + ".out").c_str(), "w", stdout);
	
	Heap::init();
	
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		cus[i].scan();
	
	std::sort(cus + 1, cus + n + 1);
	
	int ans = 0;
	
	for (int i = 1; i <= n; ++i) {
		while (!Heap::empty() && cus[i].s - Heap::top() > m) Heap::pop();
		if (!Heap::empty() && cus[i].s >= Heap::top()) {
			Heap::pop();
			++ans;
		}
		Heap::push(cus[i].s + cus[i].t);
	}
	
	printf("%d\n", ans);
	
	return 0;
}
