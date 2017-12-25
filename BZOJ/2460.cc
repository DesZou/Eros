/*
 * bzoj2460
 *
 * 线性基裸题，题中的异或值不为零的条件就是让我们构造一组线性基。
 * 同时为了满足权值最大的条件，我们要先按权值从大到小排序，保证
 * 加到线性基里的矿石权值尽可能的大。
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

const size_t Size = 1000 + 5;

int n;

long long lb[Size];

struct Mineral {long long num, magic;} c[Size];

bool operator<(const Mineral &a, const Mineral &b) {
    return a.magic > b.magic;
}

int main(void) {
    std::scanf("%d", &n);

    for(int i = 1; i <= n; ++i) {
        std::scanf("%lld%lld",
                &c[i].num, &c[i].magic);
    }

    std::sort(c + 1, c + 1 + n);

    long long ans = 0;

    for(int i = 1; i <= n; ++i)
        for(int j = 60; j >= 0; --j) if((c[i].num >> j) & 1) {
            if(!lb[j]) {
                lb[j] = c[i].num, ans += c[i].magic; break;}
            c[i].num ^= lb[j];
        }

    printf("%lld\n", ans);

    return 0;
}
