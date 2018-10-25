/**
 * C����ʵ�ֵ�쳲�������
 *
 * @author skywang
 * @date 2014/04/06
 */

#include <stdio.h>
#include "fibonacci_heap.h"

#define DEBUG 0

#if DEBUG
#define log(x, ...)   printf(x, __VA_ARGS__)
#else
#define log(x, ...)
#endif

#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )

// ��8��
int a[] = {12,  7, 25, 15, 28,
           33, 41, 1};
// ��14��
int b[] = {18, 35, 20, 42,  9,
           31, 23,  6, 48, 11,
           24, 52, 13, 2};

// ��֤"������Ϣ(쳲������ѵĽṹ)"
void test_basic()
{
    int i;
    int blen=LENGTH(b);
    FibHeap *hb = fib_heap_make();

    // 쳲�������hb
    printf("== 쳲�������(hb)���������: ");
    for(i=0; i<blen; i++)
    {
        printf("%d ", b[i]);
        fib_heap_insert_key(hb, b[i]);
    }
    printf("\n");
    printf("== 쳲�������(hb)ɾ����С�ڵ�\n");
    fib_heap_extract_min(hb);
    fib_print(hb);

    fib_heap_destroy(hb);
}

// ��֤"�������"
void test_insert()
{
    int i;
    int alen=LENGTH(a);
    FibHeap *ha = fib_heap_make();

    // 쳲�������ha
    printf("== 쳲�������(ha)���������: ");

    for(i=0; i<alen; i++)
    {
        printf("%d ", a[i]);
        fib_heap_insert_key(ha, a[i]);
    }
    printf("\n");
    printf("== 쳲�������(ha)ɾ����С�ڵ�\n");
    fib_heap_extract_min(ha);
    fib_print(ha);

    // ����50
    printf("== ����50\n");
    fib_heap_insert_key(ha, 50);
    fib_print(ha);

    fib_heap_destroy(ha);
}

// ��֤"�ϲ�����"
void test_union()
{
    int i;
    int alen=LENGTH(a);
    int blen=LENGTH(b);
    FibHeap *ha = fib_heap_make();
    FibHeap *hb = fib_heap_make();

    // 쳲�������ha
    printf("== 쳲�������(ha)���������: ");

    for(i=0; i<alen; i++)
    {
        printf("%d ", a[i]);
        fib_heap_insert_key(ha, a[i]);
    }
    printf("\n");
    printf("== 쳲�������(ha)ɾ����С�ڵ�\n");
    fib_heap_extract_min(ha);
    fib_print(ha);

    // 쳲�������hb
    printf("== 쳲�������(hb)���������: ");
    for(i=0; i<blen; i++)
    {
        printf("%d ", b[i]);
        fib_heap_insert_key(hb, b[i]);
    }
    printf("\n");
    printf("== 쳲�������(hb)ɾ����С�ڵ�\n");
    fib_heap_extract_min(hb);
    fib_print(hb);

    // ��"쳲�������hb"�ϲ���"쳲�������ha"�С�
    printf("== �ϲ�ha��hb\n");
    ha = fib_heap_union(ha, hb);
    fib_print(ha);

    // ���ٶ�
    fib_heap_destroy(ha);
}

// ��֤"ɾ����С�ڵ�"
void test_remove_min()
{
    int i;
    int alen=LENGTH(a);
    int blen=LENGTH(b);
    FibHeap *ha = fib_heap_make();
    FibHeap *hb = fib_heap_make();

    // 쳲�������ha
    printf("== 쳲�������(ha)���������: ");

    for(i=0; i<alen; i++)
    {
        printf("%d ", a[i]);
        fib_heap_insert_key(ha, a[i]);
    }
    printf("\n");
    printf("== 쳲�������(ha)ɾ����С�ڵ�\n");
    fib_heap_extract_min(ha);
    //fib_print(ha);

    // 쳲�������hb
    printf("== 쳲�������(hb)���������: ");
    for(i=0; i<blen; i++)
    {
        printf("%d ", b[i]);
        fib_heap_insert_key(hb, b[i]);
    }
    printf("\n");
    printf("== 쳲�������(hb)ɾ����С�ڵ�\n");
    fib_heap_extract_min(hb);
    //fib_print(hb);

    // ��"쳲�������hb"�ϲ���"쳲�������ha"�С�
    printf("== �ϲ�ha��hb\n");
    ha = fib_heap_union(ha, hb);
    fib_print(ha);

    printf("== ɾ����С�ڵ�\n");
    fib_heap_extract_min(ha);
    fib_print(ha);

    // ���ٶ�
    fib_heap_destroy(ha);
}

// ��֤"��С�ڵ�"
void test_decrease()
{
    int i;
    int blen=LENGTH(b);
    FibHeap *hb = fib_heap_make();

    // 쳲�������hb
    printf("== 쳲�������(hb)���������: ");
    for(i=0; i<blen; i++)
    {
        printf("%d ", b[i]);
        fib_heap_insert_key(hb, b[i]);
    }
    printf("\n");
    printf("== 쳲�������(hb)ɾ����С�ڵ�\n");
    fib_heap_extract_min(hb);
    fib_print(hb);

    printf("== ��20��СΪ2\n");
    fib_heap_update(hb, 20, 2);
    fib_print(hb);

    fib_heap_destroy(hb);
}

// ��֤"����ڵ�"
void test_increase()
{
    int i;
    int blen=LENGTH(b);
    FibHeap *hb = fib_heap_make();

    // 쳲�������hb
    printf("== 쳲�������(hb)���������: ");
    for(i=0; i<blen; i++)
    {
        printf("%d ", b[i]);
        fib_heap_insert_key(hb, b[i]);
    }
    printf("\n");
    printf("== 쳲�������(hb)ɾ����С�ڵ�\n");
    fib_heap_extract_min(hb);
    fib_print(hb);

    fib_heap_update(hb, 20, 60);
    printf("== ��20����Ϊ60\n");
    fib_print(hb);

    fib_heap_destroy(hb);
}

// ��֤"ɾ���ڵ�"
void test_delete()
{
    int i;
    int blen=LENGTH(b);
    FibHeap *hb = fib_heap_make();

    // 쳲�������hb
    printf("== 쳲�������(hb)���������: ");
    for(i=0; i<blen; i++)
    {
        printf("%d ", b[i]);
        fib_heap_insert_key(hb, b[i]);
    }
    printf("\n");
    printf("== 쳲�������(hb)ɾ����С�ڵ�\n");
    fib_heap_extract_min(hb);
    fib_print(hb);

    fib_heap_delete(hb, 20);
    printf("== ɾ���ڵ�20\n");
    fib_print(hb);

    fib_heap_destroy(hb);
}

void main()
{
    // ��֤"������Ϣ(쳲������ѵĽṹ)"
    test_basic();
    // ��֤"�������"
    //test_insert();
    // ��֤"�ϲ�����"
    //test_union();
    // ��֤"ɾ����С�ڵ�"
    //test_remove_min();
    // ��֤"��С�ڵ�"
    //test_decrease();
    // ��֤"����ڵ�"
    //test_increase();
    // ��֤"ɾ���ڵ�"
    //test_delete();
}
