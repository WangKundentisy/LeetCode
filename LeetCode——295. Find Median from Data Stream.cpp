一.题目链接：

　　https://leetcode.com/problems/find-median-from-data-stream

二.题目大意：

　　给定一段数据流，要求求出数据流中的中位数，其中数据流是动态变化的。如果数据流中的数字个数是奇数的话，则中位数是中间位置的数字；如果数据流中的数字是偶数的话，则中位数是排序好的数据流中的中间两个数的的平均值。

三.题解：

　　如果数据流是静态不变的话，此时问题是比较好求解的。但是数据流是动态变化的，所以数据流中每次进入一个新的数字时，都要保证能够高效的找到数据流的中位数。我们可以这么考虑：如果把数据流中的数字分为个数相同的两部分的话(假设为A和B，其中A中的数字全部小于B中的数字)，那么我们所求的中位数，实质就是A中的最大值和B中的最小值的平均值。因此，我们可以用两个堆来表示这个过程，其中大顶堆maxH存储的是数据流中的数值较小的数字，而小顶堆minH存储的是数据六中数值较大的数字，且maxH中的数字全部小于minH中的数字。并且堆可以快速的找出其中的最值，所以可以快速找得到minH中的最小值和maxH中的最大值，从而求出中位数。代码如下：

#include<iostream>
#include<unordered_map>
#include<queue>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<sstream>
#include<set>
#include<map>
#include<stack>
#define MAX_NUM 100
using namespace std;
class MedianFinder {
public:
    /** initialize your data structure here. */
    priority_queue<int,vector<int>,less<int>> maxH;//定义大顶堆，用于存储较小的数据部分
    priority_queue<int,vector<int>,greater<int>> minH;//定义小顶堆，用于存储较大的数据部分
    MedianFinder() {
 
    }
 
    void addNum(int num) {
        maxH.push(num);
        int tmp = maxH.top();
        maxH.pop();
        minH.push(tmp);//保证小顶堆中的数据大于大顶堆中的数据
        if(minH.size() > maxH.size())
        {
            int tmp = minH.top();
            minH.pop();
            maxH.push(tmp);//保证大顶堆中的数据小于小顶堆中的数据
        }
 
    }
 
    double findMedian() {
        if(minH.size() == maxH.size())//如果两个堆的大小相同，则返回它们最值的平均值
            return (minH.top() + maxH.top()) / 2.0;
        return minH.size() > maxH.size() ? minH.top() : maxH.top();//如果两个堆的大小不相同，返回数字个数多的堆的最值
    }
};
 
/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder obj = new MedianFinder();
 * obj.addNum(num);
 * double param_2 = obj.findMedian();
 */
 
 
int main()
{
    MedianFinder test = MedianFinder();
    test.addNum(1);
    test.addNum(2);
    test.addNum(3);
    test.addNum(4);
    test.addNum(5);
    cout<<test.findMedian()<<endl;
 
 
}
每次从数据流中找出中位数的时间为O(1),调整两个堆的时间为O(logN),对于含有n个数字的数据流，总的时间复杂度为O(NlogN),空间复杂度为O(N)。

此外，有几个点需要注意下：

1.代码中使用了priority_queue即优先队列来实现堆，因为优先队列获取优先级最高的值所需时间为O(1),调整的过程为O(logN),与堆的操作时间类似，能较好的模拟堆。

2.通常情况下，堆默认的优先级最高的值是指的最大值，也可以是最小值，不过需要显式的说明(见本例中优先队列的定义)。

3.要保证最小堆中存储的始终是较大的数值，而大顶堆中存储的是较小的数值。所以才会有addNu中的那些操作。
