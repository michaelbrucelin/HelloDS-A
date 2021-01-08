#include <stdio.h>
#include <stdlib.h>

/*����洢�ṹ�Ķ���*/
typedef struct CLinkList
{
    int data;
    struct CLinkList *next;
}node;

/************************************************************************/
/* ����                                                                  */
/************************************************************************/

/*��ʼ��ѭ������*/
void ds_init(node **pNode)
{
    int item;
    node *temp;
    node *target;

    printf("�������ֵ������0��ɳ�ʼ��\n");

	while(1)
	{
        scanf("%d", &item);
        fflush(stdin);

		if(item == 0)
            return;

        if((*pNode) == NULL)
		{ /*ѭ��������ֻ��һ�����*/
			*pNode = (node*)malloc(sizeof(struct CLinkList));
			if(!(*pNode))
				exit(0);
			(*pNode)->data = item;
			(*pNode)->next = *pNode;
		}
        else
		{
            /*�ҵ�nextָ���һ�����Ľ��*/
            for(target = (*pNode); target->next != (*pNode); target = target->next)
				;

            /*����һ���µĽ��*/
            temp = (node *)malloc(sizeof(struct CLinkList));

			if(!temp)
				exit(0);

			temp->data = item;
            temp->next = *pNode;
            target->next = temp;
        }
    }
}

/*������*/
/*����������ĵ�һ����㣬�����λ��*/
void ds_insert(node **pNode , int i)
{
    node *temp;
    node *target;
    node *p;
    int item;
    int j = 1;

    printf("����Ҫ�������ֵ:");
    scanf("%d", &item);

    if(i == 1)
	{ //�²���Ľ����Ϊ��һ�����
        temp = (node *)malloc(sizeof(struct CLinkList));

		if(!temp)
            exit(0);

		temp ->data = item;

        /*Ѱ�ҵ����һ�����*/
        for(target = (*pNode); target->next != (*pNode); target = target->next)
			;

		temp->next = (*pNode);
        target->next = temp;
        *pNode = temp;
    }
    else
	{
        target = *pNode;

        for( ; j < (i-1); ++j )
		{
			target=target->next;
		}

		temp = (node *)malloc(sizeof(struct CLinkList));

		if(!temp)
            exit(0);

		temp ->data = item;
        p = target->next;
        target->next = temp;
        temp->next = p;
    }
}

/*ɾ�����*/
void ds_delete(node **pNode, int i)
{
    node *target;
    node *temp;
    int j = 1;

    if(i == 1)
	{ //ɾ�����ǵ�һ�����
        /*�ҵ����һ�����*/
        for(target = *pNode; target->next != *pNode;target = target->next)
			;

		temp = *pNode;
        *pNode = (*pNode)->next;
        target->next = *pNode;
        free(temp);
    }
    else
	{
        target = *pNode;

		for( ; j < i-1; ++j )
		{
			target = target->next;
		}

		temp = target->next;
        target->next = temp->next;
        free(temp);
    }
}

/*���ؽ������λ��*/
int ds_search(node *pNode, int elem)
{
    node *target;
    int i = 1;

    for(target = pNode; target->data != elem && target->next != pNode; ++i)
	{
		target = target->next;
	}

	if(target->next == pNode) /*���в����ڸ�Ԫ��*/
        return 0;
    else
        return i;
}

/*����*/
void ds_traverse(node *pNode)
{
    node *temp;
    temp = pNode;
    printf("***********�����е�Ԫ��******************\n");

	do
	{
        printf("%4d ", temp->data);
    }while((temp = temp->next) != pNode);

	printf("\n");
}

int main()
{
    node *pHead = NULL;
    char opp;
    int find;

    printf("------------------- �� �� λ �� �� --------------------\n\n");
    printf("��ӭ������C��̳�ʹ��һ����������http://bbs.fishc.com\n\n");
    printf("ϲ����C�ͼ����Ϊ����VIP��Ա�ɣ�http://fishc.taobao.com\n\n");
    printf("-------------------------------------------------------\n\n");
    printf("1.��ʼ������ \n\n2.������ \n\n3.ɾ����� \n\n4.���ؽ��λ�� \n\n5.��������  \n\n0.�˳� \n\n��ѡ����Ĳ�����");
    while(opp != '0')
	{
        scanf("%c", &opp);
        switch(opp)
		{
            case '1':
                ds_init(&pHead);
                printf("\n");
                ds_traverse(pHead);
                break;

            case '2':
                printf("������Ҫ�������λ�ã�");
                scanf("%d",  &find);
                ds_insert(&pHead, find);
                printf("��λ��%d����ֵ��\n",  find);
                ds_traverse(pHead);
                printf("\n");
                break;

            case '3':
                printf("������Ҫɾ���Ľ��λ�ã�");
                scanf("%d",  &find);
                ds_delete(&pHead, find);
                printf("ɾ����%d������:\n",  find);
                ds_traverse(pHead);
                printf("\n");
                break;

            case '4':
                printf("��Ҫ���ҵ����ڼ�������ֵ��");
                scanf("%d",  &find);
                printf("Ԫ��%d����λ�ã�%d\n",  find,  ds_search(pHead, find));
                //ListTraverse(L);
                printf("\n");
                break;

            case '5':
                ds_traverse(pHead);
                printf("\n");
                break;

            case '0':
                exit(0);
        }
    }

    return 0;
}
