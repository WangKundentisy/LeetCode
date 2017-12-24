一.题目链接：https://leetcode.com/problems/reverse-integer/

二.题目大意：

　　给定一个整数，要求反转该整数之后再返回；如果归返回的整数超过了int型整数的表示范围，则返回0。例如：输入123，返回321。

三.题解：

　　这道题目在思路上并不难，主要还是在代码的实现上，这里我主要有两种实现方式。

方法1：将数字转换成字符串，然后计算出该字符串的长度，根据长度和字符来生成一个反转后的数字。代码如下：
class Solution {
public:
    int reverse(int x) {
 
        stringstream ss;//通过stringstream将int转化成string
        ss<<x;
        string str = ss.str();
        int len = str.size();
        int pos[len] = {0};
        int num = -1;//根据字符的位置来决定乘以10的num次方
        long temp = 0;
        int flag = 0;//用于标记是否为负数
        for(int i = 0; i < len; i++)
        {
            if(str[i] == '-')
            {
                flag = 1;
                continue;
            }
 
            else
            {
                num++;
                temp += ((str[i] - '0') *pow(10,num));
            }
 
        }
 
        if(flag == 1)
            temp = -1*temp;
        if(temp > (pow(2,31) -1) || temp < -pow(2,31))
                temp = 0;
        return temp;
    }
};
此方法时间复杂度为O(n)，空间复杂度为O(n)。

方法2：该方法是直接对整数x进行处理，每次利用x%10来求x的个位的数字，利用x/10来求剩余部位的数字，并利用个位数字进行迭代。代码如下：
class Solution {
public:
    int reverse(int x) {
        long long  num = 0;
        while(x)
        {
             num = num * 10 + x % 10;
             x /= 10;
        }
        return (num > INT_MAX || num < INT_MIN)?0:num;
 
    }
};
这种方法的关键在于：num = num * 10 + x % 10这一步骤，实际上就是每次利用x的个位的数字当做反转后数字的高位数，此处的思想还是非常巧妙的，很值得借鉴！此方法的时间复杂度为O(n),空间复杂度为O(1)。对于此方法有几点需要注意：

1.这种方法，不用区分正负数，因为如果x为负数的话，不论是他的余数还是整除后的结果都是负数。例如-123对10取余数的话，那么结果是-3；整除10的话，结果是-12。

2.此方法，不用预先知道x的位数，每次迭代，上次的个位数就会乘以10(高上1位)，这次的个位数就会变成反转后数字的个位数字；所以说这种思想(也可以认为一种技巧)一定要掌握。尤其是”它不用事先知道x的位数”这个重要的性质，以后很可能用得着。
