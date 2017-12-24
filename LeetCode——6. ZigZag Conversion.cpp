一.题目链接：https://leetcode.com/problems/zigzag-conversion/description/

二.题目大意：

　　给定一个字符串和一个数字，将其转换成Zigzag形式后，逐行输出该字符串。所谓的Zigzag形式，具体如下：
/*n=numRows
Δ=2n-2    1                           2n-1                         4n-3
Δ=        2                     2n-2  2n                    4n-4   4n-2
Δ=        3               2n-3        2n+1              4n-5       .
Δ=        .           .               .               .            .
Δ=        .       n+2                 .           3n               .
Δ=        n-1 n+1                     3n-3    3n-1                 5n-5
Δ=2n-2    n                           3n-2                         5n-4
*/
也就是把一个字符串拆成"N"字形。

三.题解：

　　这道题目的主要难点在于不知道Zigzag的具体形式，在了解了Zigzag的具体形式后，实际上就是一道关于字符串找规律的题目，对于有的列，它每行都有字符；而对于另一些列，它只有某一行有字符，弄清规律后，就直接撸代码。

方法1：直接用一个二维数组存储字符串的Zigzag形式，然后在逐行输入，代码如下：
class Solution
{
public:
    int index = 0;//表示字符串的位置
    int len = 0;
    int _cl = 0;//记录总列数
    string convert(string s, int numRows)
    {
        len = s.size();
        char str[1000][1000];
        memset(str,'#',sizeof(str));
        string rs = "";
        int flag = 0;//用于判断是做单列处理还是做多列处理
        if(numRows == 1)
            return s;
        while(index != len)
        {

            if(flag & 1)
            {
                int temp = manyColumn(str,numRows,s);

                if( temp == 0)
                {
                    flag++;
                    continue;

                }
            }
            else
            {
                
                int temp = oneColumn(str,numRows,s);
                if( temp == numRows)
                {
                    flag++;
                    _cl++;

                }
                else
                {
                    if(index >= len)
                        _cl++;
                }
            }
        }
        for(int i = 0; i < numRows; i++)
        {


            for(int j = 0; j < _cl; j++)
            {
                if(str[i][j] != '#')
                rs += str[i][j];
                
            }
            
        }


        return rs;
    }
    int oneColumn(char str[][1000],int numRows,string s)
    {
        for(int i = 0 ;; i++)
        {
            if(index != len && i != numRows)
            {
                str[i][_cl] = s[index++];
                
            }

            else
                return i;
        }

    }
    int manyColumn(char str[][1000],int numRows,string s)
    {

        for(int i = numRows - 2; ; i--)
        {
            if(index != len && i != 0)
            {

                str[i][_cl++] = s[index++];
                
            }
            else
            {

                return i;
            }

        }

    }
};
这种实现方法，我把二维数组初始化成值包含"#"的字符数组，然后对于这两种列进行分情况讨论，实现起来感觉很麻烦(涉及的变量多，细节点多)，时间复杂度为O(n*numRows),实际提交结果为106ms，基本上是最慢的那一类方法了。

方法2：根据方法1，做出了些改进(当然只是实现上的改进，对于算法，由于是找规律的题目，找到规律，相当于就是算法了，所以这类题目一般算法上没什么改进)。对于一个二维数组，没插入任何字符的位置，我么那就不去考虑它了，直接考虑插入字符的位置，即对于每一行，如果某列没有插入元素的话，就不去考虑这一行了，直接考虑下一行，直到所有的元素都插入完成。带代码如下：
class Solution
{
public:
    string convert(string s, int numRows)
    {
        int len = s.size();
        int row = 0;
        int flag = 0;
        string rs ="";
        if(numRows == 1)
            return s;
        string *temp = new string[numRows];//定义每一行对应的string
        for(int i = 0; i < len; i++)
        {
            if(row == 0)
                flag = 1;
            if(row == numRows - 1)
                flag = -1;
            temp[row].push_back(s[i]);
            row += flag;
 
        }
        for(int i = 0; i < numRows; i++)
            rs += temp[i];
        return rs;
 
 
    }
};
1.　这种方法就比较清晰明了了，该方法关键是把每行的字符串看成一个string，不插入字符的位置就不用考虑(同时也不考虑列的位置了)，直接想象成一个连续的字符串；然后定义一个string指针，用来指向每行的string。然后定义一个flag，当行号为0时，一定是每行都有字符的情况，这时候只要行号逐个递增即可；当插入完最后一行时，就是只有某一行又符的情况了，然后从倒数第二个字符开始逐个递减，直至行号为0时。

2.这这种方法相比方法1技巧性更强，我此处说的也不是很清晰，最好的方法就是多读几遍此处的代码，结合题目理解，掌握以下这种技巧会更好。该方法的时间复杂度为O(n)，实际提交结果是19ms，立马跑到最快的一类算法上去了...

3.另一个关键点在于，遇到row == 0和row == numRows - 1的时候，row不立马改变，改变的是flag这个变量，而row又是通过flag而改变的，这就相当于能控制row在什么时候改变了；这种技巧是很值得掌握的。

4.这个代码一定要多读，要深刻理解。
