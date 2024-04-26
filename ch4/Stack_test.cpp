#include <iostream>
#include "Stack.h"
#include <string.h>
#include <assert.h>
#include <vector>
#include <unordered_map>
// 进制转换
void test_1(int n, int base){
    Stack<char> st;
    static char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    while(n > 0){
        st.push(digit[n % base]);
        n = n / base;
    }
    int sz = st.Size();
    for(int i = 0; i < sz; i++){
        std::cout << st.pop() << " ";
    }
    std::cout << std::endl;
}
// 括号匹配 仅支持() {} []
bool test2(const char *s){
    Stack<char> st;
    for(int i = 0; i < strlen(s); i++){
        char c = s[i];
        if(c == '(' || c == '{' || c == '[') {st.push(c); continue;}
        switch (c){
            case ')':
                if(!st.empty() && st.top() == '(') {st.pop(); break;}
                else return false;
            case '}':
                if(!st.empty() && st.top() == '{') {st.pop(); break;}
                else return false;
            case ']':
                if(!st.empty() && st.top() == '[') {st.pop(); break;}
                else return false;
            default:
                return false;
        }
    }
    return st.empty();
}
// 模拟栈混洗的所有排列
// 有多少次 push就有多少次pop 状态压缩设0为pop 1为push
std::vector<std::vector<int>> test3(){
    std::vector<std::vector<int>> ans;
    for(auto i = 0; i < (1 << 10); i++){
        bool is_done = true;
        Stack<int> st;
        int cur = 1;
        std::vector<int> v;
        for(auto j = 0; j < 10; j++){
            if((i >> j & 1) == 0){
                if(st.empty()){
                    is_done = false;
                    break;
                }else{
                    v.push_back(st.pop());
                }
            }else{
                if(cur >= 6){
                    is_done = false;
                    break;
                }else{
                    st.push(cur);
                    cur += 1;
                }
            }
        }
        if(is_done) ans.push_back(v);
    }
    std::cout << "栈混洗个数：" << ans.size() << std::endl;
    for(auto &v : ans){
        for(auto &vi : v){
            std::cout << vi << " ";
        }
        std::cout << std::endl;
    } 
    return ans;
}
// 检测栈混洗序列是否正确
bool check(std::vector<int> &v){
    Stack<int> st;
    int cur = v.size();
    while(!v.empty()){
        auto ele = v.back();
        v.pop_back();
        st.push(ele);
        while(!st.empty() && st.top() == cur){
            st.pop();
            cur --;
        }
    }
    return st.empty();
}
std::unordered_map<char, int> umap;
void init(){
    umap['+'] = 1;
    umap['-'] = 1;
    umap['*'] = 2;
    umap['/'] = 2;
}
int cal(const char op, int a, int b){
    switch(op){
        case '+' : return a + b;
        case '-' : return a - b;
        case '*' : return a * b;
        case '/' : return a / b;
    }
    return 0;
}
// 中缀表达式求值
// 只支持 + - / * 
int eval(const char *s, std::string &rpn){
    Stack<int> nums;
    Stack<char> op;
    int cur = 0;
    int number = 0;
    init();
    while(true){
        if(s[cur] == '\0') break;
        if(s[cur] >= '0' && s[cur] <= '9'){
            while(s[cur] >= '0' && s[cur] <= '9'){
                rpn.push_back(s[cur]);
                number = number * 10 + (s[cur] - '0');
                cur ++;
            }
            nums.push(number);
            number = 0;
        }else{
            // 相等或者栈顶优先级高先计算栈顶 
            if(!op.empty() && umap[s[cur]] <= umap[op.top()]){
                int num2 = nums.pop();
                int num1 = nums.pop();
                rpn.push_back(op.top());
                nums.push(cal(op.pop(), num1, num2));
            }else{
                op.push(s[cur]);
                cur++;
            }
        }
    }
    while(!op.empty()){
        int num2 = nums.pop();
        int num1 = nums.pop();
        rpn.push_back(op.top());
        nums.push(cal(op.pop(), num1, num2));
    }
    return nums.top();
}
int main(){
    test_1(89, 2);
    assert(test2("(([])){[[]]}"));
    auto ans = test3();
    std::vector<int> v = {3, 1, 2, 4, 5};
    assert(check(v) == false);
    for(auto &ai : ans){
        for(auto &aii : ai){
            std::cout << aii << " ";
        }
        std::cout << std::endl;
        assert(check(ai));
    }
    std::string s = "";
    assert(eval("3+2*2", s) == 7);
    assert(s == "322*+");
    s.clear();
    assert(eval("3+5/2", s) == 5);
    assert(s == "352/+");
}