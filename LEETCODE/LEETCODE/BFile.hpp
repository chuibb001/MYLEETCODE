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
  
};

#endif /* BFile_hpp */
