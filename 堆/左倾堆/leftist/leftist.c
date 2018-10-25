/**
 * C����ʵ�ֵ������
 *
 * @author skywang
 * @date 2014/03/31
 */

#include <stdio.h>
#include <stdlib.h>
#include "leftist.h"

/*
 * ǰ�����"�����"
 */
void preorder_leftist(LeftistHeap heap)
{
    if(heap != NULL)
    {
        printf("%d ", heap->key);
        preorder_leftist(heap->left);
        preorder_leftist(heap->right);
    }
}

/*
 * �������"�����"
 */
void inorder_leftist(LeftistHeap heap)
{
    if(heap != NULL)
    {
        inorder_leftist(heap->left);
        printf("%d ", heap->key);
        inorder_leftist(heap->right);
    }
}

/*
 * �������"�����"
 */
void postorder_leftist(LeftistHeap heap)
{
    if(heap != NULL)
    {
        postorder_leftist(heap->left);
        postorder_leftist(heap->right);
        printf("%d ", heap->key);
    }
}

/*
 * ���������ڵ������
 */
static void swap_leftist_node(LeftistNode *x, LeftistNode *y)
{
    LeftistNode tmp = *x;
    *x = *y;
    *y = tmp;
}

/*
 * ��ȡ��Сֵ
 *
 * ����ֵ��
 *    �ɹ�����0��ʧ�ܷ���-1
 */
int leftist_minimum(LeftistHeap heap, int *pval)
{
    if (heap == NULL)
        return -1;

    *pval = heap->key;

    return 0;
}

/*
 * �ϲ�"�����x"��"�����y"
 *
 * ����ֵ��
 *     �ϲ��õ������ĸ��ڵ�
 */
LeftistNode* merge_leftist(LeftistHeap x, LeftistHeap y)
{
    if(x == NULL)
        return y;
    if(y == NULL)
        return x;

    // �ϲ�x��yʱ����x��Ϊ�ϲ�������ĸ���
    // ����Ĳ����Ǳ�֤: x��key < y��key
    if(x->key > y->key)
        swap_leftist_node(x, y);

    // ��x���Һ��Ӻ�y�ϲ���"�ϲ�������ĸ�"��x���Һ��ӡ�
    x->right = merge_leftist(x->right, y);

    // ���"x������Ϊ��" ���� "x�����ӵ�npl<�Һ��ӵ�npl"
    // �򣬽���x��y
    if(x->left == NULL || x->left->npl < x->right->npl)
    {
        LeftistNode *tmp = x->left;
        x->left = x->right;
        x->right = tmp;
    }
    // ���úϲ��������(x)��npl
    if (x->right == NULL || x->left == NULL)
        x->npl = 0;
    else
        x->npl = (x->left->npl > x->right->npl) ? (x->right->npl + 1) : (x->left->npl + 1);

    return x;
}

/*
 * �½����(key)����������뵽�������
 *
 * ����˵����
 *     heap ����ѵĸ����
 *     key ������ļ�ֵ
 * ����ֵ��
 *     ���ڵ�
 */
LeftistNode* insert_leftist(LeftistHeap heap, Type key)
{
    LeftistNode *node;    // �½����

    // ����½����ʧ�ܣ��򷵻ء�
    if ((node = (LeftistNode *)malloc(sizeof(LeftistNode))) == NULL)
        return heap;
    node->key = key;
    node->npl = 0;
    node->left = node->right = NULL;

    return merge_leftist(heap, node);
}

/*
 * ȡ�����ڵ�
 *
 * ����ֵ��
 *     ȡ�����ڵ��������ĸ��ڵ�
 */
LeftistNode* delete_leftist(LeftistHeap heap)
{
    if (heap == NULL)
        return NULL;

    LeftistNode *l = heap->left;
    LeftistNode *r = heap->right;

    // ɾ�����ڵ�
    free(heap);

    return merge_leftist(l, r); // �������������ϲ��������
}

/*
 * ���������
 */
void destroy_leftist(LeftistHeap heap)
{
    if (heap==NULL)
        return ;

    if (heap->left != NULL)
        destroy_leftist(heap->left);
    if (heap->right != NULL)
        destroy_leftist(heap->right);

    free(heap);
}

/*
 * ��ӡ"�����"
 *
 * heap       -- ����ѵĽڵ�
 * key        -- �ڵ�ļ�ֵ
 * direction  --  0����ʾ�ýڵ��Ǹ��ڵ�;
 *               -1����ʾ�ýڵ������ĸ���������;
 *                1����ʾ�ýڵ������ĸ������Һ��ӡ�
 */
static void leftist_print(LeftistHeap heap, Type key, int direction)
{
    if(heap != NULL)
    {
        if(direction==0)    // heap�Ǹ��ڵ�
            printf("%2d(%d) is root\n", heap->key, heap->npl);
        else                // heap�Ƿ�֧�ڵ�
            printf("%2d(%d) is %2d's %6s child\n", heap->key, heap->npl, key, direction==1?"right" : "left");

        leftist_print(heap->left, heap->key, -1);
        leftist_print(heap->right,heap->key,  1);
    }
}

void print_leftist(LeftistHeap heap)
{
    if (heap != NULL)
        leftist_print(heap, heap->key,  0);
}
