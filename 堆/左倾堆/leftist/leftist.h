#ifndef _LEFTIST_TREE_H_
#define _LEFTIST_TREE_H_

typedef int Type;

typedef struct _LeftistNode{
    Type   key;                    // �ؼ���(��ֵ)
    int npl;                    // ��·������(Null Path Length)
    struct _LeftistNode *left;    // ����
    struct _LeftistNode *right;    // �Һ���
}LeftistNode, *LeftistHeap;

// ǰ�����"�����"
void preorder_leftist(LeftistHeap heap);
// �������"�����"
void inorder_leftist(LeftistHeap heap);
// �������"�����"
void postorder_leftist(LeftistHeap heap);

// ��ȡ��Сֵ(���浽pval��)���ɹ�����0��ʧ�ܷ���-1��
int leftist_minimum(LeftistHeap heap, int *pval);
// �ϲ�"�����x"��"�����y"�������غϲ��������
LeftistNode* merge_leftist(LeftistHeap x, LeftistHeap y);
// �������뵽������У������ظ��ڵ�
LeftistNode* insert_leftist(LeftistHeap heap, Type key);
// ɾ�����(keyΪ�ڵ��ֵ)�������ظ��ڵ�
LeftistNode* delete_leftist(LeftistHeap heap);

// ���������
void destroy_leftist(LeftistHeap heap);

// ��ӡ�����
void print_leftist(LeftistHeap heap);

#endif
