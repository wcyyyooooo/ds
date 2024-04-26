#include <iostream>
typedef int Rank;
template <typename T>
class Stack{
    private:
        T *data;
        Rank _size;
        Rank _capacity;
    protected:
        void expand();
    public:
        Stack(int n) : data(new T[n]), _size(0), _capacity(n){}
        Stack() : data(new T[3]), _size(0), _capacity(3){}
        void push(T const &e);
        T pop();
        bool empty();
        Rank Size(){return _size;}
        T top();
};
template <typename T>
void Stack<T>::expand(){
    if(_size < _capacity) return;
    T *old_data = data;
    data = new T[_capacity <<= 1];
    for(int i = 0; i < _size; i++){
        data[i] = old_data[i];
    }
    delete []old_data;
}
template <typename T>
void Stack<T>::push(T const &e){
    expand();
    data[_size++] = e;
}
template <typename T>
T  Stack<T>::pop(){
    T e = data[_size - 1];
    _size --;
    return e;
}
template <typename T>
bool Stack<T>::empty(){
    return _size == 0;
}
template <typename T>
T  Stack<T>::top(){
    return data[_size - 1];
}