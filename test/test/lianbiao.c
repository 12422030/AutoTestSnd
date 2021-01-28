/**
 *创建单节点链表

        ------       ------       ------
        |数据|       |数据|       |数据|
node--> ------   |-->------   |-->------   |-->NULL
        |指针|----   |指针|----   |指针|----
        -----        ------       ------
 **/    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct  list_node
{
    int data ; 
    struct list_node *next ;
};
typedef struct list_node list_single ;  
list_single *create_list_node(int data) /**创建指针**/
{
    list_single *node = NULL ;
    node = (list_single *)malloc(sizeof(list_single));
    if(node == NULL){
        printf("malloc fair!\n");
    }
    memset(node,0,sizeof(list_single));
    node->data = data;
    node->next = NULL ;
    return node ;
}
int main(void)
{
    int data = 100 ;
    list_single *node_ptr = create_list_node(data); //创建一个节点
    printf("node_ptr->data=%d\n",node_ptr->data);   //打印节点里的数据
    printf("node_ptr->next=%d\n",node_ptr->next);  
    free(node_ptr);
    return 0 ;
}
