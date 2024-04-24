#include <iostream>
#include "bitmap.h"
void test1(int n){
    Bitmap B(n);
    B.set(0); B.set(1);
    for(int i = 2; i <= n; i++){
        if(!B.test(i)){
            for(int j = 2 * i; j <= n; j += i){
                B.set(j);
            }
        }
    }
    for(int i = 0; i < n; i++){
        if(!B.test(i)){
            std::cout << i << "是质数" << std::endl;
        }
    }
}
void test2(int n){
    Bitmap B(n);
    B.set(0); B.set(1);
    // 如果 n = p * q p == q时 n为完全平方数 p = sqrt(n)
    // p != q 设 p < q 则 p < sqrt(n)
    // 寻找n的因子时只需要遍历到sqrt(n), 如果一个数没有<=sqrt(n)的因子，其一定为质数
    // 从 i * i遍历 因为如果从 p * i开始遍历， p < i， 这个p * i会在遍历p的倍数时被遍历
    // 外层遍历sqrt(n) / (ln(sqrt(n))) 内层 n / i - i
    // n(1/2 + 1/3 + ... + 1/ln(sqrt(n)))
    // nlog(logn)
    for(int i = 2; i * i <= n; i++){
        if(!B.test(i)){
            for(int j = i * i; j <= n; j += i){
                B.set(j);
            }
        }
    }
    for(int i = 0; i < n; i++){
        if(!B.test(i)){
            std::cout << i << "是质数" << std::endl;
        }
    }
}
int main(){
    test1(100);
    test2(100);
}