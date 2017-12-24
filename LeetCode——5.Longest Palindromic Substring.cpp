一.题目链接：https://leetcode.com/problems/longest-palindromic-substring/

二.题目大意：

　　给定一个字符串，找出它最长的回文子串。例如，字符串“caabb”，它的最长回文子串为“aabb”。

三.题解：

　　找最长回文子串应该说是比较经典的题目，这个题目我目前有三种思路：

方法1：暴力解决，找出所有的子串，并判断子串是不是回文，然后记录最长的回文子串。代码如下：
class Solution {
public:
    string longestPalindrome(string s) {
        int len = s.size();
        string rs;//用于保存最长的回文子串
        int max_len = 0;
        for(int i = 0;i < len;i++)
            for(int j = i + 1;j <= len;j++)
        {
          string temp = s.substr(i,j - i);
 
            if(isPalin(temp) == true)
            {
                if(max_len < temp.size())
                {
                    max_len = temp.size();
                    rs = temp;
                }
            }
        }
    return rs;
    }
    bool isPalin(string s)
    {
        int len = s.length();
        int flag = 1;
        for(int i = 0;i < len;i++)
        {
            if(s[i] != s[len - 1 - i])
                flag = 0;
        }
        if(flag)
            return true;
        return false;
    }
 
};
中遍历所有的子串需要的时间复杂度为O(n2),判断子串是不是回文串的时间复杂度为O(n)，所以总的时间复杂度为O(n3)。

提交结果:Time Limit Exceeded(超时).

方法2：

　　以字符串中的每个字符为中心向两边扩展，从而找到最长的回文子串。其中回文子串存在两种情况：(1)形如"aabaa"这种中间只有一个字符的回文子串。(2)形如"aabbaa"这种中间有两个或多个字符的回文子串。所以在处理的时候，先优考虑第二种情况，可以吧第二中情况中的中间重复字符看成一个字符，然后剩下的部分同第一种情况就可以进行相同的处理了。代码如下：
  class Solution {
public:
    string longestPalindrome(string s) {
        int len = s.size();
        int max_len = 0;
        string rs = "";
        for(int i = 0;i < len;i++)
        {
            int f = i,b = i;
            int df = 0;
            int oddf = 0;
            while(s[b] == s[i])//中间字符存在重复的情况
            {
                b++;
                oddf = 1;
            }
            if(oddf == 1)
                b--;
            while(f >= 0 && b < len && s[f] == s[b])//中间字符的左右两边字符相等，两边都增长
            {
                f--;
                b++;
                df = 1;
            }
            if(df == 1)
            {
                f++;
                b--;
            }
            string temp = s.substr(f,b-f+1);
            if(max_len < temp.size())
            {
                max_len = temp.size();
                rs = temp;
            }
 
        }
        return rs;
}
};
这个程序中的我设置了两个哨兵，用来判断是否发生了以下情况：

(1)中间字符连续几个都相同或重复，此时下标b增加。

(2)中间字符的左右两边字符相等，所以两边都增长，此时b增加，f减小。

由于每次增长后，下标f(或b)都会再次-1(+1)，相当于多减少(增加)了一次，所以需要增加(减少)一次，来恢复成为正常的下标。　

这种方法的时间复杂度为O(n2)，空间复杂度为O(n)。

提交结果：Accepted(16ms).

方法3：

　　利用动态规划的思想，将父问题拆分为若干个子问题，用dp[i][j]来表示字符串下标为[i,j]的子串是否为回文串，那么有以下的分析：

(1)如果i == j表示子串是一个字符，那么此时必然是一个回文串。

(2)如果相邻的字符相等(这种情况实质就是方法2中的中间字符重复的情况)，j == i+1，此时要判断s[i]与s[j]是否相等，如果相等，那么该子串也是回文串，

(3)判断剩下的情况，如果(s[i],s[i+1],.....,s[j])为回文串的话，那么(s[i+1],s[i+2],.....s[j-1])必然也是一个回文串，且s[i] == s[j]。

所以，初始状态为：

dp[i][i] =1。

整个状态方程为：
(http://images2017.cnblogs.com/blog/553062/201712/553062-20171205172239503-1372195011.png)
代码如下：
class Solution
{
public:
    string longestPalindrome(string s)
    {
        int len = s.size();
        string rs = "1";
        int start = 0;
        int max_len = 1;//此处的初始值为1，默认为dp[i][i]
        int dp[1000][1000]= {0};
        for(int i = 0; i < len; i++)
        {
            dp[i][i] = 1;//初始状态，在求解前必须初始化
            for(int j = 0; j < i; j++)
            {
 
                 if(i == j+1)
                {
                    if(s[i] == s[j])
                        dp[j][i] = 1;
                }
                else
                {
                    if(s[i] == s[j])
                    {
                        dp[j][i] = dp[j+1][i -1];
                    }
                }
                if(dp[j][i] && max_len < (i - j +1))
                {
                    max_len = (i - j +1);
                    start = j;
                }
            }
        }
        rs = s.substr(start,max_len);
        return rs;
    }
 
};
这种方法有需要注意的几点：

(1)最大长度的初始值为1，而不是0，默认为dp[i][i]这种形式。

(2)由于求解父问题实质，是将父问题分解成为若干个子问题，所以子问题必须被解决，才能求解父问题。所以，一定要利用初始状态对dp进行初始化，即dp[i][i]=1。(动态规划类问题都要初始化初始状态)

(3)在这个程序中，利用dp[j][i]来代替理论上的dp[i][j]，这是因为第一层for循环还没取到所有值的时候，第二层for循环已经取了所有可能的值了，这就可能导致子问题还没解决，就去求解父问题了。例如：

求dp[0][4]时，需用到dp[1][3]，如果用常规的for循环的话，i=1肯定比i=0出现的晚，导致父问题求解出错。(这可以看成动态规划类问题的常用的技巧)

提交结果：Accepted( 212 ms). 比方法2慢好多...

========================================经查知，还有一种更优的算法============================================================================================================================
详细可见我的博客：http://www.cnblogs.com/wangkundentisy/p/7977488.html
