#include <cstring>
#include <cstdio>
#include <algorithm>
#include <iostream>

const size_t Length = 41e6 + 5;

int rl[Length];
char s[Length];

int manacher(const char *s, int len) {
    static char a[Length];

    for(int i = 0; i < len; ++i)
        a[i << 1] = '#', a[i << 1|1] = s[i];

    a[len << 1] = '#';
    len = len << 1 | 1;

    int mr = 0, p = 0, res = 0;

    for(int i = 0; i < len; ++i) {
        rl[i] = i < mr? std::min(rl[(p << 1) - i], mr - i) : 1;
        while(i - rl[i] >= 0 && i + rl[i] < len &&
                a[i - rl[i]] == a[i + rl[i]]) ++rl[i];
        if(rl[i] + i - 1 > mr) mr = rl[i] + i - 1, p = i;
        res = std::max(res, rl[i]);
    }
    return res - 1;
}

int main() {
    std::scanf("%s", s);

    int len = std::strlen(s);

    std::printf("%d\n", manacher(s, len));

    return 0;
}
