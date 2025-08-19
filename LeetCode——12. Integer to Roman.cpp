一.题目链接：https://leetcode.com/problems/integer-to-roman/

二.题目大意：

　　给定一个整数，返回它的罗马数字的形式。

三.题解：

　　要想做出这道题目，首先应该弄清楚罗马数字的规律。罗马数字中的任意一个字符连写不会重复出现4次，最多连续出现3次。题目给定的数字范围是1~3999，所以说不用特意去考虑这一点了，按照平常的思路去做就行了。给定一个罗马数字，由于它最多为4位，所以只需拆成个分位、十分位、百分位和千分位即可。对于每个位置的数字对应哪个罗马数字，只要对应起来最后拼成一起即可。代码如下：

class Solution {
public:
    string intToRoman(int num) {
    char* roman[4][10] = {{"","I","II","III","IV","V","VI","VII","VIII","IX"},//个分位的罗马字母
    {"","X","XX","XXX","XL","L","LX","LXX","LXXX","XC"},//百分位的罗马字母
    {"","C","CC","CCC","CD","D","DC","DCC","DCCC","CM"},//十分位的罗马字母
    {"","M","MM","MMM"}};//个分位的罗马字母
    string romanNum;
    romanNum.append(roman[3][num / 1000 % 10]);//千分位
    romanNum.append(roman[2][num / 100 % 10]);//百分位
    romanNum.append(roman[1][num / 10 % 10]);//十分位
    romanNum.append(roman[0][num % 10]);//个分位
    return romanNum;
    }
};
　本题的关键之处在于罗马数字的各个分位的数字如何表示。
