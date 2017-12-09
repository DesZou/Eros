/**
  luogu1415
  要分两步动归。
  第一步设f[i]为从开始到第i位能分出来的最小的末尾数字的开头
  那么f[i] = j + 1，其中j<i且num(f[j],j)<num(j+1,i)。
  这样可以找到最小的结尾。
  然后设g[i]为从结尾到第i为能分出来的最大的开头数字的末尾。
  得到g[i] = j - 1，其中j>i且num(i,j-1) < num(j,g[j])。
  然后从g[1]开始往后跳着输出即可。
  要注意的是第二次动归要从最后一位数之前开始，才能得到正解。
  并且包括前导零。
 **/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cassert>

const size_t Size = 500 + 5;

char s[Size];

int d[Size], f[Size];

bool cmp(int ax, int ay, int bx, int by) {
    if(ay < ax || by < bx) return false;
    while(s[ax] == '0') ++ax;
    while(s[bx] == '0') ++bx;
    if(ay - ax != by - bx) return (ay - ax) < (by - bx);
    for(int d = 0; ax + d <= ay; ++d)
        if(s[ax + d] != s[bx + d]) return s[ax + d] < s[bx + d];
    return false;
}

void print(int x, int y) {
    while(x <= y) printf("%c", s[x++]);
    putchar(',');
}

int main() {
    int len = 0;

    for(char c = getchar();
            c <= '9' && c >= '0'; 
            s[++len] = c, c = getchar());

    for(int i = 1; f[i] = 1, i <= len; ++i)
        for(int j = 1; j < i; ++j)
            if(cmp(f[j], j, j + 1, i)) f[i] = std::max(f[i], j + 1);

    int sp = f[len];
    while(s[sp - 1] == '0') --sp;

    d[sp] = d[f[len]] = len;
    
    for(int i = sp - 1; i > 0; --i)
        for(int j = i + 1; j <= sp; ++j)
            if(cmp(i, j - 1, j, d[j])) d[i] = std::max(d[i], j - 1);

    for(int i = 1; i < sp; i = d[i] + 1) print(i, d[i]);
    fputs(s + sp, stdout), putchar(10);

    return 0;
}
