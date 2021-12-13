//
//  main.cpp
//  LEETCODE
//
//  Created by 晏榆 on 2021/11/23.
//
/*
 1、
 2、定义定长的二维数组 int matrix[m][n]
 3、vector用法: v.erase(v.begin() + index) v.erase(v.end() - 1)
    vector拷贝： vector<int> new_vector = old_vector;
    push_back是引用传递，但其内部会复制一份；[i]也是返回引用.
    vector<vector<int>>的初始化：
 
 4、string用法: s.substr(start_index, length)
 转换：intToString()
 拼接：str = str1 + str2; append()
 
 5、sort用法: sort(v.begin(), v.end(), [](auto& a, auto& b){ return a > b})
 
 6、map用法：map.find(key) == map().end() 表示找不到元素
    遍历map: auto it = map.begin(); while (it != map.end()) { it++; }
 7、
 */
#include <iostream>
#include "BFile.hpp"

int main(int argc, const char * argv[]) {
  // insert code here...
  std::cout << "Hello, World!\n";
    Solution solution;
    string s = "10[a]2[bc]";
    solution.decodeString(s);
    std::cout << s;
  return 0;
}
