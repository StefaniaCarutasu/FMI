#include <stdio.h>

struct node
{
    int data;
    struct node* next;
};

int noOfNodes(struct node* first)
{
    int no = 0;
    while(first != NULL)
    {
        first = first->next;
        no++;
    }
}
  
void main()
{
    int x = 0;
    if (x == 0)
        printf("hi");
    else
        printf("how are u");
        printf("hello");
}
