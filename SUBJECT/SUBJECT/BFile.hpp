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
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };

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
//    给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。
//    解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> empty_set;
        result.push_back(empty_set);
        for (int i = 0; i < nums.size(); i ++) {
            int num = nums[i];
            int old_size = (int)result.size();
            for (int i = 0; i < old_size; i ++) {
                vector<int> old_vector = result[i];
                vector<int> new_vector;
                // 添加旧元素
                for (auto& old_num : old_vector) {
                    new_vector.push_back(old_num);
                }
                new_vector.push_back(num);
                result.push_back(new_vector);
            }
        }
        return result;
    };
    vector<vector<int>> subsets2(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> temp;
        for (int length = 0; length < nums.size(); length ++) {
            subsets_backtrace(0, length, temp, nums, result);
        }
        return result;
    };
    void subsets_backtrace(int start, int length, vector<int>& temp, vector<int>& nums, vector<vector<int>>& result) {
        if (length == 0) {
            result.push_back(temp);
            return;
        }
        
        if (start + length > nums.size()) {
            return;
        }
        
        for (int i = start; i < nums.size(); i ++) {
            temp.push_back(nums[i]);
            subsets_backtrace(start + 1, length - 1, temp, nums, result);
            temp.erase(temp.end());
        }
    }
//    给你一个字符串 s 和一个字符串列表 wordDict 作为字典，判定 s 是否可以由空格拆分为一个或多个在字典中出现的单词。
    bool wordBreak(string s, vector<string>& wordDict) {
            // 构建查询字典
            std::unordered_map<string, bool> dict_map;
            for (auto& dict : wordDict) {
                dict_map[dict] = true;
            }
            // 结果数组
            int n = (int)s.length();
            bool result[n + 1];
            result[0] = true;
            // 动态规划
            for (int i = 1; i <= n; i ++) {
                for (int j = 0; j < i; j ++) {
                    // 根据j分割的两个字符串都合法
                    if (result[j] && dict_map[s.substr(j, i - j)]) {
                        result[i] = true;
                        break;
                    } else {
                        result[i] = false;
                    }
                }
            }
            return result[n];
        }
//    给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
//    岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
//    此外，你可以假设该网格的四条边均被水包围。
    int numIslands(vector<vector<char>>& grid) {
        vector<vector<bool>> visit(grid.size(), vector<bool>(grid[0].size(), false));
        int count = 0;
        for (int row = 0; row < grid.size(); row ++) {
            vector<char> row_vector = grid[row];
            for (int col = 0; col < row_vector.size(); col ++) {
                if (visit[row][col] == false && grid[row][col] == '1') {
                    checkIsland(grid, visit, row, col);
                    count ++;
                }
            }
        }
        
        return count;
    };
    
    void checkIsland(vector<vector<char>>& grid, vector<vector<bool>>& visit, int row_index, int col_index) {
            // 把当前位置访问了
            visit[row_index][col_index] = true;
            
            // 继续访问
            vector<pair<int, int>> direction;
            direction.emplace_back(0, 1);
            direction.emplace_back(0, -1);
            direction.emplace_back(1, 0);
            direction.emplace_back(-1, 0);
            for (int i = 0; i < direction.size(); i ++) {
                pair<int, int>& dir = direction[i];
                int new_row = row_index + dir.first;
                int new_col = col_index + dir.second;
                if (new_row < grid.size() &&
                     new_col < grid[0].size() &&
                        new_row >= 0 &&
                        new_col >= 0 &&
                        grid[new_row][new_col] != '0' &&
                        visit[new_row][new_col] == false) {
                    checkIsland(grid, visit, new_row, new_col);
                 }
            }
        }
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // 构造图的边
        vector<vector<int>> graph(numCourses);
        for (auto& pre : prerequisites) {
            graph[pre[0]].push_back(pre[1]);
        }
        
        // 访问过的节点数组（回溯用）
        vector<bool> visit(numCourses, false);
        // 访问过的节点数组（永久记录）
        vector<bool> step(numCourses, false);

        // 找起点：注意可能有多个图集合
        for (int i = 0; i < numCourses; i ++) {
            if (step[i] == false) {
                if (has_cycle_recursive(i, graph, visit, step)) { // 只要找到一个环就可以返回FALSE了
                    return false;
                }
            }
        }
        
        return true;
    }
    // 监测cur_course为起点的子图里有没有环
    bool has_cycle_recursive(int cur_course, vector<vector<int>>& graph, vector<bool>& visit, vector<bool>& step) {
        visit[cur_course] = true;
        step[cur_course] = true;
        vector<int>& edges = graph[cur_course];
        bool has_cycle = false;
        for (int i = 0; i < edges.size(); i ++) {
            int node = edges[i];
            if (visit[node] == true) { // 下一个节点访问过，即有环
                return true;
            }
            has_cycle = has_cycle_recursive(node, graph, visit, step);
            if (has_cycle == true) {
                return true;
            }
        }
        visit[cur_course] = false; // 回溯
        
        return has_cycle;
    }
