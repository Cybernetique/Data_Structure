/**
 * C����ʵ�ֵ�쳲�������
 *
 * @author skywang
 * @date 2014/04/05
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "fibonacci_heap.h"

#if 0
#define LOG2(x) ({ \
        unsigned int _i = 0; \
        __asm__("bsr %1, %0" : "=r" (_i) : "r" ((x))); \
        _i; })
#else   // ע�⣺ͨ��gcc����ʱ��Ҫ��� -lm ѡ�
#define LOG2(x) ((log((double)(x))) / (log(2.0)))
#endif


static FibNode *fib_heap_search(FibHeap *heap, Type key);

/*
 * ��node��˫�����Ƴ�
 */
static void fib_node_remove(FibNode *node)
{
    node->left->right = node->right;
    node->right->left = node->left;
}

/*
 * ��"�����ڵ�node"����"����root"֮ǰ
 *   a ���� root
 *   a ���� node ���� root
 *
 * ע�⣺ �˴�node�ǵ����ڵ㣬��root��˫������
*/
static void fib_node_add(FibNode *node, FibNode *root)
{
    node->left        = root->left;
    root->left->right = node;
    node->right       = root;
    root->left        = node;
}

/*
 * ��˫������b���ӵ�˫������a�ĺ���
 *
 * ע�⣺ �˴�a��b����˫������
*/
static void fib_node_cat(FibNode *a, FibNode *b)
{
    FibNode *tmp;

    tmp            = a->right;
    a->right       = b->right;
    b->right->left = a;
    b->right       = tmp;
    tmp->left      = b;
}


/*
 * ����쳲�������
 */
FibHeap* fib_heap_make()
{
    FibHeap* heap;

    heap = (FibHeap *) malloc(sizeof(FibHeap));
    if (heap == NULL)
    {
        printf("Error: make FibHeap failed\n");
        return NULL;
    }

    heap->keyNum = 0;
    heap->maxDegree = 0;
    heap->min = NULL;
    heap->cons = NULL;

    return heap;
}

/*
 * ����쳲������ѵĽڵ�
 */
static FibNode* fib_node_make(Type key)
{
    FibNode * node;

    node = (FibNode *) malloc(sizeof(FibNode));
    if (node == NULL)
    {
        printf("Error: make Node failed\n");
        return NULL;
    }
    node->key    = key;
    node->degree = 0;
    node->left   = node;
    node->right  = node;
    node->parent = NULL;
    node->child  = NULL;

    return node;
}

/*
 * ���ڵ�node���뵽쳲�������heap��
 */
static void fib_heap_insert_node(FibHeap *heap, FibNode *node)
{
    if (heap->keyNum == 0)
        heap->min = node;
    else
       {
        fib_node_add(node, heap->min);
        if (node->key < heap->min->key)
            heap->min = node;
    }
    heap->keyNum++;
}

/*
 * �½���ֵΪkey�Ľڵ㣬��������뵽쳲���������
 */
void fib_heap_insert_key(FibHeap *heap, Type key)
{
    FibNode *node;

    if (heap==NULL)
        return ;

    node = fib_node_make(key);
    if (node == NULL)
        return ;

    fib_heap_insert_node(heap, node);
}

/*
 * ��h1, h2�ϲ���һ���ѣ������غϲ���Ķ�
 */
FibHeap* fib_heap_union(FibHeap *h1, FibHeap *h2)
{
    FibHeap *tmp;

    if (h1==NULL)
        return h2;
    if (h2==NULL)
        return h1;

    // ��h1Ϊ"ĸ"����h2���ӵ�h1�ϣ������Ǳ�֤h1�Ķ����󣬾����ܵ��ٲ�����
    if(h2->maxDegree > h1->maxDegree)
    {
        tmp = h1;
        h1 = h2;
        h2 = tmp;
    }

    if((h1->min) == NULL)                // h1��"��С�ڵ�"
    {
        h1->min = h2->min;
        h1->keyNum = h2->keyNum;
        free(h2->cons);
        free(h2);
    }
    else if((h2->min) == NULL)           // h1��"��С�ڵ�" && h2��"��С�ڵ�"
    {
        free(h2->cons);
        free(h2);
    }                                   // h1��"��С�ڵ�" && h2��"��С�ڵ�"
    else
    {
        // ��"h2�и�����"��ӵ�"h1"��
        fib_node_cat(h1->min, h2->min);
        if (h1->min->key > h2->min->key)
            h1->min = h2->min;
        h1->keyNum += h2->keyNum;
        free(h2->cons);
        free(h2);
    }

    return h1;
}

