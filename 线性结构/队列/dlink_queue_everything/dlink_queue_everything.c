#include <stdio.h>
#include "double_link.h"

/**
 * C ����: ˫������ʵ�֡����С����ܴ洢�������ݡ�
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

// ��p��ӵ����е�ĩβ
int add(void *p)
{
    return dlink_append_last(p);
}

// ���ء����п�ͷԪ�ء�
void* front()
{
    return dlink_get_first();
}

// ���ء����п�ͷ��Ԫ�ء�����ɾ������Ԫ�ء�
void* pop()
{
    void *p = dlink_get_first();
    dlink_delete_first();
    return p;
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


typedef struct tag_stu
{
    int id;
    char name[20];
}stu;

static stu arr_stu[] =
{
    {10, "sky"},
    {20, "jody"},
    {30, "vic"},
    {40, "dan"},
};
#define ARR_STU_SIZE ( (sizeof(arr_stu)) / (sizeof(arr_stu[0])) )

static void print_stu(stu *p)
{
    if (!p)
        return ;

    printf("id=%d, name=%s\n", p->id, p->name);
}

void main()
{
    stu *pval=NULL;

    // ���������С�
    create_dlink_queue();

    // ��10, 20, 30 �������������
    int i=0;
    for (i=0; i<ARR_STU_SIZE-1; i++)
    {
        add(&arr_stu[i]);
    }

    // �������п�ͷ��Ԫ�ء���ֵ��tmp����ɾ������Ԫ�ء�
    pval = (stu*)pop();
    print_stu(pval) ;

    // ֻ�������п�ͷ��Ԫ�ء���ֵ��tmp����ɾ����Ԫ��.
    pval = front();
    print_stu(pval) ;

    add(&arr_stu[ARR_STU_SIZE-1]);

    printf("is_empty()=%d\n", is_empty());
    printf("size()=%d\n", size());
    // ��ӡ�����е�����Ԫ��
    while (!is_empty())
    {
        pval = pop();
        print_stu(pval) ;
    }

    // ���ٶ���
    destroy_dlink_queue();
}
