一.题目链接：https://leetcode.com/problems/add-two-numbers

二.题目大意：

　　给定两个链表，每个链表表示一个非负数，不过数字的顺序是反过来存储的，要求给出这两个非负数的和，也是用一个链表以反顺序的形式来表示。

三.题解

　　该题目有以下思路：

1.两个链表都反转过来，然后遍历，用两个vector把遍历的数值存起来，之后两个vector数值对应相加(此处的相加一开始是想的是转换成int型或long型，然后数值相加；不过仔细想了想这不就是大数加法么)最后的结果反转过来再存入新链表。这种方法实现比较复杂，空间复杂度O(n),时间复杂度O(m+n)，不建议用此法。

2.仔细分析下这道题目，这些数字按从左向右的顺序实际上可以看成个位、十位。。。的顺序，所以可以直接按大数加法的思想，从左向右顺序相加；结合归并排序的思想，可以直接把结果放到已知的一个链表之中，就不用额外新建链表了，代码如下：
struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
};
 
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
            ListNode *p1 = l1;
            ListNode *p2 = l2;
            ListNode *p = p1;//最后的结果存在l1中
            ListNode *q1 = new ListNode(0);//表示l1中的最后一个节点
            ListNode *q2 = new ListNode(0);//表示l2中的最后一个节点
            int temp = 0;//表示进位
            while(p1&&p2)
            {   //记录最后一个节点的位置
                if(p1->next == NULL)
                    q1 = p1;
                if(p2->next == NULL)
                    q2 = p2;
                int _val = (p1->val + p2->val + temp) % 10;
                temp = (p1->val + p2->val + temp) / 10;
                p->val = _val;
                p1 = p1->next;
                p2 = p2->next;
                p = p->next;
            }
            if(p1&&!p2)//p1长度大于p2的长度
            {
            while(p1)
            {
                if(p1->next == NULL)
                    q1 = p1;
                int _val = (p1->val + temp) % 10;
                temp = (p1->val+temp) / 10;
                p->val = _val;
                p1 = p1->next;
                p = p->next;
            }
            //如果算完最后一个数的时候进位不为0，则链表增加一位
            if(temp != 0)
            {
                ListNode *q = new ListNode(1);
                q1->next = q;
            }
            return l1;
            }
            if(p2&&!p1){//p2的长度大于p1的长度
            q1->next = p2;
            p = p2;
            while(p2)
            {
                if(p2->next == NULL)
                    q2 = p2;
                int _val = (p2->val + temp) % 10;
                temp = (p2->val+temp) / 10;
                p->val = _val;
                p2 = p2->next;
                p = p->next;
 
            }
            if(temp != 0)
            {
                ListNode *q = new ListNode(1);
                q2->next = q;
            }
            return l1;
            }
            if(!p1&&!p2)//p1与p2的长度相同
            {
                if(temp != 0)
            {
                ListNode *q = new ListNode(1);
                q1->next = q;
            }
                return l1;
            }
 
 
 
    }
该算法的时间复杂度为O(m+n)，空间复杂度为O(1)，但有几个需要注意的点：

1.两个链表相加时候，最后一位数计算完之后，如果进位不为0的话，就需要多增加一位，即链表多增加一个节点。

2.需要用额外的节点来记录已知链表的最后一个节点，便于后续的操作。

3.最后的计算结果存在l1中，如果l1的长度小于l2的话，还需将l1的末尾连接到l2的剩余部分(此处就会用到2中的额外节点了)。

4.关于大数加法的一个想法(与本题目关联不大)：两个大数求和时，如果长度不一致的话，可通过高位补0使得两个大数的位数相同，然后求和会更加方便。
