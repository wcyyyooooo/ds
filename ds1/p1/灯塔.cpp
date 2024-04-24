#include <stdio.h>
#include <stdlib.h>
#include <iostream>
typedef long long LL;
struct pair{
    int first;
    int second;
};
const int N = 4e6 + 10;
pair v[N];
LL res = 0;
int c[N];
void mergesort(int l, int r){
    if(l >= r) return;
    int mid = (l + r) >> 1;
    mergesort(l, mid);
    mergesort(mid + 1, r);
    int i = l; int j = mid + 1; int k = 0;
    while(i <= mid && j <= r){
        if(v[i].second <= v[j].second){
            c[k++] = v[i++].second;
            res += r - j + 1;
        }else{
            c[k++] = v[j++].second;
        }
    }
    while(i <= mid) c[k++] = v[i++].second;
    while(j <= r) c[k++] = v[j++].second;
    k = 0;
    for(int i = l; i <= r; i++){
        v[i].second = c[k++];
    }
}
void quicksort(int l, int r){
    if(l >= r) return;
    int div = v[(l + r + 1) / 2].first;
    int i = l - 1;
    int j = r + 1;
    while(i < j){
        do i++; while(v[i].first < div);
        do j--; while(v[j].first > div);
        if(i < j){
            std::swap(v[i], v[j]);
        }
    }
    quicksort(l, i - 1);
    quicksort(i, r);
}
void shuffle(size_t n) {  
    srand(time(NULL));
    for (size_t i = n - 1; i > 0; i--) {  
        size_t j = rand() % (i + 1);
        std::swap(v[i], v[j]);
    }  
}
void solve(){
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        v[i] = pair{a, b};
    }
    shuffle(n);
    quicksort(0, n - 1);
    mergesort(0, n - 1);
    printf("%lld\n", res);
}
int main(){
    solve();
}