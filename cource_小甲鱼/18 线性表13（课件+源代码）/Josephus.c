//n����ΧȦ��������m���У����ʣ�µ��Ǽ��ţ�
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node *next;
}node;

node *create(int n)
{
	node *p = NULL, *head;
	head = (node*)malloc(sizeof (node ));
	p = head;
	node *s;
	int i = 1;

	if( 0 != n )
	{
		while( i <= n )
		{
			s = (node *)malloc(sizeof (node));
			s->data = i++;    // Ϊѭ�������ʼ������һ�����Ϊ1���ڶ������Ϊ2��
			p->next = s;
			p = s;
		}
		s->next = head->next;
	}

	free(head);

	return s->next ;
}

int main()
{
	int n = 41;
	int m = 3;
	int i;
	node *p = create(n);
	node *temp;

	m %= n;   // m�������ǵ���2

	while (p != p->next )
	{
		for (i = 1; i < m-1; i++)
		{
			p = p->next ;
		}

		printf("%d->", p->next->data );

		temp = p->next ;				//ɾ����m���ڵ�
		p->next = temp->next ;
		free(temp);

		p = p->next ;
	}

	printf("%d\n", p->data );

	return 0;
}
