一.题目链接：https://leetcode.com/problems/longest-increasing-subsequence/

二.题目大意：

　　给定一个没有排序的数组，要求从该数组中找到一个最长的递增子序列，并返回其长度。(递增子序列可以是不连续的)

三.题解：

　　寻找最长递增子序列问题 (LIS)，是一道比较经典的问题，该问题的解法也比较多，此处我只用了两种方法实现，所以不本无也主要陈述这两种算法。

方法1：

利用动态规划解决 (最容易想到的算法)，时间复杂度为O(N^2)，空间复杂度为O(N)，基本思想如下：

(1)定义一个数组dp，其中dp[i]表示nums数组中，以nums[i]为结尾的最长递增子序列的长度。dp数组的所有元素的初值为1。

(2)接下来对dp数组进行维护更新，从nums的首元素nums[0]开始遍历，对所有排在nums[i]元素之前的元素,如果d[j]+1>dp[i]d[j]+1>dp[i]，则dp[i]=dp[j]+1dp[i]=dp[j]+1，所以状态转方程为

dp[i]={max{dp[i],dp[j]+1},dp[i],j<ij≥i
dp[i]={max{dp[i],dp[j]+1},j<idp[i],j≥i

(3)在dp数组的更新过程中，记录其最大的元素值，最终结果即该值。

代码如下：
class Solution
{
public:
    int lengthOfLIS(vector<int>& nums)
    {
        int len = nums.size();
        int rs = 0;
        if(len == 0)
            return 0;
        vector<int>dp(len,1);//初始化dp数组
        for(int i = 0; i < len; i++)
        {
            for(int j = 0; j < i; j++)
                if(nums[i] > nums[j])
                    dp[i] = max(dp[i],dp[j] + 1);//更新当前位置元素的dp
            rs = max(rs,dp[i]);//每次更新dp[i]时，记录最大值
        }
        return rs;
    }
 
};
 

方法2：

利用二分查找的思想，时间复杂度为O(NlogN)，空间复杂度为O(N)。该算法的想如下：

(1)定义一个tail数组，其中tail[i]表示数组nums中长度为i+1的递增子序列中末尾元素最小的那个子序列的末尾元素，例如：

 

1 len = 1   :      [4], [5], [6], [3]   => tails[0] = 3
2 len = 2   :      [4, 5], [5, 6]       => tails[1] = 5
3 len = 3   :      [4, 5, 6]            => tails[2] = 6
(2)很显然，tail数组一定是个递增的有序数组，tail数组的初始大小为1，初始元素我们定义为nums[0] (也可以定义为nums中其他值,但最好是nums[0]，因为数组的长度可能为1)，对于其更新过程，详细如下：

1.遍历数组nums中的每一元素nums[i]，如果nums[i] < tail[0]的话，令tail[0] = nums[i]；

2.如果 nums[i] 大于taIl数组的租后一个元素的话 (由于tail数组时递增的，相当于大于tail数组中所有的元素)，此时将tail数组的size加1，并令nums[i]为tail数组中新的尾元素。

3.如果nums[i]不满足1和2中的情况的话，那就利用二分法从tail数组中找到处第一个大于nums[i]的元素的位置 (假设为K),则更新tail数组，令tail[K] = nums[i]。

最终tail数组的大小，就是最长递增子序列的长度 (根据tail数组所表示的意思可知)，但是tail数组中的元素构成的序列并不一定是一个最长递增子序列，只是数组大小等于LIS的长度而已。

具体的代码如下：
class Solution
{
public:
    int lengthOfLIS(vector<int>& nums)
    {
        int len = nums.size();
        if(len == 0)
            return 0;
        vector<int>tail;
        tail.push_back(nums[0]);//初始化tail数组，一开始长度为1
        for(int i = 0; i < len; i++)
        {
            if(nums[i] < tail[0]) //更新tail数组首元素
                tail[0] = nums[i];
            else if(nums[i] > tail.back())//更新tail数组尾元素
                tail.push_back(nums[i]);
            else//更新tail1数组其他位置的元素，即找到第一个大于等于nums[i]的元素
            {
                int left = 0, right = tail.size() - 1;
                while(left <= right)//利用二分法找到第一个大于等于nums[i]的元素的位置，并进行更新
                {
                    int mid =left + (right - left) / 2;//防止溢出
                    if(tail[mid] >= nums[i])
                        right = mid - 1;
                    else
                        left = mid + 1;
                }
                tail[left] = nums[i]; //left即第一个大于等于nums[i]的元素的位置
        }
        }
        return tail.size();//最终tail数组的大小即所求的结果
    }
 
};
注：此处的tail数组实质为一个动态数组，所以用vector来实现最好不过了。

参考：https://leetcode.com/problems/longest-increasing-subsequence/discuss/74824/JavaPython-Binary-search-O(nlogn)-time-with-explanation
