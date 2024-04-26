#include <stack>
#include <string>
#include <unordered_map>
class Solution {
public:
    int cal(const char op, int a, int b){
        switch (op){
            case '+' : return a + b;
            case '-' : return a - b;
            case '*' : return a * b;
            case '/' : return a / b;
        }
        return 0;
    }
    int calculate(std::string s) {
        std::stack<char> op;
        std::stack<int> num;
        int cur = 0;
        int number = 0;
        std::unordered_map<char, int> umap;
        umap['+'] = 1;umap['-'] = 1;umap['*'] = 2;umap['/'] = 2;
        while(true){
            if(cur == s.size()) break;
            if(s[cur] == ' ') {cur ++ ; continue;}
            if(s[cur] >= '0' && s[cur] <= '9'){
                while(s[cur] >= '0' && s[cur] <= '9'){
                    number = number * 10 + (s[cur] - '0');
                    cur ++;
                }
                num.push(number);
                number = 0;
            }else{
                if(!op.empty() && umap[s[cur]] <= umap[op.top()]){
                    int b = num.top(); num.pop();
                    int a = num.top(); num.pop();
                    num.push(cal(op.top(), a, b));
                    op.pop();
                }else{
                    op.push(s[cur]);
                    cur ++;
                }
            }
        }
        while(!op.empty()){
            int b = num.top(); num.pop();
            int a = num.top(); num.pop();
            num.push(cal(op.top(), a, b));
            op.pop();
        }
        return num.top();
    }
};