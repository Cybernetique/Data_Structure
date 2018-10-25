#include <stdio.h>
#include "double_link.h"

/**
 * C ����: ˫������ʵ�֡����С���ֻ�ܴ洢int���ݡ�
 *
 * @author skywang
 * @date 2013/11/07
 */

// ��������
int create_dlink_queue()
{
    return create_dlink();
}

// ���ٶ���
int destroy_dlink_queue()
{
    return destroy_dlink();
}

// ��val��ӵ����е�ĩβ
int add(int val)
{
    return dlink_append_last(val);
}

// ���ء����п�ͷԪ�ء�
int front()
{
    return dlink_get_first();
}

// ���ز�ɾ�������п�ͷԪ�ء�
int pop()
{
    int ret = dlink_get_first();
    dlink_delete_first();
    return ret;
}

// ���ء����С��Ĵ�С
int size()
{
    return dlink_size();
}

// ���ء����С��Ƿ�Ϊ��
int is_empty()
{
    return dlink_is_empty();
}

void main()
{
    int tmp=0;

    // ���������С�
    create_dlink_queue();

    // ��10, 20, 30 ���ζ�����
    add(10);
    add(20);
    add(30);

    // �������п�ͷ��Ԫ�ء���ֵ��tmp����ɾ������Ԫ�ء�
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
    destroy_dlink_queue();
}
