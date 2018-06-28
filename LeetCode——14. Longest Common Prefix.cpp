一.题目链接：https://leetcode.com/problems/longest-common-prefix/

二.题目大意：

　　给定若干个字符串，找出它们的最长公共子串。

三.题解：

　　这道题目应该是一道典型题目，需要着重掌握的。该题目的解法并不是很难，代码最好精简化。本题有两种思路：

1.纵向扫描

　　任意选出一个字符串(一般都是选择第一个字符串)，从该字符串的第一个字符起，与剩余所有的字符串的相应位置的字符比较，若出现相应位置字符不同的情况，则立即返回之前匹配成功的前缀。

代码如下：
class Solution
{
public:
    string longestCommonPrefix(vector<string>& strs)
    {
        int len = strs.size();
        if(len == 0)//判断特殊情况
            return "";
        int s_len = strs[0].size();
        for(int i = 0; i < s_len; i++)
            for(int j = 1; j < len; j++)
              {
                if(strs[j][i] != strs[0][i])
                    return strs[0].substr(0,i);
              }
        return strs[0];
    }
};
该方法有几点需要注意：

(1).特殊情况(即vector为空的情况)一定要考虑(字符串相关的题目，为空的情况是一定要考虑的，切记！)，对于每个字符串为空的情况，就不用单独考虑了(在两个for循环中就已经解决这种情况了)。

(2).该算法的时间复杂度为O(n1+n2+...)，空间复杂度为O(1).

2.横向扫描

　　把所有的字符串与第一个字符串进行比较，选出两者相同的部分，并选取长度最短的部分作为最终结果。这种方法的时间复杂度与纵向扫描在同一数量级的。
