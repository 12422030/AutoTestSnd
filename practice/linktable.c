#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Node{
  int data;
  struct Node *next;
};
int main()
{
    int len,i,val;
    struct Node *p=NULL;
    struct Node *pHead=NULL;
    struct Node *pTail=NULL;
    printf("输入链表的长度:\n");
    scanf("%d",&len);
    pHead=(struct Node *)malloc(sizeof(struct Node));
    if(pHead==NULL)
    {
        return -1;
    }
    pTail=pHead;
    pTail->next=NULL;
    for(i=0;i<len;i++)
    {
        printf("输如第%d个值:",i+1);
        scanf("%d",&val);
        struct Node *pNew=NULL;
        pNew=(struct Node *)malloc(sizeof(struct Node));
        if(pNew==NULL)
        {
            printf("创建错误\n");
            return -2;
        }
        pNew->data=val;
        pNew->next=NULL;
        pTail->next=pNew;
        pTail=pNew;
    }
    printf("开始打印链表:\n");
    p=pHead->next;
    while(p!=NULL)
    {
        printf("-%d-",p->data);
        p=p->next;
    }
    printf("\n");
    printf("链表打印结束:\n");
    return 0;
}
