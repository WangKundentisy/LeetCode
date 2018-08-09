一.题目链接：

　　https://leetcode.com/problems/find-peak-element/

二.题目大意：

　　给定一个长度为N的一维数组，数组是无序的，要求找到数组中的极大值(或局部最大值)，并返回该极大值的下标，并假设 nums[-1] = nums[n] = -∞.；当某元素同时大于它两边的元素时，则该元素是数组中的一个极大值，数组中若存在多个极大值，则返回任意一个即可。

算法的时间复杂度要求为log级别。

三.题解：

　　这个问题的最直观的解法，就是遍历一遍数组，然后判断每个元素是否符合极大值的条件，但是时间复杂度为O(N)，不符合题目的要求。既然要求是对数级别的时间复杂度，那就不妨利用二分法的思想来查找符合条件的元素。

代码如下：
class Solution
{
public:
    int findPeakElement(vector<int>& nums)
    {
        if(nums.empty())
            return -1;
        int len = nums.size();
        int low = 0;
        int high = len - 1;
        while(low < high - 1)//至少要省出一个中间值来，所以low < high -1
        {
            int mid  = ((high - low) >> 1) + low;//一位运算符的优先级比较低，所以一定加上括号
            if(nums[mid] > nums[mid + 1] && nums[mid] > nums[mid - 1])
                return mid;
            else if(nums[mid] < nums[mid + 1])
            {
                if (low == mid)//特殊情况，必须通过low = mid + 1跳出这种循环
                    low = mid + 1;
                else
                    low = mid;
            }
 
            else
                high = mid;
        }
        return nums[low] > nums[high] ? low : high;//有可能还没找到mid就跳出循环了，此时low和high必有一个满足条件
 
 
    }
};
该算法的时间复杂度为O(logN)，空间复杂度为O(1)，能够满足题目的要求。有几点需要注意：

1.循环的终止条件为low < high -1，因为极大值要同时大于两边的元素，所以至少要有三个值，否则就跳出循环。

2.有种特殊情况，就是low = mid后，再次更新mid的话，low与mid的值还是相同，相当于陷入了死循环，此时通过low = mid + 1跳出死循环。

3.如果在循环中没有返回mid的话，可能数组只有一个元素，也可能只有数组的末尾元素才是极大值，所以最后要判断一下low和high的值，并返回其中较大的。

四.题目扩展：

 如果数组为二维数组的话，如何找到局部最大值(极大值)？

一般有三种方法：直接遍历、利用二分法、利用画圈法(分治)。具体可以参考：https://www.jianshu.com/p/b4f5cb071f04
