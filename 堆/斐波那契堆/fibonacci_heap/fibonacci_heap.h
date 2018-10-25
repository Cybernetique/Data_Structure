#ifndef _FIBONACCI_HEAP_H_
#define _FIBONACCI_HEAP_H_

typedef int Type;

typedef struct _FibonacciNode
{
    Type   key;                        // �ؼ���(��ֵ)
    int degree;                        // ����
    struct _FibonacciNode *left;    // ���ֵ�
    struct _FibonacciNode *right;    // ���ֵ�
    struct _FibonacciNode *child;    // ��һ�����ӽڵ�
    struct _FibonacciNode *parent;    // ���ڵ�
    int marked;                       //�Ƿ�ɾ����1������(1��ʾɾ����0��ʾδɾ��)
}FibonacciNode, FibNode;

typedef struct _FibonacciHeap{
    int   keyNum;                    // ���нڵ������
    int   maxDegree;                // ����
    struct _FibonacciNode *min;        // ��С�ڵ�(ĳ����С�ѵĸ��ڵ�)
    struct _FibonacciNode **cons;    // ���ȵ��ڴ�����
}FibonacciHeap, FibHeap;

// ����Fibonacci��
FibHeap* fib_heap_make();
// �½���ֵΪkey�Ľڵ㣬��������뵽쳲���������
void fib_heap_insert_key(FibHeap *heap, Type key);
// ɾ����ֵΪkey�Ľ��
void fib_heap_delete(FibHeap *heap, Type key);
// �Ƴ���С�ڵ�
void fib_heap_extract_min(FibHeap *heap);
// ����heap���е�oldkeyΪnewkey
void fib_heap_update(FibHeap *heap, Type oldkey, Type newkey);
// ��h1, h2�ϲ���һ���ѣ������غϲ���Ķ�
FibHeap* fib_heap_union(FibHeap *h1, FibHeap *h2);
// ��쳲�������heap���Ƿ���ڼ�ֵΪkey�Ľڵ㣻���ڷ���1�����򷵻�0��
int fib_heap_contains(FibHeap *heap, Type key);
// ��ȡ��С�ڵ��Ӧ��ֵ(������pkey��)���ɹ�����1��ʧ�ܷ���0��
int fib_heap_get_min(FibHeap *heap, Type *pkey);
// ����쳲�������
void fib_heap_destroy(FibHeap *heap);
// ��ӡ"쳲�������"
void fib_print(FibHeap *heap);

#endif