/*
 * ��"�ѵ���С���"�Ӹ��������Ƴ���
 * ����ζ��"����С�ڵ���������"�Ӷ����Ƴ�!
 */
static FibNode *fib_heap_remove_min(FibHeap *heap)
{
    FibNode *min = heap->min;

    if (heap->min == min->right)
        heap->min = NULL;
    else
    {
        fib_node_remove(min);
        heap->min = min->right;
    }
    min->left = min->right = min;

    return min;
}

/*
 * ��node���ӵ�root�����
 */
static void fib_heap_link(FibHeap * heap, FibNode * node, FibNode *root)
{
    // ��node��˫�������Ƴ�
    fib_node_remove(node);
    // ��node��Ϊroot�ĺ���
    if (root->child == NULL)
        root->child = node;
    else
        fib_node_add(node, root->child);

    node->parent = root;
    root->degree++;
    node->marked = 0;
}

/*
 * ����fib_heap_consolidate����ռ�
 */
static void fib_heap_cons_make(FibHeap * heap)
{
    int old = heap->maxDegree;

    // ����log2(x)��"+1"��ζ������ȡ����
    // ex. log2(13) = 3������ȡ��Ϊ3+1=4��
    heap->maxDegree = LOG2(heap->keyNum) + 1;

    // ���ԭ���ռ䲻�������ٴη����ڴ�
    if (old >= heap->maxDegree)
        return ;

    // ��Ϊ��Ϊheap->maxDegree���ܱ��ϲ�������ҪmaxDegree+1
    heap->cons = (FibNode **)realloc(heap->cons,
            sizeof(FibHeap *) * (heap->maxDegree + 1));
}

/*
 * �ϲ�쳲������ѵĸ�������������ͬ��������
 */
static void fib_heap_consolidate(FibHeap *heap)
{
    int i, d, D;
    FibNode *x, *y, *tmp;

    fib_heap_cons_make(heap);//���ٹ�ϣ���ÿռ�
    D = heap->maxDegree + 1;

    for (i = 0; i < D; i++)
        heap->cons[i] = NULL;

    // �ϲ���ͬ�ȵĸ��ڵ㣬ʹÿ����������Ψһ
    while (heap->min != NULL)
    {
        x = fib_heap_remove_min(heap);    // ȡ�����е���С��(��С�ڵ����ڵ���)
        d = x->degree;                    // ��ȡ��С���Ķ���
        // heap->cons[d] != NULL����ζ����������(x��y)��"����"��ͬ��
        while (heap->cons[d] != NULL)
        {
            y = heap->cons[d];            // y��"��x�Ķ�����ͬ����"
            if (x->key > y->key)        // ��֤x�ļ�ֵ��yС
            {
                tmp = x;
                x = y;
                y = tmp;

            }
            fib_heap_link(heap, y, x);    // ��y���ӵ�x��
            heap->cons[d] = NULL;
            d++;
        }
        heap->cons[d] = x;
    }
    heap->min = NULL;

    // ��heap->cons�еĽ�����¼ӵ�������
    for (i=0; i<D; i++)
    {
        if (heap->cons[i] != NULL)
        {
            if (heap->min == NULL)
                heap->min = heap->cons[i];
            else
            {
                fib_node_add(heap->cons[i], heap->min);
                if ((heap->cons[i])->key < heap->min->key)
                    heap->min = heap->cons[i];
            }
        }
    }
}

/*
 * �Ƴ���С�ڵ㣬�������Ƴ��ڵ���쳲�������
 */
FibNode* _fib_heap_extract_min(FibHeap *heap)
{
    if (heap==NULL || heap->min==NULL)
        return NULL;

    FibNode *child = NULL;
    FibNode *min = heap->min;
    // ��minÿһ������(���ӺͶ��ӵ��ֵ�)����ӵ�"쳲������ѵĸ�����"��
    while (min->child != NULL)
    {
        child = min->child;
        fib_node_remove(child);
        if (child->right == child)
            min->child = NULL;
        else
            min->child = child->right;

        fib_node_add(child, heap->min);
        child->parent = NULL;
    }

    // ��min�Ӹ��������Ƴ�
    fib_node_remove(min);
    // ��min�Ƕ���Ψһ�ڵ㣬�����öѵ���С�ڵ�ΪNULL��
    // �������öѵ���С�ڵ�Ϊһ���ǿսڵ�(min->right)��Ȼ���ٽ��е��ڡ�
    if (min->right == min)
        heap->min = NULL;
    else
    {
        heap->min = min->right;
        fib_heap_consolidate(heap);
    }
    heap->keyNum--;

    return min;
}

