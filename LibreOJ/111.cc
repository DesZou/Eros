#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <iostream>

const size_t Size = 1e6 + 5;
const size_t Set = 150;

typedef int Array[Size << 1];

template<class T> T min(const T &a, const T &b) {
    return a < b? a : b;
}

template<class T> T max(const T &a, const T &b) {
    return a > b? a : b;
}

template<class T> bool chkmin(T &a, const T &b) {
    return a > b? a = b, 1 : 0;
}

template<class T> bool chkmax(T &a, const T &b) {
    return a < b? a = b, 1 : 0;
}

template<class T> T input() {
    T r(0); char c(std::getchar()); bool n(false);
    for(; !std::isdigit(c); c = std::getchar()) if(c == '-') n = 1;
    for(; std::isdigit(c); c = std::getchar()) r = r * 10 - 48 + c;
    return n? -r : r;
}

Array sa, rank, fst, snd;

int len;

std::string s;

bool cmp(int *a, int x, int y, int z) {
    return a[x] == a[y] && a[x + z] == a[y + z];
}

void getSa() {
    for(int i = 1; i <= len; ++i) ++fst[rank[i]];
    for(int i = 1; i <= Set; ++i) fst[i] += fst[i - 1];
    for(int i = len; i > 0; --i) sa[fst[rank[i]]--] = i;

    for(int l = 1, i, m = Set, c = 0; c < len; m = c, l <<= 1) {
        for(i = len - l + 1, c = 0; i <= len; ++i) snd[++c] = i;
        for(i = 1; i <= len; ++i) if(sa[i] > l) snd[++c] = sa[i] - l;

        std::memset(fst, 0, sizeof(int) * (m + 1));

        for(i = 1; i <= len; ++i) ++fst[rank[snd[i]]];
        for(i = 1; i <= m; ++i) fst[i] += fst[i - 1];
        for(i = len; i > 0; --i) sa[fst[rank[snd[i]]]--] = snd[i];

        std::swap(rank, snd);
        rank[sa[1]] = 1;

        for(i = 2, c = 1; i <= len; ++i)
            rank[sa[i]] = cmp(snd, sa[i], sa[i - 1], l)? c : ++c;
    }
}

int main() {
    std::ios::sync_with_stdio(false);

    std::cin >> s;

    len = s.length();

    for(int i = 0; i < len; ++i) rank[i + 1] = s[i];

    getSa();

    for(int i = 1; i <= len; ++i)
        std::cout << sa[i] << (i == len? '\n' : ' ');

    return 0;
}
