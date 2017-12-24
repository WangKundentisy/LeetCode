一.题目链接：https://leetcode.com/problems/string-to-integer-atoi/

二.题目大意：

　　实现一个和C语言里atoi具有相同功能的函数，即能够把字符串转换成整型。例如：输入字符串“-123”，返回值为一个整数-123。

三.题解：

　　这道题也属于字符串处理类的题目，只要看懂题目所给定的规则就好了，题目给的规则大致如下：

1.若一开始遇到连续的2空白字符，则忽略这些字符，直到遇到第一个非空白字符。

2.若遇到的第一个空白字符为'+'或者'-',则只有下一个字符为数字字符时才继续执行，否则返回0。如果下一个字符为数字字符，那么就往后顺序判断字符是否为数字字符，直到遇到非数字字符(然后该字符之后的字符串就不用考虑了)。

3.若遇到的第一个非空白字符为数字字符，则执行与第2步相同的操作，即往后顺序判断字符是否为数字字符，直到遇到非数字字符(然后该字符之后的字符串就不用考虑了)。(实际上相当于第一个出现的数字字符串)

4.如果数字字符串转换成的数字大于INT_MAX(int所能表示的最大值)，或者小于INT_MIN(int所能表示的最小值)的话,则返回INT_MAX或者INT_MIN。

这里有需要注意的一点是：这道题不用考虑小数的问题，因为题目要求转化的是整型，不包括浮点型！！！

看懂这道题目给定的规则后，实现就简单了，代码如下：
class Solution
{
public:
    int myAtoi(string str)
    {
        int len = str.size();
        long long rs = 0;
        int i = 0;
        int flag = 1;//表示正负号
        while(i < len && str[i] == 32)
        {
            i++;
        }
        if(str[i] == '+')
        {
            flag = 1;
            i++;
            while(str[i] >= '0' && str[i] <= '9')
            {
                rs = rs * 10 + str[i] - '0';
                i++;
                if(rs > INT_MAX)
                    break;
            }
 
        }
        else if(str[i] == '-')
        {
            flag = -1;
            i++;
            while(str[i] >= '0' && str[i] <= '9')
            {
                rs = rs * 10 + str[i] - '0';
                i++;
                if(rs > INT_MAX)
                    break;
            }
        }
        else if(str[i] >= '0' && str[i] <= '9')
        {
            while(str[i] >= '0' && str[i] <= '9')
            {
                rs = rs * 10 + str[i] - '0';
                i++;
                if(rs > INT_MAX)
                    break;
            }
        }
        else
            return 0;
        rs = rs *flag;
        if(rs > INT_MAX)
            return INT_MAX;
        else if(rs < INT_MIN)
            return INT_MIN;
        else
            return rs;
    }
 
};
该算法的时间复杂度为O(n),空间复杂度为O(1)，这段代码有几处需要重点理解：

1.字符转数字的操作为：rs = rs * 10 + str[i] - '0'。此处实际上与第7题反转数字(http://www.cnblogs.com/wangkundentisy/p/8059028.html)用了相同的道理，这么做的好处是不用事先知道字符串的长度。

2.在while循环中有一步为：if(rs > INT_MAX)  break;为什么要加这一步？最后的判断不能的代替这一步吗？

确实不能，因为rs 是long long型，这种数据类型占8个字节，它表示的范围也是有限的，所以当超过这个范围时，就会发生溢出，产生错误的返回值(例如：“1212121212121212121212121212121212121212”)。所以在字符串转化的过程中，一旦发现超过int的范围，就终止，就不会发生这种情况了。(之前我想的是把所有的rs都加完之后再考虑，这样就有可能发生上述情况，所以在rs增加的过程中判断才是比较合理的)。
