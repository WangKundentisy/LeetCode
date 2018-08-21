方法1：两两归并
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty())
            return nullptr;
        if(lists.size() == 1)
            return lists[0];
        while(lists.size() > 1)
        {
            lists.push_back(mergeTwo(lists[0],lists[1]));
            lists.erase(lists.begin());
            lists.erase(lists.begin());
        }
        return lists[0];
    }
    ListNode* mergeTwo(ListNode* a,ListNode* b)//两两归并
    {
       ListNode * head = new ListNode(0);//定义头结点
       ListNode *p = head;
       while(a != nullptr && b != nullptr)
       {
           if(a->val < b->val)
           {
               p->next = a;
               p = p->next;
               a = a->next;
           }
           else
           {
               p->next = b;
               p = p->next;
               b = b->next;
           }
       }
       if(a != nullptr)
        p->next = a;
       if(b != nullptr)
        p->next = b;
       ListNode * rs = head->next;
       delete head;//释放头结点的空间
       return rs;


    }
};
