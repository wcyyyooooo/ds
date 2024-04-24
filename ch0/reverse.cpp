#include <iostream>
#include <vector>
#include <algorithm>
// https://leetcode.cn/problems/rotate-array/solutions/551039/xuan-zhuan-shu-zu-by-leetcode-solution-nipk/
// 有gcd方法的证明
void reverse1(std::vector<int> &v, int k){
    auto iter1 = v.begin() + k - 1;
    auto iter2 = v.begin() + k;
    std::reverse(v.begin(), iter1 + 1);
    std::reverse(iter2, v.end());
    std::reverse(v.begin(), v.end());
}
int gcd(int a, int b){
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}
void reverse2(std::vector<int> &v, int k){
    int n = v.size();
    int step = gcd(n, k);
    for(int i = 0; i < step; i++){
        int pre = i;
        int last = v[i];
        int j = i;
        while(true){
            j = (pre + k) % n;
            if(j == i) break;
            v[pre] = v[j];
            pre = j;
        }
        v[pre] = last;
    }
}
int main(){
    std::vector<int> v;
    for(size_t i = 0; i < 10; i++){
        v.push_back(i);
    }
    reverse1(v, 3);
    for(size_t i = 0; i < 10; i++){
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
    reverse2(v, 3);
    for(size_t i = 0; i < 10; i++){
        std::cout << v[i] << " " ;
    }
}