void fib_heap_extract_min(FibHeap *heap)
{
    FibNode *node;

    if (heap==NULL || heap->min==NULL)
        return ;

    node = _fib_heap_extract_min(heap);
    if (node!=NULL)
        free(node);
}

/*
 * ��쳲�������heap���Ƿ���ڼ�ֵΪkey�Ľڵ㣻���ڷ���1�����򷵻�0��
 */
int fib_heap_get_min(FibHeap *heap, Type *pkey)
{
    if (heap==NULL || heap->min==NULL || pkey==NULL)
        return 0;

    *pkey = heap->min->key;
    return 1;
}

/*
 * �޸Ķ���
 */
static void renew_degree(FibNode *parent, int degree)
{
    parent->degree -= degree;
    if (parent-> parent != NULL)
        renew_degree(parent->parent, degree);
}

/*
 * ��node�Ӹ��ڵ�parent���������а��������
 * ��ʹnode��Ϊ"�ѵĸ�����"�е�һԱ��
 */
static void fib_heap_cut(FibHeap *heap, FibNode *node, FibNode *parent)
{
    fib_node_remove(node);
    renew_degree(parent, node->degree);
    // nodeû���ֵ�
    if (node == node->right)
        parent->child = NULL;
    else
        parent->child = node->right;

    node->parent = NULL;
    node->left = node->right = node;
    node->marked = 0;
    // ��"node������"��ӵ�"������"��
    fib_node_add(node, heap->min);
}

/*
 * �Խڵ�node����"��������"
 *
 * �������У������С��Ľ���ƻ�����С�����ʣ�
 *     �����������(��������˫��������ɾ��������
 *     ����뵽����С�����ڵ��γɵ�˫��������)��
 *     Ȼ���ٴ�"���нڵ�ĸ��ڵ�"�����������ڵ�ݹ�ִ�м�����֦
 */
static void fib_heap_cascading_cut(FibHeap *heap, FibNode *node)
{
    FibNode *parent = node->parent;
    if (parent != NULL)
        return ;

    if (node->marked == 0)
        node->marked = 1;
    else
    {
        fib_heap_cut(heap, node, parent);
        fib_heap_cascading_cut(heap, parent);
    }
}

/*
 * ��쳲�������heap�нڵ�node��ֵ����Ϊkey
 */
static void fib_heap_decrease(FibHeap *heap, FibNode *node, Type key)
{
    FibNode *parent;

    if (heap==NULL || heap->min==NULL ||node==NULL)
        return ;

    if ( key>=node->key)
    {
        printf("decrease failed: the new key(%d) is no smaller than current key(%d)\n", key, node->key);
        return ;
    }

    node->key = key;
    parent = node->parent;
    if (parent!=NULL && node->key < parent->key)
    {
        // ��node�Ӹ��ڵ�parent�а������������node��ӵ���������
        fib_heap_cut(heap, node, parent);
        fib_heap_cascading_cut(heap, parent);
    }

    // ������С�ڵ�
    if (node->key < heap->min->key)
        heap->min = node;
}

/*
 * ��쳲�������heap�нڵ�node��ֵ����Ϊkey
 */
static void fib_heap_increase(FibHeap *heap, FibNode *node, Type key)
{
    FibNode *child, *parent, *right;

    if (heap==NULL || heap->min==NULL ||node==NULL)
        return ;

    if (key <= node->key)
    {
        printf("increase failed: the new key(%d) is no greater than current key(%d)\n", key, node->key);
        return ;
    }

    // ��nodeÿһ������(����������,����,...)����ӵ�"쳲������ѵĸ�����"��
    while (node->child != NULL)
    {
        child = node->child;
        fib_node_remove(child);               // ��child��node����������ɾ��
        if (child->right == child)
            node->child = NULL;
        else
            node->child = child->right;

        fib_node_add(child, heap->min);       // ��child��ӵ���������
        child->parent = NULL;
    }
    node->degree = 0;
    node->key = key;

    // ���node���ڸ������У�
    //     ��node�Ӹ��ڵ�parent���������а��������
    //     ��ʹnode��Ϊ"�ѵĸ�����"�е�һԱ��
    //     Ȼ�����"��������"
    // �������ж��Ƿ���Ҫ���¶ѵ���С�ڵ�
    parent = node->parent;
    if(parent != NULL)
    {
        fib_heap_cut(heap, node, parent);
        fib_heap_cascading_cut(heap, parent);
    }
    else if(heap->min == node)
    {
        right = node->right;
        while(right != node)
        {
            if(node->key > right->key)
                heap->min = right;
            right = right->right;
        }
    }
}

