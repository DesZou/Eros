#include <bits/stdc++.h>

bool edge[105][105];

std::string filename("graph");

int main(int argc, char *argv[]) {
	assert(argc >= 4);
	
	filename += argv[1];
	freopen((filename + ".in").c_str(), "w", stdout);
	
	int id; sscanf(argv[1], "%d", &id);
	
	srand(time(0));
	
	int n, m, e, q;
	
	sscanf(argv[2], "%d", &n);
	sscanf(argv[3], "%d", &m);
	if (m == -1) m = n * (n - 1) / 2;
	if (id >= 5 && id <= 14) sscanf(argv[5], "%d", &e);
	else {
		do {
			e = rand() % m + 1;
		} while (e < (m >> 1));
	}
	sscanf(argv[4], "%d", &q);
	
	printf("%d %d %d\n", n, m, e);
	if (m == n * (n - 1) / 2) {
		for (int i = 1; i <= n; ++i)
			for (int j = i + 1; j <= n; ++j)
				printf("%d %d %d\n", i, j, rand() % 1000 + 1);
	}
	else {
		for (int i = 1; i <= m; ++i) {
			static int u, v, w;
			
			do {
				u = rand() % n + 1;
				v = rand() % n + 1;
			} while (u == v || edge[u][v]);
			
			edge[u][v] = edge[v][u] = 1;
			w = rand() % 1000 + 1;
			
			printf("%d %d %d\n", u, v, w);
		}
	}
	
	printf("%d\n", q);
	
	while (q--) {
		static int u, v;
		
		do {
			u = rand() % n + 1;
			v = rand() % n + 1;
		} while (u == v);
		
		printf("%d %d\n", u, v);
	}
	
	return 0;
}
