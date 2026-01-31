# the-storehouse-of-howhi
This is a storehouse created by howhi.I'll produce more high-quaity projects.
I have already studied linked lists and will introduce some commonly used functions related to linked lists.

//建立、打印、合并、逆序链表，以及删除某些特定节点
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct ListNode {
    int data;
    struct ListNode *next;
};

struct ListNode *readlist();
struct ListNode *deletem( struct ListNode *L, int m );
void printlist( struct ListNode *L )
{
     struct ListNode *p = L;
     while (p) {
           printf("%d ", p->data);
           p = p->next;
     }
     printf("\n");
}//打印链表 

int main()
{
    int m;
    struct ListNode *L = readlist();
    scanf("%d", &m);
    L = deletem(L, m);
    printlist(L);

    return 0;
}
struct ListNode *readlist()
{
	struct ListNode *head;
	struct ListNode *tail;
	head = tail = NULL;
	int data;
	while (1)
	{
		scanf("%d", &data);
		if (data == -1)
		{
			break;
		}
		struct ListNode *newnode = (struct ListNode*)malloc(sizeof(struct ListNode));
		newnode->data = data;
		newnode->next = NULL;
		if (head == NULL)
		{
			head = tail = newnode;
		}
		else
		{
			tail->next = newnode;
			tail = newnode;
		}
	}
	return head;
}//读入建立链表 
struct ListNode *deletem( struct ListNode *L, int m )
{
	struct ListNode dummy;
	dummy.next = L;
	struct ListNode *prev = &dummy;
	struct ListNode *curr = L;
	while (1)
	{
		if (curr == NULL)
		{
			break;
		}
		if (curr->data == m)
		{
			prev->next = curr->next;
			
			curr = curr->next;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	return dummy.next;
}//删除数据为特定值的链表 
struct ListNode *mergelists(struct ListNode *list1, struct ListNode *list2)
{
	struct ListNode *head = NULL;
	struct ListNode *tail = NULL;
	
	
		if (list1 == NULL)
			return list2;
		if (list2 == NULL)
			return list1;

		if (list1->data <= list2->data)
		{
			head = list1;
			list1=list1->next;
		}
		else
		{
			head = list2;
			list2=list2->next;
		}
		tail = head;
		tail->next = NULL;
		while (list1 && list2)
		{
			if (list1->data <= list2->data)
			{
				tail->next = list1;
				list1 = list1->next;
			}
			else
			{
				tail->next = list2;
				list2 = list2->next;
			}
			tail = tail->next;
			
		}
	
	if (list1)
	{
		tail->next = list1;
	}
	if (list2)
	{
		tail->next = list2;
	}
	return head;
}//合并链表 
struct ListNode *createlist()
{
	int data;
	struct ListNode *head, *tail;
	head = tail = NULL;
	while (1)
	{
		scanf("%d", &data);
		if (data==0)
		{
			break;
			
		}
		struct ListNode *new_node = (struct ListNode*)malloc(sizeof(struct ListNode));
		new_node->data = data;
		new_node->next = NULL;
		if (head == NULL)
		{
			head = tail = new_node;
		}
		else
		{
			tail->next = new_node;
			tail = new_node;
		}
		
	}
    return head;
}//建立链表 
struct ListNode *reverse( struct ListNode *head )
{
   struct ListNode *new_head=NULL;
   struct ListNode *curr=head;
   struct ListNode *temp;
   while (curr!=NULL)
   {
      temp=curr;
      curr=curr->next;
      temp->next=new_head;
      new_head=temp;
   }
   return new_head;
}
struct ListNode *reverse_createlist()
{
   int data;
   struct ListNode *head=NULL;
   while (1)
   {
      scanf("%d",&data);
      if (data==-1)
      {
         break;
      }
      struct ListNode *new_node=(struct ListNode *)malloc(sizeof(struct ListNode));
      new_node->data=data;
      new_node->next=head;
      head=new_node;
      
   }
   return head;
   
}//逆序建立链表 


//实现对链表的排序（归并排序，基于链表不便于随机访问的特性）
#include <stdio.h>
#include <stdlib.h>
struct ListNode {
	int val;
	struct ListNode* next;
};
struct ListNode* findmiddle(struct ListNode* head);
void sort(struct ListNode** head);
struct ListNode* merge(struct ListNode* s1, struct ListNode* s2);
struct ListNode* CreateNode(int n);
void printlistnode(struct ListNode* head);
int main()
{
    struct ListNode *aaa=CreateNode(5);
	printlistnode(aaa);
	sort(&aaa);
	printf("After sorted:\n");
	printlistnode(aaa);
	return 0;
}
struct ListNode* findmiddle(struct ListNode* head)
{
	if (!head || !head->next)
	{
		return head;
	}
	struct ListNode* slow = head, * fast = head->next;
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}
void sort(struct ListNode** head)
{
	struct ListNode* first = *head;
	if (!first || !first->next)
	{
		return;
	}
	struct ListNode* mid = findmiddle(first);
	struct ListNode* left = first;
	struct ListNode* right = mid->next;
	mid->next=NULL;
	sort(&left);
	sort(&right);
	*head=merge(left,right);
}
struct ListNode* merge(struct ListNode* s1, struct ListNode* s2)
{
	struct ListNode dummy;
	struct ListNode* tail = &dummy;
	dummy.next = NULL;
	while (s1 && s2)
	{
		if (s1->val <= s2->val)
		{
			tail->next = s1;
			s1 = s1->next;
		}
		else
		{
			tail->next = s2;
			s2 = s2->next;

		}
		tail = tail->next;
	}
	tail->next = (s1 ? s1 : s2);
	return dummy.next;

}
struct ListNode* CreateNode(int n)
{
	struct ListNode* head;
	struct ListNode* tail;
	struct ListNode* new_node;
	head = tail = new_node = NULL;
	int val;
	int count = 0;
	for (count = 0;count < n;count++)
	{
		scanf_s("%d", &val);
		new_node = (struct ListNode*)malloc(sizeof(struct ListNode));
		new_node->val = val;
		new_node->next = NULL;
		if (!head)
		{
			head = tail = new_node;
		}
		else
		{
			tail->next = new_node;
			tail = new_node;
		}
	}
	return head;
}
void printlistnode(struct ListNode* head)
{
	printf("##$$\n");
	while (head)
	{
		printf("%d\n",head->val);
		head=head->next;
	}
	printf("##$$\n");
}
