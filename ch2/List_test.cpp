#include <iostream>
#include "List.h"

int main(){
    List<int> l;
    for(int i = 10; i >= 1; i--){
        l.push_back(i);
    }
    l.insertionSort(l.Begin()->nxt, 10);
    auto cur = l.Begin()->nxt;
    while(cur != l.End()){
        cur = cur->nxt;
    }
    std::cout << std::endl;
}