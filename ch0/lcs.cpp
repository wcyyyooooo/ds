#include <iostream>
#include <vector>
#include <string_view>

int lcs1(std::string_view str1, std::string_view str2){
    if(str1.size() == 0 || str2.size() == 0) return 0;
    if(str1.back() == str2.back()){
        return lcs1(str1.substr(0, str1.size() - 1), str2.substr(0, str2.size() - 1)) + 1;
    }
    return std::max(lcs1(str1, str2.substr(0, str2.size() - 1)), lcs1(str1.substr(0, str1.size() - 1), str2));
}

int lcs2(std::string_view str1, std::string_view str2){
    std::vector<std::vector<int>> dp(str1.size() + 1, std::vector<int>(str2.size() + 1));
    for(size_t i = 0; i <= str1.size(); i++){
        dp[i][0] = 0;
    }
    for(size_t i = 0; i < str1.size(); i++){
        dp[0][i] = 0;
    }
    for(size_t i = 1; i <= str1.size(); i++){
        for(size_t j = 1; j <= str2.size(); j++){
            if(str1[i - 1] == str2[j - 1]){
                dp[i][j] = std::max(dp[i - 1][j - 1] + 1, dp[i][j]);
            }else{
                dp[i][j] = std::max(dp[i][j - 1], std::max(dp[i - 1][j - 1], dp[i - 1][j]));
            }
        }
    }
    return dp[str1.size()][str2.size()];
}
int main(){
    std::cout << lcs1("program", "algorithm") << " " << "right answer : 3" << std::endl;
    std::cout << lcs2("program", "algorithm") << " " << "right answer : 3" << std::endl;
}