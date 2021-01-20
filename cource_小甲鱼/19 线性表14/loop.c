#include "stdio.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef int ElemType;/* ElemType���͸���ʵ������������������Ϊint */

typedef struct Node
{
    ElemType data;
    struct Node *next;
}Node, *LinkList;

/* ��ʼ����ͷ���Ŀ����� */
Status InitList(LinkList *L)
{
    *L = (LinkList)malloc(sizeof(Node)); /* ����ͷ���,��ʹLָ���ͷ��� */

    if(!(*L)) /* �洢����ʧ�� */
            return ERROR;

    (*L)->next=NULL; /* ָ����Ϊ�� */

    return OK;
}

/* ��ʼ������˳�����Ա�L�Ѵ��ڡ��������������L������Ԫ�ظ��� */
int ListLength(LinkList L)
{
    int i=0;
    LinkList p=L->next; /* pָ���һ����� */
    while(p)
    {
        i++;
        p=p->next;
    }
    return i;
}

/*  �������n��Ԫ�ص�ֵ����������ͷ���ĵ������Ա�L��ͷ�巨�� */
void CreateListHead(LinkList *L, int n)
{
	LinkList p;
	int i;

	srand(time(0));                         /*  ��ʼ����������� */

	*L = (LinkList)malloc(sizeof(Node));
	(*L)->next = NULL;                      /*  ����һ����ͷ���ĵ����� */

	for (i=0; i < n; i++)
	{
		p = (LinkList)malloc(sizeof(Node)); /*  �����½�� */
		p->data = rand()%100+1;             /*  �������100���ڵ����� */
		p->next = (*L)->next;
		(*L)->next = p;						/*  ���뵽��ͷ */
	}
}

/*  �������n��Ԫ�ص�ֵ����������ͷ���ĵ������Ա�L��β�巨�� */
void CreateListTail(LinkList *L, int n)
{
	LinkList p,r;
	int i;

	srand(time(0));                      /* ��ʼ����������� */
	*L = (LinkList)malloc(sizeof(Node)); /* LΪ�������Ա� */
	r = *L;                              /* rΪָ��β���Ľ�� */

	for (i=0; i < n; i++)
	{
		p = (Node *)malloc(sizeof(Node)); /*  �����½�� */
		p->data = rand()%100+1;           /*  �������100���ڵ����� */
		r->next=p;                        /* ����β�ն˽���ָ��ָ���½�� */
		r = p;                            /* ����ǰ���½�㶨��Ϊ��β�ն˽�� */
	}

    r->next = (*L)->next->next;
}

// �Ƚϲ����ķ���
int HasLoop1(LinkList L)
{
    LinkList cur1 = L;  // ������ cur1
    int pos1 = 0;       // cur1 �Ĳ���

    while(cur1)
    {                       // cur1 ������
        LinkList cur2 = L;  // ������ cur2
        int pos2 = 0;       // cur2 �Ĳ���
        while(cur2)
        {                           // cur2 ��㲻Ϊ��
            if(cur2 == cur1)
            {                       // ��cur1��cur2������ͬ���ʱ
                if(pos1 == pos2)    // �߹��Ĳ���һ��
                    break;          // ˵��û�л�
                else                // ����
                {
                    printf("����λ���ڵ�%d����㴦��\n\n", pos2);
                    return 1;       // �л�������1
                }
            }
            cur2 = cur2->next;      // ���û���ֻ���������һ�����
            pos2++;                 // cur2 ��������
        }
        cur1 = cur1->next;  // cur1�������һ�����
        pos1++;             // cur1 ��������
    }
    return 0;
}

// ���ÿ���ָ��ķ���
int HasLoop2(LinkList L)
{
    int step1 = 1;
    int step2 = 2;
    LinkList p = L;
    LinkList q = L;

    while (p != NULL && q != NULL && q->next != NULL)
    {
        p = p->next;
        if (q->next != NULL)
            q = q->next->next;

        printf("p:%d, q:%d \n", p->data, q->data);

        if (p == q)
            return 1;
    }
    return 0;
}

int main()
{
    LinkList L;
    Status i;
    char opp;
    ElemType e;
    int find;
    int tmp;

    i = InitList(&L);
    printf("��ʼ��L��ListLength(L)=%d\n",ListLength(L));

    printf("\n1.�����л�����β�巨�� \n2.�����޻�����ͷ�巨�� \n3.�ж������Ƿ��л� \n0.�˳� \n\n��ѡ����Ĳ�����\n");
    while(opp != '0')
    {
        scanf("%c",&opp);
        switch(opp)
        {
            case '1':
                CreateListTail(&L, 10);
                printf("�ɹ������л�L(β�巨)\n");
                printf("\n");
                break;

            case '2':
                CreateListHead(&L, 10);
                printf("�ɹ������޻�L(ͷ�巨)\n");
                printf("\n");
                break;

            case '3':
                printf("����һ: \n\n");
                if( HasLoop1(L) )
                {
                    printf("���ۣ������л�\n\n\n");
                }
                else
                {
                    printf("���ۣ������޻�\n\n\n");
                }

                printf("��������\n\n");
                if( HasLoop2(L) )
                {
                    printf("���ۣ������л�\n\n\n");
                }
                else
                {
                    printf("���ۣ������޻�\n\n\n");
                }
                printf("\n");
                break;

            case '0':
                exit(0);
        }
    }

}