/*
 * ���¶����heap�Ľڵ�node�ļ�ֵΪkey
 */
void _fib_heap_update(FibHeap *heap, FibNode *node, Type key)
{
    if(key < node->key)
        fib_heap_decrease(heap, node, key);
    else if(key > node->key)
        fib_heap_increase(heap, node, key);
    else
        printf("No need to update!!!\n");
}

void fib_heap_update(FibHeap *heap, Type oldkey, Type newkey)
{
    FibNode *node;

    if (heap==NULL)
        return ;

    node = fib_heap_search(heap, oldkey);
    if (node!=NULL)
        _fib_heap_update(heap, node, newkey);
}

/*
 * ����С��root�в��Ҽ�ֵΪkey�Ľڵ�
 */
static FibNode* fib_node_search(FibNode *root, Type key)
{
    FibNode *t = root;    // ��ʱ�ڵ�
    FibNode *p = NULL;    // Ҫ���ҵĽڵ�

    if (root==NULL)
        return root;

    do
    {
        if (t->key == key)
        {
            p = t;
            break;
        }
        else
        {
            if ((p = fib_node_search(t->child, key)) != NULL)
                break;
        }
        t = t->right;
    } while (t != root);

    return p;
}

/*
 * ��쳲�������heap�в��Ҽ�ֵΪkey�Ľڵ�
 */
static FibNode *fib_heap_search(FibHeap *heap, Type key)
{
    if (heap==NULL || heap->min==NULL)
        return NULL;

    return fib_node_search(heap->min, key);
}

/*
 * ��쳲�������heap���Ƿ���ڼ�ֵΪkey�Ľڵ㡣
 * ���ڷ���1�����򷵻�0��
 */
int fib_heap_contains(FibHeap *heap, Type key)
{
    return fib_heap_search(heap,key)!=NULL ? 1: 0;
}

/*
 * ɾ�����node
 */
static void _fib_heap_delete(FibHeap *heap, FibNode *node)
{
    Type min = heap->min->key;
    fib_heap_decrease(heap, node, min-1);
    _fib_heap_extract_min(heap);
    free(node);
}

void fib_heap_delete(FibHeap *heap, Type key)
{
    FibNode *node;

    if (heap==NULL || heap->min==NULL)
        return ;

    node = fib_heap_search(heap, key);
    if (node==NULL)
        return ;

    _fib_heap_delete(heap, node);
}

/*
 * ����쳲�������
 */
static void fib_node_destroy(FibNode *node)
{
    FibNode *start = node;

    if(node == NULL)
        return;

    do {
        fib_node_destroy(node->child);
        // ����node������nodeָ����һ��
        node = node->right;
        free(node->left);
    } while(node != start);
}

void fib_heap_destroy(FibHeap *heap)
{
    fib_node_destroy(heap->min);
    free(heap->cons);
    free(heap);
}

/*
 * ��ӡ"쳲�������"
 *
 * ����˵����
 *     node       -- ��ǰ�ڵ�
 *     prev       -- ��ǰ�ڵ��ǰһ���ڵ�(���ڵ�or�ֵܽڵ�)
 *     direction  --  1����ʾ��ǰ�ڵ���һ������;
 *                    2����ʾ��ǰ�ڵ���һ���ֵܽڵ㡣
 */
static void _fib_print(FibNode *node, FibNode *prev, int direction)
{
    FibonacciNode *start=node;

    if (node==NULL)
        return ;
    do
    {
        if (direction == 1)
            printf("%8d(%d) is %2d's child\n", node->key, node->degree, prev->key);
        else
            printf("%8d(%d) is %2d's next\n", node->key, node->degree, prev->key);

        if (node->child != NULL)
            _fib_print(node->child, node, 1);

        // �ֵܽڵ�
        prev = node;
        node = node->right;
        direction = 2;
    } while(node != start);
}

void fib_print(FibHeap *heap)
{
    int i=0;
    FibonacciNode *p;

    if (heap==NULL || heap->min==NULL)
        return ;

    printf("== 쳲������ѵ���ϸ��Ϣ: ==\n");
    p = heap->min;
    do {
        i++;
        printf("%2d. %4d(%d) is root\n", i, p->key, p->degree);

        _fib_print(p->child, p, 1);
        p = p->right;
    } while (p != heap->min);
    printf("\n");
}
