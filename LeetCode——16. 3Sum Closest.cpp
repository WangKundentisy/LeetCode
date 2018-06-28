一.题目链接：https://leetcode.com/problems/3sum-closest/

二.题目大意：

　给定一个数组A和一个目标值target，要求从数组A中找出3个数来，使得这三个数的和最接近target。

三.题解：

这道题实质就是3sum(http://www.cnblogs.com/wangkundentisy/p/9079622.html)问题的变形,而且题目假设的是解是唯一的，所以该题甚至都不用考虑重复情况了。所以只需在3sum问题中，判断下三个元素的和与target的差值，并根据差值进行赋值即可。

代码如下：
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int len = nums.size();
        int differ = 0x7fffffff;//初始化差值
        int sum = 0;
        if(len < 3)
            return 0;
        sort(nums.begin(),nums.end());
        for(int i = 0; i < len; i++)
        {
            if(i != 0 && nums[i] == nums[i -1])
                continue;
            int j = i + 1, k = len - 1;
            while(j < k)
            {
                if(nums[i]+ nums[j] + nums[k] == target)
                {
                    return target;//由于题目假设的是解释唯一的，所以如果遇到正好和为target的情况，可以立马返回
                }
                else if(nums[i] + nums[j] + nums[k] < target)
                {
                    int temp = target - (nums[i] + nums[j] + nums[k]);
                    if(temp < differ)//找到离target差异最小的一组数据
                    {
                        sum = nums[i] + nums[j] + nums[k];
                        differ = temp;
                    }
                    j++;
                }
                else
                {
                    int temp = (nums[i] + nums[j] + nums[k]) - target;
                    if(temp < differ)
                    {
                        sum = nums[i] + nums[j] + nums[k];
                        differ = temp;
                    }
                    k--;
                }
            }
        }
        return sum;
    }
};
由于本题基本与3sum问题一致，所以注意事项直接看3sum问题就行了。
