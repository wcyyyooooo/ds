#include <iostream>
typedef int Rank;
#define Node(T) ListNode<T>*
template <typename T>
struct ListNode{
    T data;
    Node(T) pre;
    Node(T) nxt;
    ListNode(){};
    ListNode(T e, Node(T) p = nullptr, Node(T) s = nullptr) : data(e), pre(p), nxt(s){};
    Node(T) insertAsPre(T const& e);
    Node(T) insertAsNxt(T const& e);
};

template <typename T>
class List{
    private:
        int _size;
        Node(T) header;
        Node(T) trailer;
    protected:
        void init();
        void clear();
    public:
        List(){init();}
        Node(T) push_front(T const &e);
        Node(T) push_back(T const &e);
        Node(T) find(T const &e);
        Node(T) find(T const &e, int n, Node(T) p);
        int deduplicate();
        int uniquify();
        Node(T) selectMax(Node(T) p, int n);
        void selectSort(Node(T) p, int n);
        void copyNodes(Node(T) p, int n);
        void insertionSort(Node(T) p, int n);
        Node(T) search(Node(T) p, int n, T const &e);
        Node(T) Begin() {return header;}
        Node(T) End() {return trailer;}
        T& operator[](Rank r)const;
        T remove(Node(T) p);
        ~List(){
            clear();
            delete header;
            delete trailer;
        }
};
template <typename T>
void List<T>::init(){
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->pre = nullptr;
    header->nxt = trailer;
    trailer->pre = header;
    trailer->nxt = nullptr;
    _size = 0;
}
template <typename T>
Node(T) List<T>::push_front(T const &e){
    _size++;
    return header->insertAsNxt(e);
}
template <typename T>
Node(T) List<T>::push_back(T const &e){
    _size ++;
    return trailer->insertAsPre(e);
}
// header->....    header <- cur ->header->nxt
template <typename T>
Node(T) ListNode<T>::insertAsNxt(T const &e){
    Node(T) cur = new ListNode<T>(e, this, nxt);
    nxt->pre = cur;
    nxt = cur;
    return cur;
}
// ...->trailer    trailer->pre <- cur -> trailer
template <typename T>
Node(T) ListNode<T>::insertAsPre(T const &e){
    Node(T) cur = new ListNode<T>(e, pre, this);
    pre->nxt = cur;
    pre = cur;
    return cur;
}
template <typename T>
void List<T>::copyNodes(Node(T) p, int n){
    init();
    while(n --){
        this->push_back(p->data);
        p = p->nxt;
    }
}
template <typename T>
T& List<T>::operator[](Rank r) const {
    Node(T) p = header->nxt;
    while(r-- > 0) p = p->nxt;
    return p->data;
}

template <typename T>
T List<T>::remove(Node(T) p){
    T e = p->data;
    p->pre->nxt = p->nxt;
    p->nxt->pre = p->pre;
    delete p;
    _size --;
    return e;
}

template <typename T>
void List<T>::clear(){
    while(_size > 0){
        remove(header->nxt);
    }
}

template <typename T>
Node(T) List<T>::find(T const &e){
    Node(T) cur = header->nxt;
    while(cur != trailer){
        if(cur->data == e){
            return cur;
        }
        cur = cur->nxt;
    }
    return nullptr;
}
template <typename T>
Node(T) List<T>::find(T const &e, int n, Node(T) p){
    while(n-- > 0){
        if(e == (p = p->pre)->data) return p;
    }
    return nullptr;
}
template <typename T>
int List<T>::deduplicate(){
    if(_size < 2) return 0;
    int oldsize = _size;
    Node(T) p = header;
    Rank r = 0;
    while(trailer != (p = p->nxt)){
        Node(T) q = find(p->data, r, p);
        q ? remove(q) : r++;
    }
    return oldsize - _size;
}
template <typename T>
int List<T>::uniquify(){
    if(_size < 2) return 0;
    Rank oldSize = _size;
    Node(T) p = header->nxt;
    Node(T) q = p;
    while(trailer != (q = p->nxt)){
        if(p->data != q->data) p = q;
        else remove(q);
    }
    return oldSize - _size;
}
template <typename T>
void List<T>::selectSort(Node(T) p, int n){
    Node(T) header = p->pre;
    Node(T) tail = p;
    for(int i = 0; i < n; i++) tail = tail->nxt;
    while(n > 1){
        Node(T) mx = selectMax(header->nxt, n);
        T c = mx->data;
        mx->data = tail->pre->data;
        tail->pre->data = c;
        n--;
        tail = tail->pre;
    }
}
template <typename T>
Node(T) List<T>::selectMax(Node(T) p, int n){
    Node(T) mx = p;
    for(; n > 1; n--){
        p = p->nxt;
        if(p->data >= mx->data){
            mx = p;
        }
    }
    return mx;
}
template <typename T>
Node(T) List<T>::search(Node(T) p, int n, T const &e){
    while(n -- >= 0){
        p = p->pre;
        if(p->data <= e){
            break;
        }
    }
    return p;
}
template <typename T>
void List<T>::insertionSort(Node(T) p, int n){
    for(int r = 0; r < n; r++){
        Node(T) ins = search(p, r, p->data);
        std::cout << ins->data << std::endl;
        ++_size;
        ins->insertAsNxt(p->data);
        p = p->nxt;
        remove(p->pre);
    }
}