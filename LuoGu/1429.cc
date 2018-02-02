/*
 *  luogu1429
 *
 *  分治，先按 x 轴排序，每次取两个子区间的最小距离记为 d 。
 *  然后我们可以发现离中间点 x 方向距离超过 d 的点就不用考虑了。
 *  而对于每个在其中的点，与它距离不超过 d 的在对面的点不会很多，
 *  这些点都会在长为 d ，宽为 2d 的一个矩形中，超过了这个矩形的
 *  点与我们选的点的距离也会超过 d 。而它们互相之间的距离已经不
 *  能小于 d ，所以这些点不会超过 6 个。所以对于一边的每一个点，
 *  它的待定点对都是 O(1) 的（但是不是 1 ）。总复杂度 O(n log n) 。
 *  实现的时候，把与中间点 x 方向距离不超过 d 的点放在一起按 y 轴排序，
 *  然后暴力判断。
 * */
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <iostream>

const size_t Size = 2e5 + 5;
const int Inf = -1u >> 1;

int n;

struct Data {double x, y;} d[Size];

bool operator<(const Data &a, const Data &b) {
    return a.x == b.x? a.y < b.y : a.x < b.x;
}

inline double hypot(const Data &a, const Data &b) {
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

bool cmpY(const int &a, const int &b) {
    return d[a].y < d[b].y;
}

double partSolve(int l, int r) {
    if(l == r) return Inf;
    else if(l + 1 == r) return hypot(d[l], d[r]);
    int mid = (l + r) >> 1;
    double res = std::min(partSolve(l, mid), partSolve(mid + 1, r));

    static int tmp[Size], cnt;

    cnt = 0;

    for(int i = l; i <= r; ++i)
        if(std::fabs(d[mid].x - d[i].x) < res) tmp[++cnt] = i;

    std::sort(tmp + 1, tmp + 1 + cnt, cmpY);

    for(int i = 1; i <= cnt; ++i)
        for(int j = i + 1; hypot(d[tmp[i]], d[tmp[j]]) < res && j <= cnt; ++j)
            res = hypot(d[tmp[i]], d[tmp[j]]);

    return res;
}

int main() {
    std::scanf("%d", &n);

    for(int i = 1; i <= n; ++i)
        std::scanf("%lf%lf", &d[i].x, &d[i].y);

    std::sort(d + 1, d + 1 + n);

    std::printf("%.4lf", partSolve(1, n));

    return 0;
}
