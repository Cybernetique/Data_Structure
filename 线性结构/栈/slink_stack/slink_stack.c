#include <stdio.h>
#include <malloc.h>

/**
 * C ����: ��������ʵ�ֵ�ջ��ֻ�ܴ洢int���ݡ�
 *
 * @author skywang
 * @date 2013/11/07
 */

// ��������ġ��ڵ㡱
struct node {
    int val;
    struct node* next;
};

// ��������ġ���ͷ��
static struct node *phead=NULL;

// �����ڵ㣬valΪ�ڵ�ֵ
static struct node* create_node(int val)
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

    while (phead != NULL) {
        pnode = phead;
        phead = phead->next;
        free(pnode);
    }
    return 0;
}

// ��val���뵽����ı�ͷλ��
static struct node* push(int val)
{
    struct node *pnode = NULL;

    pnode = create_node(val);
    pnode->next = phead;
    phead = pnode;

    return phead;
}

// ɾ������ı�ͷ
static int pop()
{
    if (!phead)
    {
        printf("remove failed! link is empty!");
        return -1;
    }

    int ret;
    struct node *pnode;
    ret = phead->val;
    pnode = phead;
    phead = phead->next;
    free(pnode);

    return ret;
}

// ��������ı�ͷ�ڵ��ֵ
static int peek()
{
    if (!phead)
    {
        printf("peek failed! link is empty!");
        return -1;
    }

    return phead->val;
}

// ���������нڵ�ĸ���
static int size()
{
    int count=0;
    struct node *pnode=phead;

    while (pnode != NULL) {
        pnode = pnode->next;
        count++;
    }
    return count;
}

// �����Ƿ�Ϊ��
static int is_empty()
{
    return phead==NULL;
}

// ��ӡ��ջ��
static void print_single_link()
{
    if (is_empty())
    {
        printf("stack is Empty\n");
        return 0;
    }

    printf("stack size()=%d\n", size());

    struct node *pnode=NULL;

    while (phead != NULL) {
        printf("%d\n", phead->val);
        pnode = phead;
        phead = phead->next;
        free(pnode);
    }
}

void main()
{
    int tmp=0;

    // ��10, 20, 30 ��������ջ��
    push(10);
    push(20);
    push(30);

    //print_single_link();    // ��ӡջ

    // ����ջ��Ԫ�ء���ֵ��tmp����ɾ����ջ��Ԫ�ء�
    tmp = pop();
    printf("tmp=%d\n", tmp);
    //print_single_link();    // ��ӡջ

    // ֻ����ջ������ֵ��tmp����ɾ����Ԫ��.
    tmp = peek();
    printf("tmp=%d\n", tmp);
    //print_single_link();    // ��ӡջ

    push(40);
    print_single_link();    // ��ӡջ

    // ����ջ
    destroy_single_link();
}
