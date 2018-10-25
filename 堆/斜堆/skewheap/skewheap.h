#ifndef _SKEW_HEAP_H_
#define _SKEW_HEAP_H_

typedef int Type;

typedef struct _SkewNode{
    Type   key;                    // �ؼ���(��ֵ)
    struct _SkewNode *left;    // ����
    struct _SkewNode *right;    // �Һ���
}SkewNode, *SkewHeap;

// ǰ�����"б��"
void preorder_skewheap(SkewHeap heap);
// �������"б��"
void inorder_skewheap(SkewHeap heap);
// �������"б��"
void postorder_skewheap(SkewHeap heap);

// ��ȡ��Сֵ(���浽pval��)���ɹ�����0��ʧ�ܷ���-1��
int skewheap_minimum(SkewHeap heap, int *pval);
// �ϲ�"б��x"��"б��y"�������غϲ��������
SkewNode* merge_skewheap(SkewHeap x, SkewHeap y);
// �������뵽б���У������ظ��ڵ�
SkewNode* insert_skewheap(SkewHeap heap, Type key);
// ɾ�����(keyΪ�ڵ��ֵ)�������ظ��ڵ�
SkewNode* delete_skewheap(SkewHeap heap);

// ����б��
void destroy_skewheap(SkewHeap heap);

// ��ӡб��
void print_skewheap(SkewHeap heap);

#endif
