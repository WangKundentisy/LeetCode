一.题目链接：

　　https://leetcode.com/problems/letter-combinations-of-a-phone-number/

二.题目大意：

　　给定一段数字字符串，其中每个数字字符对应了如下的字母字符，求出输入字符串对应的所有可能的字母字符串集合。

　　例如，输入数字字符串"23",其对应的所有可能的字母字符串集合为 ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"]

三.题解：

　　这道题目直接根据题意来做即可，相当于每个数字字符对应若干个字母字符，把这些所有可能的字母组合存储起来即可，本体代码如下 (本题的思想不难理解，关键是这个实现的过程，需要仔细琢磨下)：

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        string dic[] = {"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
        vector<string> res;
        if(digits == "")
            return res;
        res.push_back("");//初始化结果数组
        int d_len = digits.size();
        for(int i = 0; i < d_len; i++)
        {
            vector<string> tmp;//用于扩充结果的中间变量
            string str = dic[digits[i] - '0'];
            if(str == "")
                continue;
            for(int j = 0 ; j < str.size(); j++)
                for(int k = 0; k < res.size(); k++)
                    tmp.push_back(res[k] + str[j]);//对res数组的每个元素附上新的字母字符
            res = tmp;//每次中间处理完之后，交换结果
        }
        return res;
    }
};
注意：

1.当输入的数字字符串为空时，最终返回的字符字符串集合为空，所以这里需要特判一下。

2.初始时res数组必须有一个“”，这样做的目的是为了方便后续将res数组进行扩充，因为后续的扩充操作实际上就是在res数组原有的每个元素基础上附加上新的字母字符，并且这个过程由tmp数组来实现，最终将tmp数组的结果赋值给res数组作为最终的结果。
