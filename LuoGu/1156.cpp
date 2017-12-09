#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const size_t Size = 100 + 5;

int d, g;

struct Data {int t, f, h;} r[Size];

bool operator<(const Data &a, const Data &b) {
    return a.t < b.t;
}

int f[Size];

int main() {
    scanf("%d%d", &d, &g);
    for(int i = 1; i <= g; ++i)
        scanf("%d%d%d", &r[i].t, &r[i].f, &r[i].h);

    std::sort(r + 1, r + 1 + g);

    f[0] = 10;

    for(int i = 1; i <= g; ++i)
        for(int j = d; j >= 0; --j) if(f[j] >= r[i].t) {
            if(j + r[i].h >= d) {
                printf("%d\n", r[i].t);
                return 0;
            }
            f[j + r[i].h] = std::max(f[j + r[i].h], f[j]);
            f[j] += r[i].f;
        }

    printf("%d\n", f[0]);

    return 0;
}
