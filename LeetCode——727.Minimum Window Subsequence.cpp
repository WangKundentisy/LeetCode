一.题目链接：https://leetcode.com/problems/minimum-window-substring/

二.题目大意：

　给定两个字符串S和T，要求从S中找出包含T中所有字母的最短子串，同时要求时间复杂度为O(n)。

三.题解：

这道看上去和https://leetcode.com/problems/longest-substring-without-repeating-characters最长不重复子序列类似，似乎都可以利用滑窗法来解决(当然，此处的窗口大小必然是动态的，不固定的)。然而不同的是，S中的字符可能包含T中不存在的字符，也就是说：在滑窗构建的过程中(遍历S的过程中)，会遇到两种情况，当前字符不是T中的字符和当前字符是T中的字符。那么如何构建滑窗呢？具体如下：

(1)我们设置两个指针left和right，分别表示滑窗的两端。哈希表_map用于存储T中出现的字符以及相应的个数。cnt用于统计目前滑窗中出现的T中的字符的个数。

(2)right指针不停的向右移动，并且判断此处的字符是否是T中的字符，是的话，计数器cnt加1，同时_map中相应的字符对应的次数减去1。当cnt的数值与T的长度相同时，表示我们已经构造完成了一个符合条件的滑窗了。

(3)由于，整个S中可能存在多个符合条件的滑窗，所以当我们找到一个符合条件的滑窗时，需要记录相应的长度和起始下标；然后再去构建下一个滑窗。

(4)如何构建下一个滑窗呢？此时，就需要操作左指针left了，将left向右移动，若left处的字符是T中的字符的话，则cnt减去1。相应的_map处的字符对应的次数加1，此时需要构建新的滑窗，再去操作right指针；重复这个过程直至遍历完S。如果left处的字符不是T中的字符的话，继续右移，知道遇到T中的字符。

实现代码如下：
class Solution {
public:
    string minWindow(string S, string T) {
        int s_len = S.size();
        int t_len = T.size();
        if(s_len == 0 || t_len == 0 || s_len < t_len)//特殊输入的处理
            return "";
        int cnt = 0;//用于统计当前滑动窗口内中包含T中的字符的个数
        int len = INT_MAX;//此处我用的int的最小值，也可以用s_len + 1
        int head = -1;//记录最终结果的初始位置
        int left = 0, right = 0;//定义滑动窗口的两个边界
        unordered_map<char,int> _map;//存储T中的字符及出现的次数
        for(int i = 0; i < t_len; i++)//初始化哈希表_map
        {
            if(_map.find(T[i])  == _map.end())
                _map.insert(pair<char,int>(T[i],1));
            else
                (_map.find(T[i])->second)++;
        }
        for(right = 0 ; right < s_len; right++)//移动右指针
        {
            if(_map.find(S[right]) != _map.end())//当窗口内部含有T中的字符时
            {
                _map[S[right]]--;//相应字符的此处减1
                if(_map[S[right]] >= 0)//减1后如果次数大于等于0，说明我们已经满足一个字符了，所以cnt加1
                    cnt++;
                while(cnt == t_len)//如果滑窗内已经包含所有T中的字符
                {
                    if(right - left + 1 < len)//更新最小的情况
                    {
                        len = right - left + 1;
                        head = left;
                    }
                    if(_map.find(S[left]) != _map.end())//如果左指针处指的是T中的字符；如果不是T中的字符则继续左移
                    {
                        _map[S[left]]++;//相应处的字符的次数加1
                       if(_map[S[left]] > 0)//如果加1之后此处大于0了，说明需要这个字符(这个字符是唯一的)，如果向右移动的话(舍去这个字符)，cnt就会减1
                            cnt--;
                        //如果这个字符不是唯一的话，不需要操作
                    }
                    left++;//移动左指针，直到滑窗中不再包含T中的全部字符
                }
            }
        }
        return head == - 1 ?"" : S.substr(head,len);//head== -1相当于没找到符合条件的子序列
 
    }
};
　　

实际上，左指针移动时，相当于考虑了三种情况：left处的字符不是T中的字符、left处的字符是T中的字符且是唯一的、left处的字符是T中的字符但不是唯一的(滑窗中其他处还有这个字符，此时_map[S[left]]是小于等于0的)。

我们也可以把_map[S[i]]理解成还需要多少个S[i]字符。该算法的时间复杂度为O(N)，空间复杂度为O(1)，因为ASCII码的话，最多256个字符就行。
