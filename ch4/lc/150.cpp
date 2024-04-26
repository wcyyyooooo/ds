#include <vector>
#include <string>
#include <iostream>
#include <stack>
using namespace std;
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        for(auto &s : tokens){
            if(s == "+" || s == "-" || s == "*" || s == "/"){
                int b = st.top(); st.pop();
                int a = st.top(); st.pop();
                switch(s[0]){
                    case '+' : {st.push(a + b); break;}
                    case '-' : {st.push(a - b); break;}
                    case '*' : {st.push(a * b); break;}
                    case '/' : {st.push(a / b); break;}
                }
            }else{
                st.push(stoi(s));
            }
        }
        return st.top();
    }
};