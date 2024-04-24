#include <stdio.h>
const int N = 1e7 + 10;
int v[N];
void solve(){
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++){
        int x;
        scanf("%d", &x);
        v[x + 1] += 1;
    }
    for(int i = 1; i < N; i++){
        v[i] += v[i - 1];
    }
    for(int i = 0; i < m; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d\n", v[b + 1] - v[a]);
    }
}
int main(){
    solve();
    return 0;
}
