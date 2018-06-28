一.题目链接：https://leetcode.com/problems/roman-to-integer/

二.题目大意：

　　给定一个罗马数字，返回它的整数形式。

三.题解：

　　这道题与12题恰好相反，关键之处在于罗马数字的组成规律。首先，弄清楚每个罗马字母对应的数字大小：

       

实质上，对于一个罗马数字，只需遍历它的每个字母，然后将字母对应的数字逐一相加即可，但是如果后一个字母对应的数字比相邻的前一个字母对应的数字大的话，那么这两个字母对应的数值实际上是大的数字减去小的数字，而不是两个数字的和。举个例子：例如MCM，它有两个需要特别注意的地方：

1.CM对应的数值实际上是M-C，即1000-100 = 900.

2.由于在遍历判断的时候，C会多加上一次，所以在遇到类似"CM"的情况时，需要用M-2*C，把多加的那个C减去。

代码如下：
class Solution {
public:
    int romanToInt(string s) {
    int len = s.size();
    unordered_map<char,int> mp;
    mp.insert(pair<char,int>('I',1));
    mp.insert(pair<char,int>('V',5));
    mp.insert(pair<char,int>('X',10));
    mp.insert(pair<char,int>('L',50));
    mp.insert(pair<char,int>('C',100));
    mp.insert(pair<char,int>('D',500));
    mp.insert(pair<char,int>('M',1000));
    int val = mp.find(s[0])->second;
    for(int i = 1; i < len; i++)
    {
        if(mp.find(s[i])->second > mp.find(s[i - 1])->second)
        {
            val += (mp.find(s[i])->second - 2 * mp.find(s[i - 1])->second);
        }
        else
        {
            val += mp.find(s[i])->second;
        }
 
    }
    return val;
 
 
    }
};
　此处我是从下标1处开始遍历的，由于是判断s[i] >s[i-1],所以会出现多加一次C的情况，所以才会减去2*C。
