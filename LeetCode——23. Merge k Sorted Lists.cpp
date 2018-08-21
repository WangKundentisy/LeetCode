//方法1：两两归并
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

//方法2：利用优先队列
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty())
            return nullptr;
        priority_queue<ListNode*,vector<ListNode*>,cmp> tmp;
        for(auto i:lists)
        {
            if(i)
                tmp.push(i);
        }
        if(tmp.empty())//如果lists中的元素全部为空，则返回空指针
            return nullptr;
        ListNode* rs = tmp.top();//初始化rs
        ListNode* q = rs;
        tmp.pop();
        if(q->next)
            tmp.push(q->next);
        while(!tmp.empty())//重复寻找K个指针中的最小值
        {
            ListNode* p = tmp.top();
            q->next = p;
            q = q->next;
            tmp.pop();
            if(p->next)
                tmp.push(p->next);
        }
        return rs;
    }
    struct cmp
    {
        bool operator()(const ListNode* a,const ListNode *b)
        {
            return a->val > b->val;
        }
    };
};
