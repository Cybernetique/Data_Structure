/**
 * C����ʵ�ֵ������
 *
 * @author skywang
 * @date 2014/03/31
 */

#include <stdio.h>
#include "leftist.h"

#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )

void main()
{
    int i;
    int a[]= {10,40,24,30,36,20,12,16};
    int b[]= {17,13,11,15,19,21,23};
    int alen=LENGTH(a);
    int blen=LENGTH(b);
    LeftistHeap ha,hb;

    ha=hb=NULL;

    printf("== �����(ha)���������: ");
    for(i=0; i<alen; i++)
    {
        printf("%d ", a[i]);
        ha = insert_leftist(ha, a[i]);
    }
    printf("\n== �����(ha)����ϸ��Ϣ: \n");
    print_leftist(ha);


    printf("\n== �����(hb)���������: ");
    for(i=0; i<blen; i++)
    {
        printf("%d ", b[i]);
        hb = insert_leftist(hb, b[i]);
    }
    printf("\n== �����(hb)����ϸ��Ϣ: \n");
    print_leftist(hb);

    // ��"�����hb"�ϲ���"�����ha"�С�
    ha = merge_leftist(ha, hb);
    printf("\n== �ϲ�ha��hb�����ϸ��Ϣ: \n");
    print_leftist(ha);


    // ���������
    destroy_leftist(ha);
}
