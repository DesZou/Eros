/**
 luogu2023
 线段树维护标记，先乘后加即可。
 **/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

const int size = 1e5 + 2; long long Mod;
struct Node{
    long long s,t,val,plusTag,timesTag;
    Node *left,*right;
    inline bool contain(int l,int r){return s >= l && t <= r;}
    inline void pushUp(){val = (left->val + right->val) % Mod;}
    inline int Mid(){return ((s ^ t) >> 1) + (s & t);}
    inline void pushDownTo(int plus,int times){
        plusTag = (plusTag * times + plus) % Mod,
        timesTag = (timesTag * times) % Mod,
        val = (val * times + plus * (t - s + 1)) % Mod;
    }
    void checkTag(){
        if(plusTag || timesTag != 1){
            left->pushDownTo(plusTag,timesTag);
            right->pushDownTo(plusTag,timesTag);
            plusTag = 0, timesTag = 1;
        }
    }
    void plus(int l,int r,long long key){
        if(contain(l,r)){
            val = (val + (t - s + 1) * key) % Mod;
            plusTag = (plusTag + key) % Mod;
        }else{
            checkTag();
            if(l <= Mid()) left->plus(l,r,key);
            if(r > Mid()) right->plus(l,r,key);
            pushUp();
        }
    }
    void times(int l,int r,long long key){
        if(contain(l,r)){
            val = val * key % Mod;
            timesTag = timesTag * key % Mod;
            plusTag = plusTag * key % Mod;
        }else{
            checkTag();
            if(l <= Mid()) left->times(l,r,key);
            if(r > Mid()) right->times(l,r,key);
            pushUp();
        }
    }
    long long query(int l,int r){
        if(contain(l,r)) return val;
        checkTag(); long long ans = 0;
        if(l <= Mid()) ans += left->query(l,r);
        if(r > Mid()) ans += right->query(l,r);
        return ans % Mod;
    }
}*root;

inline int input(){
    static int x; bool f = 1; static char c;
    x = 0, c = getchar();
    while(c<'0'||c>'9'){if(c == '-') f = 0; c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)-48+c; c=getchar();}
    return f? x:-x;
}

void build(Node* &now,int s,int t){
    now = new Node, now->s = s, now->t = t, now->timesTag = 1, now->plusTag = 0;
    int mid = (s + t) >> 1;
    if(s == t) now->val = input();
    else{build(now->left,s,mid); build(now->right,mid + 1,t); now->pushUp();}
}

int main(){
    int N,M;
    N = input(), Mod = input();
    build(root,1,N), M = input();
    while(M--){
        static int s,x,y;
        s = input(), x = input(), y = input();
        switch(s){
            case 1:{root->times(x,y,input()); break;}
            case 2:{root->plus(x,y,input()); break;}
            default: printf("%lld\n",root->query(x,y));
        }
    }
    return 0;
}
