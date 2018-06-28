一.题目链接：https://leetcode.com/problems/4sum/

二.题目大意：

　给定一个数组A和一个目标值target，要求从数组A中找出4个数来使之构成一个4元祖，使得这四个数的和等于target，找出所有的四元组，当然这些四元组不能有重复的。

三.题解：

这道题实质就是3sum的变形，关于4sum问题，已经在https://www.cnblogs.com/wangkundentisy/p/9079622.html这里说过了，无外乎最外面两层循环，最里面的循环使用哈希表或者双指针，此处使用的是双指针法。具体代码如下：
class Solution
{
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target)
    {
        int len = nums.size();
        vector<vector<int>> rs;
        if(len < 4)
            return rs;
        sort(nums.begin(),nums.end());
        for(int i = 0; i < len; i++)
        {
            if(i != 0 && nums[i] == nums[i - 1])
                continue;
            for(int j = i + 1; j < len - 1; j++)
            {
                if(j != i + 1 && nums[j] == nums[j -1])//注意此处的去重，要保证j不是第一次被使用，所以必须是j!=i+1
                    continue;
                int l = j + 1, r = len - 1;
                while(l < r)
                {
                    if(nums[i] + nums[j] + nums[l] + nums[r] == target)
                    {
                        rs.push_back({nums[i],nums[j],nums[l],nums[r]});
                        l++;
                        r--;
                        while( l < r && nums[l] == nums[l - 1])
                            l++;
                        while(l < r && nums[r] == nums[r + 1])
                            r--;
                    }
                    else if(nums[i] + nums[j] + nums[l] + nums[r] < target)
                        l++;
                    else
                        r--;
 
                }
            }
        }
        return rs;
 
    }
};
本例中的方法的时间复杂度为O(N^3),空间复杂度为O(1)。此外，之前在3sum问题中总结过：4sum问题还有时间复杂度为O(N^2)的算法，具体可见：https://www.cnblogs.com/wangkundentisy/p/9079622.html

这里有几点需要注意：

1.由于题目要求四元组是唯一的，所以要进行去重：每一个外层循环都需要去重，即i和j都要去重(对于ksum问题，也是这样的，k-1个外层循环都要按照这个规律进行去重)。

2.外层循环的去重，要保证此处的指针不是第一次被使用，也就是说在该位置之前，应该确保已经执行过一次了(如果是第一次使用，就不用去重了)，所以才用 i != 0和 j != i + 1这种判断条件，对于ksum问题，一定注意这种规律。
