一.题目链接：https://leetcode.com/problems/container-with-most-water/

二.题目大意：

　　给定n个非负整数a1,a2....an；其中每一个整数对应着一条垂直的线段，即(i,ai)到(i,0)这个线段。其中这n个线段中，任意两个线段与x轴就构成了一个容器；要你找出体积最大的容器出来，并返回它的体积值。

三.题解：

　　这道题目最容易想到的就是暴力法，从n个线段中任取两个来组成容器进行判断。

方法1：

　　暴力法，代码如下：

class Solution {
public:
    int maxArea(vector<int>& height) {
        int s = height.size();
        int max_container = 0;
        for(int i = 0 ; i < s; i++)
        {
            for(int j = i + 1; j < s; j++)
            {
                int temp = height[i] > height[j]?height[j]:height[i];
                int temp_container = temp * (j - i);
                if(temp_container > max_container)
                    max_container = temp_container;
            }
        }
        return max_container;
    }
};
该算法的时间复杂度为O(n2)，空间复杂度为O(1)，但是，最终结果会超时！

方法2：

　　仔细想想整个过程，我们会发现：对于两个长度不同的线段构成的容器，容器的体积取决于较短的那个线段。所以，我们可以利用这么一种方法：定义两个指针(L指针和R指针)，分别指向数组的头部和尾部，然后每次比较L和R指向的线段长度大小，如果L指针指向的线段长度小的话，L指针向右移动；如果R指针指向的线段长度小的话，R指针向左移动。然后每次计算容器的体积，选择最大的那个作为最终结果。(至于方法为什么可行，在后面解释)代码如下：

class Solution {
public:
    int maxArea(vector<int>& height) {
       int c_len = height.size();
       int max_container = 0;
       int l_index = 0, r_index = c_len - 1;
       while(l_index < r_index)
       {
           int temp = (r_index - l_index) * min(height[l_index],height[r_index]);
           max_container = max_container>temp?max_container:temp;
           if(height[l_index] < height[r_index])
                l_index++;
           else
                r_index--;
       }
       return max_container;
    }
};
该算法的时间复杂度为O(n),空间复杂度为O(1)。下面详细解释一下这种方法：

1.首先，要了解到的一点是此处的容器相当于一个两边不相同的长方形，而不是一个圆柱，所以它的体积计算公式是：底 x 高。而不是π x R2 x h 。

2.由于容器的体积是由较小的那个线段决定，假设L指针指向元素A，R指针指向元素B，如果A<B的话；那么，对于B左边所有的边(A除外)，它们与A构成的容器体积一定小于A与B构成的容器体积。

证：假设A与B构成的容器的底为L1、容器的高为H1，A与B左边其他线段构成的容器的底为Li、高为Hi，则Li < L1一定成立，H1≥Hi也是一定成立的(因为体积取决于较小的线段，如果Hi > H1,则Hi = H1；否则Hi不变)所以Li x Hi一定小于L1 x H1。

所以当A<B的话，L指针向左移动，而不是R指针向右移动。这样就相当于，A不用再与B左边其他的线段配对了(相比暴力而言省去了很多没用的比较)，这样的话每次判断哪个线段小，就移动相应的指针。

3.但是，如果A==B的话该怎么办？

实际上，当A==B的话，这种情况是不需要特别考虑的。即此时L指针向右移动也行，R指针向左移动也可以。为什么呢？因为此时的A和B都可以看作是较小的那个线段，根据第1步，L和R谁移动都是合理的。并且无论是L指针向右移动还是R指针向左移动，它们都遍历了A、B之间所有的线段，所以这两种移动情况结果是一样的。
