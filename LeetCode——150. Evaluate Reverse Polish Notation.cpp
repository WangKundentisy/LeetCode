一.题目链接：https://leetcode.com/problems/evaluate-reverse-polish-notation/

二.题目大意：

　　给定后缀表达式，求出该表达式的计算结果。

三.题解：

　　对于这道题目，首先观察后缀表达式(逆波兰表达式)的特点，那就是运算符在操作数的后面，所以每遇到一个运算符，只需找到它之前的最近的两个数字作为操作数，然后求出的结果作为一个新的操作数。很显然，可以使用一个栈来存储操作数，每遇到运算符从栈中取出顶端的两个数运算即可，运算结果再入栈。代码如下：

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        if(tokens.empty())
            return 0;
            stack<int> s;
        for(int i = 0; i < tokens.size(); i++)
        {
            if(tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/")
            {
                int a = s.top();
                s.pop();
                int b = s.top();
                s.pop();
                if(tokens[i] == "+")
                    s.push(b + a);
                if(tokens[i] == "-")
                    s.push(b - a);
                if(tokens[i] == "*")
                    s.push(b * a);
                if(tokens[i] == "/")
                    s.push(b / a);
            }
            else
                s.push(stoi(tokens[i]));
        }
        return s.top();
    }
};
该算法的时间复杂度为O(n)；但此处有几点需要注意：

1.该算法的实现并不难，在string转换成int型时，此处利用了stoi()函数，stoi函数能够将string转换成int数字，它与atoi()作用类似，它们有以下几点不同：

(1)stoi()函数的形参是string型，而atoi()函数的形参是char *。

(2)stoi函数默认要求输入的参数字符串是符合int范围的[-2147483648, 2147483647]，否则会runtime error；而atoi函数则不做范围检查，若超过int范围，则显示-2147483648（溢出下界）或者2147483647（溢出上界）。

(3)stoi头文件：<string>,c++函数;而atoi头文件:<cstdlib>,c函数

(我之前是自己写的转换函数，所以代码看起来比较乱，没有上传。。。)

2.string不同于char *，它可以直接用“==”进行比较，例如，string a; if(a == "123") ....；

3.莫忘记所写程序应考虑的三点：边界条件、特殊输入、错误处理。(《剑指offer》 P14)
