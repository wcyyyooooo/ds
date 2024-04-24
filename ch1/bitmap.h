#ifndef BITMAP_H
#define BITMAP_H
#include <string.h>
class Bitmap{
    private:
        int N;
        char *M;
    public:
        Bitmap(int n = 8) : N((n + 7) / 8), M(new char[N]){
            memset(M, 0, N);
        }
        ~Bitmap(){delete []M; M = NULL;}
        bool test(int k){
            return M[k >> 3] & (0x80 >> (k & 0x07));
        }
        void set(int k){
            expand(k);
            M[k >> 3] |= (0x80 >> (k & 0x07));
        }
        void clear(int k){
            expand(k);
            M[k >> 3] &= ~(0x80 >> (k & 0x07));
        }
        void expand(int k){
            if((k + 7) / 8 <= N) return;
            char *new_ = new char[(k + 7) / 8];
            memcpy(new_, M, N);
            N = (k + 7) / 8; 
            char *old_ = M;
            M = new_;
            delete []old_;
        }
};

#endif