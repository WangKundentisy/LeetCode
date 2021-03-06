一.题目链接：https://leetcode.com/problems/3sum/

二.题目大意：

　3和问题是一个比较经典的问题，它可以看做是由2和问题(见http://www.cnblogs.com/wangkundentisy/p/7525356.html)演化而来的。题目的具体要求如下：

给定一个数组A，要求从A中找出这么三个元素a,b,c使得a + b + c = 0，返回由这样的a、b、c构成的三元组，且要保证三元组是唯一的。(即任意的两个三元组，它们里面的元素不能完全相同)

三.题解：

　　我们知道3和问题是由2和问题演化而来的，所以说我们可以根据2和问题的求法，来间接求解三和问题。常见的2和问题的求解方法，主要包括两种那：利用哈希表或者两用双指针。

而三和问题，我们可以看成是在2和问题外面加上一层for循环，所以3和问题的常用解法也是分为两种：即利用哈希表和利用双指针。下面具体介绍两种方法：

方法1：利用哈希表

这种方法的基本思想是，将数组中每个元素和它的下标构成一个键值对存入到哈希表中，在寻找的过程中对于数组中的某两个元素a、b只需在哈希表中判断是否存在-a-b即可，由于在哈希表中的查找操作的时间复杂度为O(1)，在数组中寻找寻任意的找两个元素a、b需要O(n^2)，故总的时间复杂度为O(N^2)。代码如下:

1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
class Solution
{
public:
    vector<vector<int> > threeSum(vector<int> &num)
    {
        vector<vector<int>> rs;
        int len = num.size();
        if(len == 0)
            return rs;
        sort(num.begin(),num.end());//排序是为了不重复处理后续重复出现的元素
        for(int i = 0; i < len; i++)
        {
            if(i != 0 && num[i] == num[i - 1])//i重复出现时不重复处理
                continue;
            unordered_map<int,int> _map;//注意建立_map的位置
            for(int j = i + 1; j < len; j++)
            {
                if(_map.find(-num[i]-num[j]) != _map.end())
                {
                    rs.push_back({num[i],num[j],-num[i]-num[j]});
                    while(j + 1 < len && num[j] == num[j + 1])//j重复出现时不重复处理
                        j++;
                }
                _map.insert({num[j],j});//注意_map插入的元素是根据j来的不是根据i来的
            }
 
        }
        return rs;
 
    }
 
};
这种方法先对数组nums进行排序，然后在双重for循环中对哈希表进行操作，时间复杂度为O(N*logN)+O(N^2)，所以总的时间复杂度为O(N^2)，空间复杂度为O(N)，典型的以时间换空间的策略。但是，有几个重要的点一定要掌握：

1.为什么要事先对数组nums进行排序？

这是因为由于题目要求的是返回的三元组必须是重复的，如果直接利用哈希表不进行特殊处理的话，最终的三元组一定会包含重复的情况，所以我们对数组进行排序是为了对最终的结果进行去重，其中去重包括i重复的情况和j重复的情况分，不注意两种情况的处理方式是不同的，i是判断与i-1是否相同；而j是判断与j+1是否相同。

2.关于对三元组进行去重，实际上有两种方式：

(1)按照本例中的形式，先对数组进行排序，在遍历的过程中遇到重复元素的情况就跳过。

(2)不对数组事先排序，在遍历过程中不进行特殊的处理，在得到整个三元组集合后，在对集合中的三元组进行去重，删去重复的三元组。(一个简单的思路是对集合中每个三元组进行排序，然后逐个元素进行比较来判断三元组是否重复)。(这种思路可能会比本例中的方法性能更优一些)

3.注意哈希表建立的位置，是首先确定i的位置后，才开始创建哈希表的；而不是先建立哈希表，再根据i和j进行遍历。此外，哈希表中存储的元素是根据j的位置来决定的，相当于每次先固定一个i，然后建立一个新的哈希表，然后在遍历j，并根据j判断哈希表。(这个过程并不难理解，自己举个例子，画个图应该就明白了)

然而，我利用这种方法(上述代码)，在leetcode上提交居然超时了！！！即方法1在leetcode没通过啊。

方法2：利用两个指针

这种方法是最常用的方法(leetcode上AC的代码大多都是这种方法)，主要的思想是：必须先对数组进行排序(不排序的话，就不能利用双指针的思想了，所以说对数组进行排序是个大前提)，每次固定i的位置，并利用两个指针j和k，分别指向数组的i+1位置和数组的尾元素，通过判断num[j]+num[k]与-num[i]的大小，来决定如何移动指针j和k，和leetcode上最大容器的拿到题目的思想类似。具体代码如下：

class Solution
{
public:
    vector<vector<int> > threeSum(vector<int> &num)
    {
        vector<vector<int>> rs;
        int len = num.size();
        if(len == 0)
            return rs;
        sort(num.begin(),num.end());
        for(int i = 0; i < len; i++)
        {
            int j = i + 1;
            int k = len - 1;
            if(i != 0 && num[i] == num[i - 1])//如果遇到重复元素的情况，避免多次考虑
                continue;
            while(j < k)//对于每一个num[i]从i之后的元素中,寻找对否存在三者之和为0的情况
            {
                if(num[i] + num[j] +num[k] == 0)//当三者之和为0的情况
                {
                    rs.push_back({num[i],num[j],num[k]});
                    j++;//当此处的j,k满足时，别忘了向前/向后移动，判断下一个是否也满足
                    k--;
                    while(j < k && num[j] == num[j - 1])//如果遇到j重复的情况，也要避免重复考虑
                        j++;
                    while(j < k && num[k] == num[k + 1])//如果遇到k重复的情况，也要避免重复考虑
                        k--;
                }
                else if(num[i] + num[j] + num[k] < 0)//三者之和小于0的情况，说明num[j]太小了，需要向后移动
                    j++;
                else//三者之和大于0的情况，说明num[k]太大了，需要向前移动
                    k--;
            }
        }
        return rs;
 
    }
 
};
　　

该方法的时间复杂度为O(N*logN)+O(N^2)=O(N^2)和方法1实际上是一个数量级的，但是空间复杂度为O(1)，所以说综合比较的话，还是方法2的性能更好一些。同样地，这种方法也有几个需要注意的点：

1.需要先对数组进行排序，一开始的时候也强调了，不排序的话整个思路就是错的；这种方法的一切都是建立在有序数组的前提下。

2.每次找到符合条件的num[j]和num[k]时，这时候，j指针要往前移动一次，同时k指针向后移动一次，避免重复操作，从而判断下个元素是否也符合

3.和方法1一样，都需要去重(且去重时，一般都是在找到满足条件的元素时才执行)，由于该方法一定要求数组是有序的，所以就按照第一种去重方法来去重就好了。但是需要注意下与第1种方法去重的不同之处：

(1)i指针的去重同方法1一样，都是判断当前位置的元素与前一个位置的元素是否相同，如果相同，就忽略。这是因为前一个位置的元素已经处理过了，如果当前位置的元素与之相同的话，就没必要处理了，否则就会造成重复。

(2)j指针(还有k指针)的去重方法同方法1是不同的。先分析下方法1：

如果num[j]是符合条件的元素的话，并且下一个元素同num[j]相同的话，那么久没必要再去判断了，直接跳过就行了。那如果把nums[j] == num[j +1]改成num[j] == num[j -1]行吗？显然不行啊，举个例子就行，假如num[j] == 1且此时1正好符合，那么对于序列1,1....的话，当判断第一个1时，会把结果存入数组；如果改成num[j] == num[j-1]的话，判断第二个1的时候，会先把元素存入数组，然后再判断和前一个元素是否相同；即实际上这样已经发生重复操作了，如果是nums[j] == num[j +1]就是直接判断下一个元素，就是先判断在存储，就不会重复操作了。(也可以这样理解：由于去重操作只在找到重复元素的时候才进行，当num[j]满足时，如果num[j+1]也满足，则一定不用再判断了；而如果num[j-1]与num[j]相同的话，反而会把num[j-1]和num[j]都存进去了)

在分析下方法2：

对于方法2中的j指针和k指针，就比较好理解了；由于在判断是满足条件的元素的话，就会j++,k--，此时j和k的位置都发生了变化，就不知道是不是满足了，所以要根据前一个元素来判断，如果现在的元素与前一个元素(对于j来说就是j-1，对于k来说就是K+1)相同的话，就直接跳过，从而避免了重复操作。

与方法1中的j是不同的，方法1中的j并没有执行j++操作(或者说是后执行的j++)。

方法2最终在leetcode上AC了，以后还是优先使用这种的方法吧！

 =======================================================分割线======================================================================================

　　以上问题都是针对2sum和3sum，那么对于4sum。。。ksum，上述解法也是可行的。所以对于Ksum问题来讲，通常有两种思路：

1.利用双指针。

2.利用哈希表。

这两种方法的本质都是，在外层有k-2层循环嵌套，最内层循环中采用双指针或者哈希表，所以总的时间复杂度为O(N^k-1)。

注：对于Ksum问题，如果题目要求结果不能重复的话，一定要考虑去重，去重方法，上面第一个例子也讲了。

实际上，对于4sum问题，还有更优的解法。主要是利用哈希表，其中哈希表类为<int,vector<pair<int,int>>>型，其中key表示的是数组中任意来年各个元素的和，value表示的这两个元素对应下标构成的pair，即pair<i,j>，由于对于两组不同的元素(共4个)可能存在重复的和，即key值相同，所以value对应的是一个pair构成的数组。这样的话，后面只需要两次循环找出hash[target - num[i] - num[j]]即可，所以总的时间复杂为O(N^2),空间复杂度也为O(N^2)。(由于pair<int,int>本质就是个哈希表，所以这种方法的实质就是嵌套哈希表)

可参考：

　　https://blog.csdn.net/nanjunxiao/article/details/12524405

　　https://www.cnblogs.com/TenosDoIt/p/3649607.html

　　https://blog.csdn.net/haolexiao/article/details/70768526

　　http://westpavilion.blogspot.com/2014/02/k-sum-problem.html
