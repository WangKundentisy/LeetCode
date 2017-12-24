一.题目链接：https://leetcode.com/problems/palindrome-number/

二.题目大意：

　　给定一个整数，判断它是否为一个回文数。(例如-12，它就不是一个回文数；11它是一个回文数)

三.题解：

　　这道题目我一共用了两种解法：

方法1：将数字转化成字符串，然后首尾对应判断每个字符即可，代码如下：
class Solution {
public:
    bool isPalindrome(int x) {
        bool rs = true;
        stringstream ss;
        ss<<x;
        string str = "";
        str = ss.str();
        int len = str.size();
        int flag = 0;
        for(int i = 0 ; i < len; i++)
        {
            if(str[i] == str[len -1 -i])
                    ;
            else
                flag = 1;
        }
        if(flag == 1)
            rs = false;
        return rs;
 
    }
};
这个是比较容易想到的方法，时间复杂度为O(n)，空间复杂度为O(n)。

方法2：

该方法与第7题(7. Reverse Integer)的思想类似，从数字的末位开始相当于反转数字，反转的过程中如果反转的值和剩余的数字相同的话，那么它就是一个回文数字。代码如下：
class Solution {
public:
    bool isPalindrome(int x) {
        bool rs = true;
        int sum = 0;
        int temp = 0;
        if(x < 0)
            return false;
        if(x >= 0 && x <=9)
            return true;
        if(x % 10 == 0)
            return false;
        while(x)
        {
            sum = sum *10+ x % 10;
            x /= 10;
            temp = x / 10;
            if(temp && sum == temp)
                return x;
            if(sum == x)
                return true;
        }
        return false;
 
    }
};
该方法的时间复杂度为O(n)，空间复杂度为O(1)。此方法有几处需要注意的点：

1.负数的话，一定不是回文数字。

2.该数字能够整除10的话，那么它也一定不是回文数字。(例如：1122110，如果直接执行while语句的部分的话，那么就会把它判断为回文数；而实际上它并不是回文数)

3.while语句中用了两个判断，其中sum == x是用于判断偶数位的情况(例如：1221)；而sum == temp是用于判断奇数位情况的(例如：12321)，此处一定注意两种情况都需要考虑！

4.对于x=0的情况，和x为一位数的情况，由于我while循环的条件是x不等于0并且循环体里面对单位数字无效；所以这两种情况单独讨论。

5.此处还有另一种方法，就是while循环体改造成如下的形式：
class Solution {
public:
    bool isPalindrome(int x) {
        bool rs = true;
        int sum = 0;
        int temp = 0;
        if(x < 0 || (x && x % 10 == 0))//x不为0
            return false;
        if(x == 0)
            return true;
        while(x)
        {
            sum = sum *10+ x % 10;
            if(sum == x)
                return true;
            x /= 10;
            if(sum == x)
                return true;
        }
        return false;
 
    }
};
　相当于x在整除10前后都与sum比较，在x整数10之前与sum比较也能解决奇数位数字的情况；但一开始的判断条件需要变一下。
