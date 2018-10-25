/**
 * ��������C ����
 *
 * @author skywang
 * @date 2014/03/15
 */

#include <stdio.h>

// ���鳤��
#define LENGTH(array) ( (sizeof(array)) / (sizeof(array[0])) )

/*
 * ��ȡ����a�����ֵ
 *
 * ����˵����
 *     a -- ����
 *     n -- ���鳤��
 */
int get_max(int a[], int n)
{
    int i, max;

    max = a[0];
    for (i = 1; i < n; i++)
        if (a[i] > max)
            max = a[i];
    return max;
}

/*
 * �����鰴��"ĳ��λ��"��������(Ͱ����)
 *
 * ����˵����
 *     a -- ����
 *     n -- ���鳤��
 *     exp -- ָ����������a���ո�ָ����������
 *
 * ���磬��������a={50, 3, 542, 745, 2014, 154, 63, 616}��
 *    (01) ��exp=1��ʾ����"��λ"������a��������
 *    (02) ��exp=10��ʾ����"ʮλ"������a��������
 *    (03) ��exp=100��ʾ����"��λ"������a��������
 *    ...
 */
void count_sort(int a[], int n, int exp)
{
    int output[n];             // �洢"����������"����ʱ����
    int i, buckets[10] = {0};

    // �����ݳ��ֵĴ����洢��buckets[]��
    for (i = 0; i < n; i++)
        buckets[ (a[i]/exp)%10 ]++;

    // ����buckets[i]��Ŀ�����ø��ĺ��buckets[i]��ֵ���Ǹ�������output[]�е�λ�á�
    for (i = 1; i < 10; i++)
        buckets[i] += buckets[i - 1];

    // �����ݴ洢����ʱ����output[]��
    for (i = n - 1; i >= 0; i--)
    {
        output[buckets[ (a[i]/exp)%10 ] - 1] = a[i];
        buckets[ (a[i]/exp)%10 ]--;
    }

    // ������õ����ݸ�ֵ��a[]
    for (i = 0; i < n; i++)
        a[i] = output[i];
}

/*
 * ��������
 *
 * ����˵����
 *     a -- ����
 *     n -- ���鳤��
 */
void radix_sort(int a[], int n)
{
    int exp;    // ָ�����������鰴��λ��������ʱ��exp=1����ʮλ��������ʱ��exp=10��...
    int max = get_max(a, n);    // ����a�е����ֵ

    // �Ӹ�λ��ʼ��������a��"ָ��"��������
    for (exp = 1; max/exp > 0; exp *= 10)
        count_sort(a, n, exp);
}

void main()
{
    int i;
    int a[] = {53, 3, 542, 748, 14, 214, 154, 63, 616};
    int ilen = LENGTH(a);

    printf("before sort:");
    for (i=0; i<ilen; i++)
        printf("%d ", a[i]);
    printf("\n");

    radix_sort(a, ilen);

    printf("after  sort:");
    for (i=0; i<ilen; i++)
        printf("%d ", a[i]);
    printf("\n");
}