//    s = "3[a]2[bc]"
//    s = "3[a2[c]]"
    string decodeString(string s) {
        stack<int> stack;
        int i = 0;
        while (i != s.size()) {
            string sub_str = s.substr(i, 1);

            if (sub_str == "[") {
                stack.push(i);
            } else if (sub_str == "]") {
                // 进行局部展开
                int left_index = stack.top();
                stack.pop();
                string repeat_str = s.substr(left_index + 1, i - left_index - 1);
                // 找数字
                int num = 0;
                int inc = 1;
                int num_index = left_index - 1;
                int num_count = 0;
                while (num_index > -1) {
                    string num_str = s.substr(num_index, 1);
                    char num_char = *num_str.c_str();
                    if (num_char >= 48 && num_char <= 57) {
                        int cur_num = num_char - 48;
                        num += (cur_num * inc);
                        inc *= 10;
                        num_count ++;
                    } else {
                        break;
                    }
                    num_index -- ;
                }
                string complete_str;
                for (int time = 0; time < num; time ++) {
                    complete_str += repeat_str;
                }
                s = s.substr(0, left_index - num_count) + complete_str + s.substr(i + 1, s.size() - i - 1);
                i -= (i - left_index + num_count);
                i += (complete_str.length() - 1);
            }
            i ++;
        }

        return s;
    }
//    给你一个 只包含正整数 的 非空 数组 nums 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
//    [1,5,11,5]
    bool canPartitionDP(vector<int>& nums) {
        int sum = sumOfNums(nums);
        if (sum % 2 != 0) {
            return false;
        }
        if (nums.size() < 2) {
            return false;
        }
        int half_sum = sum / 2;
        vector<vector<int>> dp(nums.size(), vector<int>(half_sum + 1, 0)); // dp表示该列的数值容量下，能否由行表示的子数组的子集和最大值
        // 初始化第一行
        int num = nums[0];
        if (num <= half_sum)
            dp[0][num] = num;
        for (int i = 1; i < nums.size(); i ++) {
            int num = nums[i];
            for (int j = 1; j <= half_sum; j ++) {
                if (j - num >= 0) {
                    if (num + dp[i - 1][j - num] == j) {
                        dp[i][j] = num + dp[i - 1][j - num];
                    }
                }
                // 没找到新结果，就集成旧结果
                if (dp[i][j] == 0) {
                    dp[i][j] = dp[i - 1][j];
                }
                
            }
        }
        
        return dp[nums.size() - 1][half_sum] == half_sum;
    }
    
    bool canPartition(vector<int>& nums) {
        int mid = (int)nums.size() / 2;
        int sum = sumOfNums(nums);
        double half_sum = (double)sum / 2.0;
        
        for (int i = 1; i <= mid; i ++) {
            // 递归找到C(n, i)
            vector<int> result;
            if (canPartitionRecursive(nums, result, 0, i, half_sum)) {
                return true;
            }
        }
        
        return false;
    }
    bool canPartitionRecursive(vector<int>& nums, vector<int>& result, int start_index, int pick_count, double sum) {
        if (result.size() == pick_count) {
            if (sumOfNums(result) == sum) {
                return true;
            } else {
                return false;
            }
        } else {
            for (int i = start_index; i < nums.size(); i ++) {
                result.push_back(nums[i]);
                bool success = canPartitionRecursive(nums, result, i + 1, pick_count, sum);
                if (success) {
                    return true;
                }
                result.pop_back();
            }
        }
        
        return false;
    }
    
    int sumOfNums(vector<int>& nums) {
        int sum = 0;
        for (int& num: nums) {
            sum += num;
        }
        return sum;
    }
