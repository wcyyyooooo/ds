#include "Vector.h"
#include <iostream>
int main(){
    Vector<int> v;
    for(int i = 0; i < 10; i++){
        v.insert(0, i);
    }
    v.print();
    v.mergeSort(0, v.Size());
    v.print();
    return 0;
}