/**
 * C����ʵ�ֵ�б��
 *
 * @author skywang
 * @date 2014/03/31
 */

#include <stdio.h>
#include <stdlib.h>
#include "skewheap.h"

/*
 * ǰ�����"б��"
 */
void preorder_skewheap(SkewHeap heap)
{
    if(heap != NULL)
    {
        printf("%d ", heap->key);
        preorder_skewheap(heap->left);
        preorder_skewheap(heap->right);
    }
}

/*
 * �������"б��"
 */
void inorder_skewheap(SkewHeap heap)
{
    if(heap != NULL)
    {
        inorder_skewheap(heap->left);
        printf("%d ", heap->key);
        inorder_skewheap(heap->right);
    }
}

/*
 * �������"б��"
 */
void postorder_skewheap(SkewHeap heap)
{
    if(heap != NULL)
    {
        postorder_skewheap(heap->left);
        postorder_skewheap(heap->right);
        printf("%d ", heap->key);
    }
}

/*
 * ���������ڵ������
 */
static void swap_skewheap_node(SkewNode *x, SkewNode *y)
{
    SkewNode tmp = *x;
    *x = *y;
    *y = tmp;
}

/*
 * ��ȡ��Сֵ
 *
 * ����ֵ��
 *    �ɹ�����0��ʧ�ܷ���-1
 */
int skewheap_minimum(SkewHeap heap, int *pval)
{
    if (heap == NULL)
        return -1;

    *pval = heap->key;

    return 0;
}

/*
 * �ϲ�"б��x"��"б��y"
 *
 * ����ֵ��
 *     �ϲ��õ������ĸ��ڵ�
 */
SkewNode* merge_skewheap(SkewHeap x, SkewHeap y)
{
    if(x == NULL)
        return y;
    if(y == NULL)
        return x;

    // �ϲ�x��yʱ����x��Ϊ�ϲ�������ĸ���
    // ����Ĳ����Ǳ�֤: x��key < y��key
    if(x->key > y->key)
        swap_skewheap_node(x, y);

    // ��x���Һ��Ӻ�y�ϲ���
    // �ϲ���ֱ�ӽ���x�����Һ��ӣ�������Ҫ�������һ���������ǵ�npl��
    SkewNode *tmp = merge_skewheap(x->right, y);
    x->right = x->left;
    x->left  = tmp;

    return x;
}

/*
 * �½����(key)����������뵽б����
 *
 * ����˵����
 *     heap б�ѵĸ����
 *     key ������ļ�ֵ
 * ����ֵ��
 *     ���ڵ�
 */
SkewNode* insert_skewheap(SkewHeap heap, Type key)
{
    SkewNode *node;    // �½����

    // ����½����ʧ�ܣ��򷵻ء�
    if ((node = (SkewNode *)malloc(sizeof(SkewNode))) == NULL)
        return heap;
    node->key = key;
    node->left = node->right = NULL;

    return merge_skewheap(heap, node);
}

/*
 * ȡ�����ڵ�
 *
 * ����ֵ��
 *     ȡ�����ڵ��������ĸ��ڵ�
 */
SkewNode* delete_skewheap(SkewHeap heap)
{
    SkewNode *l = heap->left;
    SkewNode *r = heap->right;

    // ɾ�����ڵ�
    free(heap);

    return merge_skewheap(l, r); // �������������ϲ��������
}

/*
 * ����б��
 */
void destroy_skewheap(SkewHeap heap)
{
    if (heap==NULL)
        return ;

    if (heap->left != NULL)
        destroy_skewheap(heap->left);
    if (heap->right != NULL)
        destroy_skewheap(heap->right);

    free(heap);
}

/*
 * ��ӡ"б��"
 *
 * heap       -- б�ѵĽڵ�
 * key        -- �ڵ�ļ�ֵ
 * direction  --  0����ʾ�ýڵ��Ǹ��ڵ�;
 *               -1����ʾ�ýڵ������ĸ���������;
 *                1����ʾ�ýڵ������ĸ������Һ��ӡ�
 */
static void skewheap_print(SkewHeap heap, Type key, int direction)
{
    if(heap != NULL)
    {
        if(direction==0)    // heap�Ǹ��ڵ�
            printf("%2d is root\n", heap->key);
        else                // heap�Ƿ�֧�ڵ�
            printf("%2d is %2d's %6s child\n", heap->key, key, direction==1?"right" : "left");

        skewheap_print(heap->left, heap->key, -1);
        skewheap_print(heap->right,heap->key,  1);
    }
}

void print_skewheap(SkewHeap heap)
{
    if (heap != NULL)
        skewheap_print(heap, heap->key,  0);
}