//    给定两个字符串 s 和 p，找到 s 中所有 p 的 异位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。
//    异位词 指由相同字母重排列形成的字符串（包括相同的字符串）。
    vector<int> findAnagrams(string s, string p) {
        vector<int> result;
        if (p.size() > s.size()) return result;
        
        int length = (int)p.length();
        vector<int> s_count(26, 0);
        vector<int> p_count(26, 0);
        // 初始化窗口
        for (int i = 0; i < length; i ++) {
            ++s_count[s[i] - 97];
            ++p_count[p[i] - 97];
        }
        
        // 首次比较
        if (s_count == p_count) {
            result.push_back(0);
        }
        
        // 滑动窗口
        for (int i = 0; i < s.length() - p.length(); i ++) {
            ++s_count[s[i + length] - 97];
            --s_count[s[i] - 97];
            
            if (s_count == p_count) {
                result.push_back(i + 1);
            }
        }
        
        return result;
    }
    
    void findAnagramsRecursive(string p, string cur, unordered_set<string>& table, vector<bool>& use) {
        if (p.length() == cur.length()) {
            table.insert(cur);
        } else {
            for (int i = 0; i < p.length(); i ++) {
                if (!use[i]) {
                    cur += p.substr(i, 1);
                    use[i] = true;
                    findAnagramsRecursive(p, cur, table, use);
                    use[i] = false;
                    cur.pop_back();
                }
            }
        }
    }
    
    TreeNode* convertBST(TreeNode* root) {
        convertBSTRecursive(root, 0);
        return root;
    }
    int convertBSTRecursive(TreeNode* root, int base) {
        if (!root) return 0;
        
        int this_root_max_sum_except_base = root->val;
        
        // right tree first
        if (root->right) {
            int sum = convertBSTRecursive(root->right, base);
            root->val += sum;
            this_root_max_sum_except_base = root->val;
        }
        
        // left tree second
        if (root->left) {
            int sum = convertBSTRecursive(root->left, root->val + base);
            this_root_max_sum_except_base += sum;
        }
        
        root->val += base;
        
        return this_root_max_sum_except_base;
    }
//    给你一个整数数组 nums ，你需要找出一个 连续子数组 ，如果对这个子数组进行升序排序，那么整个数组都会变为升序排序。
//    输入：nums = [2,6,4,8,10,9,15]
//    输出：5
    int findUnsortedSubarray(vector<int>& nums) {
        if (nums.size() <= 1) return 0;
        
        int count = 0;
        int interval_start = -1;
        int interval_end = 0;
        int interval_min = 0;
        int interval_max = 0;
        // 一轮循环构造几个关键点变量
        for (int i = 1; i < nums.size(); i ++) {
            if (nums[i] < nums[i - 1]) {
                if (interval_start == -1) {
                    // 初始化
                    interval_start = i - 1;
                    interval_min = nums[i];
                    interval_max = nums[i - 1];
                }
                interval_end = i;
            }
        }
        if (interval_start == -1) {
            return 0;
        }
        // 二轮循环寻找区间内最大最小值
        for (int i = interval_start; i <= interval_end; i ++) {
            if (nums[i] > interval_max) {
                interval_max = nums[i];
            }
            if (nums[i] < interval_min) {
                interval_min = nums[i];
            }
        }
        // 三轮循环延展开始边界
        for (int i = interval_start - 1; i >= 0; i --) {
            if (nums[i] > interval_min) {
                interval_start --;
            }
        }
        for (int i = interval_end + 1; i < nums.size(); i ++) {
            if (nums[i] < interval_max) {
                interval_end ++;
            }
        }
        if (interval_end != interval_start) {
            count = interval_end - interval_start + 1;
        }
        
        return count;
    }
};

#endif /* BFile_hpp */
