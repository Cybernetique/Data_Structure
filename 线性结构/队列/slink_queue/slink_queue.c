#include <stdio.h>
#include <malloc.h>

/**
 * C ����: ������ʵ�֡����С���ֻ�ܴ洢int���ݡ�
 *
 * @author skywang
 * @date 2013/11/07
 */

// ������ڵ�
struct node {
    int val;
    struct node* next;
};

// ��ͷ
static struct node *phead=NULL;

// �����ڵ㣬valΪ�ڵ�ֵ
static struct node* create_node(val)
{
    struct node *pnode=NULL;
    pnode = (struct node*)malloc(sizeof(struct node));
    if (!pnode)
        return NULL;
    pnode->val = val;
    pnode->next = NULL;

    return pnode;
}

// ���ٵ�������
static int destroy_single_link()
{
    struct node *pnode=NULL;

    while (phead != NULL)
    {
        pnode = phead;
        phead = phead->next;
        free(pnode);
    }
    return 0;
}

// ��val��ӵ����е�ĩβ
static void add(int val)
{
    if (!phead)
    {
        phead = create_node(val);
        return ;
    }

    struct node *pnode = create_node(val);
    struct node *pend = phead;
    while (pend->next)
        pend = pend->next;

    pend->next = pnode;
}

// ���ء����п�ͷԪ�ء�
int front()
{
    return phead->val;
}

// ���ز�ɾ�������п�ͷԪ�ء�
static int pop()
{
    int ret = phead->val;
    struct node *pnode = phead;

    phead = phead->next;
    free(pnode);

    return ret;
}

// ���������нڵ�ĸ���
static int size()
{
    int count=0;
    struct node *pend = phead;

    while (pend)
    {
        pend = pend->next;
        count++;
    }

    return count;
}

// �����Ƿ�Ϊ��
static int is_empty()
{
    return size()==0;
}

void main()
{
    int tmp=0;

    // ��10, 20, 30 ���μ��뵽������
    add(10);
    add(20);
    add(30);

    // �������п�ͷԪ�ء���ֵ��tmp����ɾ������Ԫ�ء�
    tmp = pop();
    printf("tmp=%d\n", tmp);

    // ֻ�������п�ͷ��Ԫ�ء���ֵ��tmp����ɾ����Ԫ��.
    tmp = front();
    printf("tmp=%d\n", tmp);

    add(40);

    printf("is_empty()=%d\n", is_empty());
    printf("size()=%d\n", size());
    while (!is_empty())
    {
        printf("%d\n", pop());
    }

    // ���ٶ���
    destroy_single_link();
}
