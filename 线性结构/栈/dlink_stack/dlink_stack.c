#include <stdio.h>
#include "double_link.h"

/**
 * C ����: ˫������ʵ��ջ��ֻ�ܴ洢int���ݡ�
 *
 * @author skywang
 * @date 2013/11/07
 */
// ����ջ
int create_dlink_stack()
{
    return create_dlink();
}

// ����ջ
int destroy_dlink_stack()
{
    return destroy_dlink();
}

// ��val��ӵ�ջ��
int push(int val)
{
    return dlink_insert_first(val);
}

// ���ء�ջ��Ԫ��ֵ��
int peek()
{
    return dlink_get_first();
}

// ���ء�ջ��Ԫ��ֵ������ɾ����ջ��Ԫ�ء�
int pop()
{
    int ret = peek();
    dlink_delete_first();
    return ret;
}

// ���ء�ջ���Ĵ�С
int size()
{
    return dlink_size();
}

// ���ء�ջ���Ƿ�Ϊ��
int is_empty()
{
    return dlink_is_empty();
}

// ��ӡ��ջ��
void print_dlink_stack()
{
    return print_dlink();
}

void main()
{
    int tmp=0;

    // ������ջ��
    create_dlink_stack();

    // ��10, 20, 30 ��������ջ��
    push(10);
    push(20);
    push(30);

    //print_dlink_stack();    // ��ӡջ

    // ����ջ��Ԫ�ء���ֵ��tmp����ɾ����ջ��Ԫ�ء�
    tmp = pop();
    printf("tmp=%d\n", tmp);
    //print_dlink_stack();    // ��ӡջ

    // ֻ����ջ������ֵ��tmp����ɾ����Ԫ��.
    tmp = peek();
    printf("tmp=%d\n", tmp);
    //print_dlink_stack();    // ��ӡջ

    push(40);
    print_dlink_stack();    // ��ӡջ

    // ����ջ
    destroy_dlink_stack();
}
