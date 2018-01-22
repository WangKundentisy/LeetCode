一.题目链接：https://leetcode.com/problems/regular-expression-matching/

二.题目大意：

　　实现一个正则表达式，该正则表达式只有两种特殊的字符——“.”和“*”，其中.能表示任意字符，即它可以匹配任意的字符；*表示可以重复前面的字符0次或者多次(例如：a*可以表示成“”(空，相当于重复0次)或者表示成“aaa”重复3次)。

三.题解：

　　这道题目比较常用的方法是递归；该题目的难点之处在于遇到*的时候它可能匹配0次，也可能匹配1次或多次；这种特性很显然满足递归的特性。所以要根据字符是否为*来进行分情况讨论，详细如下：

对于一个模式字符串，从前往后的来分析它：

1.如果当前字符的下一个字符不是“*”的话(由于第一个字符不可能是* 所以根据下一个字符是否为*来分情况才更加的合理)，此时只需要判断需匹配字符串s的当前字符和模式字符串p的当前字符是否相等即可。如果*s == *p或者*p == '.' && *s != '\0'的话，那么当前字符匹配成功，就可以继续往下匹配了。

2.如果当前字符的下一个字符是“*”的话，此时就需要匹配当前字符0次、1次或多次了(而此处的重复次数可以用递归法来实现，也可以用迭代法来实现)，直到不能匹配更多的字符。

3.既然是递归，那么一定·要有终止条件的，该问题的终止条件显然是：当p到达终点时(即*p == '\0'时)如果s也到达终点了，那么返回true；如果s没到达终点，那么返回false。通过这个条件我们也可以看出，字符串p的最终长度一定是与字符串s的长度一样，才能够匹配成功。(这也就是题目时所说的完全匹配，而不是部分匹配。通过这一点，我们可也快速的去除那些不符合匹配的例子，如：ab和.*c,两者显然不匹配；而ab和.* 两者显然匹配)

具体代码如下：

方法1(递归+部分迭代)：
class Solution {
public:
    bool isMatch(string s, string p) {
        return matchCore(s.c_str(),p.c_str());
    }
    bool matchCore(const char *s,const char *p)
    {
        if(*p == '\0' && *s == '\0')
            return true;
        if(*p == '\0' && *s != '\0')
            return false;
        //如果下一个字符不是*的话
        if(*(p+1) != '*')
        {
            if(*p == *s||(*p == '.' && *s != '\0'))
                return matchCore(s + 1,p + 1);
            else//一旦有一个字符不一样，则不匹配
                return false;
        }
        else//下一个字符是*
        {
            //*重复一次或多次，只有当当前字符匹配成功时，才考虑*重复多少次，否则不用考虑*了，直接跳过
            while(*p == *s ||(*p == '.' && *s != '\0'))
            {
                if(matchCore(s,p + 2))
                    return true;
                s++;
            }
            //*不再重复，即直接跳过*
            return matchCore(s,p + 2);
        }
 
    }
};
注:

1.该方法中while循环的部分相当于对*进行匹配1次或多次，而matchCore(s,p+2)相当于忽略* ，即匹配0次。下面来详细阐述一下此处过程：

(1)首先，先判断p和s的当前字符是否相同，如果不相同的话，* 这个字符就可以忽略了，相当于匹配0次，即执行matchCore(s,p+2)；

(2)如果p和s的当前字符相同的话，此时要考虑对*进行处理了，即匹配0次、1次还是多次？首先先尝试匹配0次，如果匹配0次的话，p和s的剩下部分都相匹配的话，那么直接就可以返回true了，if(machCore(s,p+2) retrun true;这两行代码就是这个意思。如果匹配0次的话不可行怎么办？此时就是s++相当于匹配1次(如果if(matchCore(s,p+2)这个条件成立的话，相当于匹配1次就成功了)，匹配一次完之后再进行判断p和s的当前字符是否相同，然后重复之前的过程；这样就完成了匹配0次、1次或多次这整个过程。

2.一定要注意递归函数的终止条件！！

3.此处有个c++方法需要注意，即string.c_str()的用法，它的功能是将一个string类型的字符串转换成一char *字符串。

方法2(全部递归)：
class Solution {
public:
    bool isMatch(string s, string p) {
        return matchCore(s.c_str(),p.c_str());
    }
    bool matchCore(const char *s,const char *p)
    {
        if(*p == '\0' && *s == '\0')
            return true;
        if(*p == '\0' && *s != '\0')
            return false;
        //如果下一个字符不是*的话
        if(*(p+1) != '*')
        {
            if(*p == *s||(*p == '.' && *s != '\0'))
                return matchCore(s + 1,p + 1);
            else//一旦有一个字符不一样，则不匹配
                return false;
        }
        else//下一个字符是*
        {
 
            if(*p == *s || (*p == '.' && *s != '\0'))//只有当当前字符匹配成功时，才考虑*重复多少次，否则不用考虑*了，直接跳过
                return matchCore(s,p + 2) || matchCore(s + 1,p + 2) || matchCore(s + 1,p); //*重复0次、一次或多次
            else
                return matchCore(s, p + 2);
        }
 
    }
};
注：

全部递归的话，比之前的"递归+迭代"法满了不少，方法1用了23ms，但方法2(本方法)用了731ms。所以能不用递归就不用递归，这句话是很有道理的；但递归法写的代码确实看上去更加容易理解，虽然相比迭代有时会爆栈或超时(超时很有可能是添加了多余的操作，有时这种多余的操作并不那么的明显)

方法3(全部递归-优化)：
class Solution {
public:
    bool isMatch(string s, string p) {
        return matchCore(s.c_str(),p.c_str());
    }
    bool matchCore(const char *s,const char *p)
    {
        if(*p == '\0' && *s == '\0')
            return true;
        if(*p == '\0' && *s != '\0')
            return false;
        //如果下一个字符不是*的话
        if(*(p+1) != '*')
        {
            if(*p == *s||(*p == '.' && *s != '\0'))
                return matchCore(s + 1,p + 1);
            else//一旦有一个字符不一样，则不匹配
                return false;
        }
        else//下一个字符是*
        {
 
            if(*p == *s || (*p == '.' && *s != '\0'))//只有当当前字符匹配成功时，才考虑*重复多少次，否则不用考虑*了，直接跳过
                return matchCore(s,p + 2) || matchCore(s + 1,p); //*重复0次、一次或多次
            else
                return matchCore(s, p + 2);
        }
 
    }
};
方法3相比方法2，主要是优化了一处，即

1
return matchCore(s,p + 2) || matchCore(s + 1,p + 2) || matchCore(s + 1,p);
变成了

1
return matchCore(s,p + 2) || matchCore(s + 1,p);
因为仔细想想，重复多次是由多个重复1次组成的啊，所以最终不用再强调重复一次了，直接用matchCore(s+1,p)既可以表示重复1次也可以表示成重复多次。

那么去除这一步后，耗时多少呢？是26ms！！可见递归并不比迭代慢，主要是是否不增加多余的操作。话说，做到这一步心里很是挺爽的~~
