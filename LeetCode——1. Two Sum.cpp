一.题目链接：https://leetcode.com/articles/two-sum/

二.题目大意：

　　给定一个int型数组A和int值a，要求从A中找到两个数，使得这两个数值的和为a；返回结果为一个数组，该数组存储的为这两个数在数组A中的下标。(题目假设结果是唯一的)

三.题解

　　1.该题目首先最容易想到的就是暴力破解，只需要两个循环分别遍历数组；这样的话，时间复杂度为O(N2)，空间复杂度为O(1)，代码如下：
int* twoSum(int* nums, int numsSize, int target) {
    int *rs = malloc(sizeof(int)*2);
    int i = 0,j = 0;
    for(i = 0; i < numsSize; i++)
        for (j = i + 1; j < numsSize; j++)
            {
                if(nums[i] + nums[j] == target)
                {
                    rs[0] = i;
                    rs[1] = j;
                    return rs;
                }
            }
            return rs;
}
2.由于O(N2)的时间复杂度效率太低，有没有更好的方法？我们只需想方设法优化第二个for循环即可(第一个for循环一般无法优化，因为该程序至少要遍历一次)；可以考虑利用map来进行查询，代码如下：

vector<int> twoSum(vector<int>& nums, int target) {
    vector<int>rs;
    int i = 0;
    int temp;
    map<int,int>hs;
    map<int, int>::iterator iter;//由于map调用find()方法时，返回的结果为一个迭代器
    for(i = 0; i < nums.size(); i++)
    {
 
        temp = target - nums[i];
        iter = hs.find(temp);
        if(iter != hs.end())
        {
            rs.push_back(iter->second);//iter->first和iter->second分别表示key和value
            rs.push_back(i);
            return rs;
        }
        hs.insert(pair<int,int>(nums[i],i));
    }
        return rs;
}
由于map的查找时间为O(logN)，故整个程序的时间复杂度为O(N*logN);空间复杂度为O(N)(因为程序额外利用的存储空间最大为N-1级别，即map的大小)，实质上是以空间换取时间的一种策略，方法2和方法1相比，只是第二步查询的方式变了，这种思想值得借鉴。

3.鉴于方法2的思想，我们还可以进一步去优化，那就是利用哈希表，c11标准中的哈希表为unordered_map，代码如下：

vector<int> twoSum(vector<int>& nums, int target) {
    vector<int>rs;
    int i = 0;
    int temp;
    unordered_map<int,int>hs;
    unordered_map<int, int>::iterator iter;
    for(i = 0; i < nums.size(); i++)
    {
 
        temp = target - nums[i];
        iter = hs.find(temp);
        if(iter != hs.end())
        {
            rs.push_back(iter->second);
            rs.push_back(i);
            return rs;
        }
        hs.insert(pair<int,int>(nums[i],i));
    }
        return rs;
}
　　与方法2，唯一不同之处在于map换成了unordered_map，unordered_map查询时间为O(1)，故整个程序的时间复杂度为O(N),空间复杂度为O(N)(与法2类似)，只不过底层实现上与map有区别)。

注意：

1.map的底层实现是红黑树，所以保证了一个稳定的动态操作时间，查询、插入、删除都是O(logN)，最坏和平均都是查询效率为O(logN);unordered_map底层的实现是哈希表，查询效率为O(1),虽然是O（1），但是并不是unordered_map查询时间一定比map短，因为实际情况中还要考虑到数据量，而且unordered_map的hash函数的构造速度也没那么快，所以不能一概而论，应该具体情况具体分析。而且unordered_map是C11标准中新加的，所以编译器必须支持c11标准才能用unordered_map。

2.在unordered_map之前，一般用hash_map,但是hash_map并没有被并入c++标准库中，所以有的编译器可能不支持，leetcode就不支持。。。；所以以后就用unordered_map代替hash_map。
