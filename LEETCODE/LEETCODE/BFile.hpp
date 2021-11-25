//
//  BFile.hpp
//  LEETCODE
//
//  Created by 晏榆 on 2021/11/23.
//

#ifndef BFile_hpp
#define BFile_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <stack>

using namespace std;

class Solution {
//  以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。请你合并所有重叠的区间，并返回一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间。
public:
  vector<vector<int>> merge(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b) {
      return a[0] < b[0];
    });
    
    vector<vector<int>> result;
    for (auto& interval : intervals) {
      // ragular case
      int interval_min = interval[0];
      int interval_max = interval[1];
      bool find = false;
      for (auto& cluster : result) {
        int cluster_min = cluster[0];
        int cluster_max = cluster[1];
        // case 1
        if (interval_min <= cluster_max &&
            interval_min >= cluster_min &&
            interval_max > cluster_max) {
          cluster[1] = interval_max;
          find = true;
        }
        // case 2
        else if (interval_min < cluster_min &&
                 interval_max >= cluster_min &&
                 interval_max <= cluster_max) {
          cluster[0] = interval_min;
          find = true;
        }
        // case 3
        else if (interval_min <= cluster_min && interval_max >= cluster_max) {
          cluster[0] = interval_min;
          cluster[1] = interval_max;
          find = true;
        }
        // case 4
        else if (interval_min >= cluster_min && interval_max <= cluster_max) {
          find = true;
        }
      }
      
      if (!find) {
        result.push_back(interval);
      }
    }
    
    return result;
  };
//  一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。
//  机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。
//  问总共有多少条不同的路径？
  int uniquePaths(int m, int n) {
    int sum = 0;
    int matrix[m][n];
    for (int i = 0; i < m; i ++) {
      for (int j = 0; j < n; j ++) {
        if (i == 0) {
          matrix[i][j] = 1;
        } else if (j == 0) {
          matrix[i][j] = 1;
        } else {
          matrix[i][j] = matrix[i - 1][j] + matrix[i][j - 1];
        }
      }
    }
    sum = matrix[m - 1][n - 1];
    
    return sum;
  };
  // 有权重求极值的版本
  int minPathSum(vector<vector<int>>& grid) {
    int sum = 0;
    unsigned long m = grid.size();
    unsigned long n = grid[0].size();
    
    int matrix[m][n];
    for (int i = 0; i < m; i ++) {
      for (int j = 0; j < n; j ++) {
        int value = grid[i][j];
        if (i == 0 && j == 0) {
          matrix[i][j] = value;
        } else if (i == 0) {
          matrix[i][j] = matrix[i][j - 1] + value;
        } else if (j == 0) {
          matrix[i][j] = matrix[i - 1][j] + value;
        } else {
          int value1 = matrix[i - 1][j];
          int value2 = matrix[i][j - 1];
          int cur_value = value1 < value2? value1: value2;
          cur_value += value;
          matrix[i][j] = cur_value;
        }
      }
    }
    sum = matrix[m - 1][n - 1];
    return sum;
  };
//  给定一个包含红色、白色和蓝色，一共 n 个元素的数组，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。
//  此题中，我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。
  void sortColors(vector<int>& nums) {
    int first = 0;
    int last = (int)nums.size() - 1;
    while (first < last &&
           first < nums.size() &&
           last >= 0) {
      if (nums[first] == 0) {
        first ++;
      } else if (nums[last] == 2) {
        last --;
      } else if (nums[first] == 2) {
        nums[first] = nums[last];
        nums[last] = 2;
        last --;
      } else if (nums[last] == 0) {
        nums[last] = nums[first];
        nums[first] = 0;
        first ++;
      } else if (nums[first] == nums[last]) {
        // special case : first = last = 1, break it
        bool has_swap = false;
        for (int i = first + 1; i < last; i ++) {
          int value = nums[i];
          if (value == 0) {
            nums[first] = 0;
            nums[i] = 1;
            has_swap = true;
            break;
          } else if (value == 2) {
            nums[last] = 2;
            nums[i] = 1;
            has_swap = true;
            break;
          }
        }
        
        if (!has_swap) {
          break;
        }
      }
    }
  };
  void sortColors2(vector<int>& nums) {
    int n = (int)nums.size();
    int p0 = 0, p2 = n - 1;
    for (int i = 0; i <= p2; ++i) {
      while (i <= p2 && nums[i] == 2) {
        swap(nums[i], nums[p2]);
        --p2;
      }
      if (nums[i] == 0) {
        swap(nums[i], nums[p0]);
        ++p0;
      }
    }
  };
  
//  给定一个只包含三种字符的字符串：（ ，） 和 *，写一个函数来检验这个字符串是否为有效字符串。有效字符串具有如下规则：
//
//  任何左括号 ( 必须有相应的右括号 )。
//  任何右括号 ) 必须有相应的左括号 ( 。
//  左括号 ( 必须在对应的右括号之前 )。
//  * 可以被视为单个右括号 ) ，或单个左括号 ( ，或一个空字符串。
//  一个空字符串也被视为有效字符串。
  bool checkValidString(string s) {
    stack<int> left_stack;
    stack<int> star_stack;
    for (int i = 0; i < s.length(); i ++) {
      char c = s[i];
      if (c == '(') {
        left_stack.push(i);
      } else if (c == '*') {
        star_stack.push(i);
      } else if (c == ')') {
        if (!left_stack.empty()) {
          left_stack.pop();
        } else if (!star_stack.empty()) {
          star_stack.pop();
        } else {
          return false;
        }
      }
    } // end for
    while (!left_stack.empty() && !star_stack.empty()) {
      int left_index = left_stack.top();
      left_stack.pop();
      int star_index = star_stack.top();
      star_stack.pop();
      if (left_index > star_index) {
        return false;
      }
    }
    
    return left_stack.empty();
  };
};

#endif /* BFile_hpp */
