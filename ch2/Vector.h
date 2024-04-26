#include <iostream>
#include <list>
typedef int Rank;

template<typename T>
class Vector{
    public:
        const T & operator[] (Rank r) const ;
        Rank insert(Rank r, T &e);
        int remove(Rank lo, Rank hi);
        T remove(Rank r);
        Rank find(T const &e, Rank lo, Rank hi);
        template <typename F>
        void traverse(F &fun);
        int deduplicate();
        int disordered();
        int uniquify();
        Rank search(T const& e, Rank lo, Rank hi) const;
        void print();
        void bubbleSort(Rank lo, Rank hi);
        void mergeSort(Rank lo, Rank hi);
        Rank Size() {return _size;}
        Vector(int c = 3) : _ele(new T[c]), _capacity(c), _size(0) {}
        Vector(T const *a, Rank lo, Rank hi){copyfrom(a, lo, hi);}
        Vector(Vector<T> &v, Rank lo, Rank hi){copyfrom(v._ele, lo, hi);}
        Vector(Vector<T> &v){copyfrom(v._ele, 0, v.size());}
        ~Vector(){delete []_ele;}
    protected:
        void copyfrom(T const *ele, Rank lo, Rank hi);
        void expand();
        void merge(Rank lo, Rank mid, Rank hi);
        void shrink(){}
    private:
        T* _ele;
        Rank _size;
        Rank _capacity;
};


template <typename T>
void Vector<T>::print(){
    std::cout << "Size : " << _size << std::endl;
    std::cout << "Capacity : " << _capacity << std::endl;
    for(size_t i = 0; i < _size; i++){
        std::cout << _ele[i] << " ";
    }
    std::cout << std::endl;
}
template <typename T>
void Vector<T>::copyfrom(T const *ele, Rank lo, Rank hi){
    _ele = new T[_capacity = 2 * (hi - lo)];
    _size = 0;
    while(lo < hi){
        _ele[_size ++] = ele[lo++];
    }
}
template <typename T>
void Vector<T>::expand(){
    if(_size < _capacity) return;
    T *old_ele = _ele;
    _ele = new T[_capacity <<= 1];
    for(int i = 0; i < _size; i++){
        _ele[i] = old_ele[i];
    }
    delete []old_ele;
}
template <typename T>
const T & Vector<T>::operator[](Rank r) const {return _ele[r];}

template <typename T>
Rank Vector<T>::insert(Rank r, T &e){
    expand();
    for(int i = _size; i > r; i--){
        _ele[i] = _ele[i - 1];
    }
    _ele[r] = e;
    _size ++;
    return r;
}

template <typename T>
int Vector<T>::remove(Rank lo, Rank hi){
    if(lo == hi) return 0;
    while(hi < _size) _ele[lo++] = _ele[hi++];
    _size = lo;
    shrink();
    return hi - lo;
}

template <typename T>
T Vector<T>::remove(Rank r){
    T e = _ele[r];
    remove(r, r + 1);
    return e;
}

template <typename T>
Rank Vector<T>::find(T const & e, Rank lo, Rank hi){
    while((lo < hi -- ) && e != _ele[hi]);
    return hi;
}

template <typename T>
int Vector<T>::deduplicate(){
    int old_size = _size;
    Rank i = 1;
    while(i < _size){
        (find(_ele[i], 0, i) < 0) ? i++ : remove(i);
    }
    return old_size - _size;
}
template<typename T>
template <typename F>
void Vector<T>::traverse(F &fun){
    for(int i = 0; i < _size; i++) fun(_ele[i]);
}
template <typename T>
int Vector<T>::disordered(){
    int n = 0;
    for(int i = 1; i < _size; i++){
        if(_ele[i - 1] > _ele[i]) n++;
    }
    return n;
}
template <typename T>
int Vector<T>::uniquify(){
    int old_size = _size;
    Rank i = 0, j = 0;
    while(++j < _size){
        if(_ele[i] != _ele[j]) _ele[++i] = _ele[j];
    }
    _size = ++i;
    shrink();
    return old_size - _size;
}

template <typename T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const {
    return (rand() % 2) ? binSearch(_ele, e, lo, hi) : fibSearch(_ele, e, lo, hi);
}

// [lo, hi)
template <typename T>
static Rank binSearch(T *A, T const& e, Rank lo, Rank hi){
    while(lo < hi){
        Rank mid = (lo + hi) >> 1;
        // [lo, mid)
        if(e < A[mid]) hi = mid;
        // [mid + 1, hi)
        else if(e > A[mid]) lo = mid + 1;
        else return mid;
    }
    return -1;
}

template <typename T>
static Rank binSearchB(T *A, T const& e, Rank lo, Rank hi){
    while(hi - lo > 1){
        Rank mid = (lo + hi) >> 1;
        if(e < A[mid]){
            hi = mid;
        }else{
            lo = mid;
        }
    }
    return (e == A[lo]) ? lo : -1;
}

template <typename T>
static Rank binSearchC(T *A, T const& e, Rank lo, Rank hi){
    while(lo < hi){
        Rank mid = (lo + hi) >> 1;
        if(A[mid] <= e){
            lo = mid + 1;
        }else{
            hi = mid;
        }
    }
    return lo - 1;
}
class Fib{
    public:
        Fib(Rank n){
            int f0 = 0;
            int f1 = 1;
            lst.push_back(f0);
            lst.push_back(f1);
            while(f1 <= n){
                f0 = f1;
                f1 = f1 + f0;
                lst.push_back(f1);
            }
        }
        Rank get(){return lst.back();}
        void pre() {lst.pop_back();}
    private:
        std::list<Rank> lst;
};
template <typename T>
static Rank fibSearch(T *A, T const& e, Rank lo, Rank hi){
    Fib fib(hi - lo);
    while(lo < hi){
        while(hi - lo < fib.get()) fib.pre();
        Rank mid = lo + fib.get() - 1;
        if(e < A[mid]){
            hi = mid;
        }else if(A[mid] < e){
            lo = mid + 1;
        }else{
            return mid;
        }
    }
    return -1; 
}
template <typename T>
static Rank bubble(T *A, Rank lo, Rank hi){
    Rank last = lo;
    while(++lo < hi){
        if(A[lo - 1] > A[lo]){
            last = lo;
            std::swap(A[lo - 1], A[lo]);
        }
    }
    return last;
}
template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi){
    while(lo < (hi = bubble(_ele, lo, hi)));
}
// 合并[lo, mid) [mid, hi)
template <typename T>
void Vector<T>::merge(Rank lo, Rank mid, Rank hi){
    T* A = _ele + lo;
    int lb = mid - lo;
    T* B = new T[lb];
    for(int i = 0; i < lb; i++){
        B[i] = A[i];
    }
    int lc = hi - mid;
    T* C = _ele + mid;
    for(Rank i = 0, j = 0, k = 0; j < lb; ){
        if((k < lc) && C[k] < B[j]) A[i++] = C[k++];
        if(!(k < lc) || B[j] <= C[k]) A[i++] = B[j++];
    }
    delete []B;
}
template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi){
    if(hi - lo == 1) return;
    Rank mid = (lo + hi) / 2;
    mergeSort(lo, mid); mergeSort(mid, hi);
    merge(lo, mid, hi);
}