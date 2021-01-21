#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

typedef struct QNode
{
    ElemType data;
    struct QNode *next;
} QNode, *QueuePtr;

typedef struct
{
    QueuePtr front, rear;
} LinkQueue;

initQueue(LinkQueue *q)
{
    q->front = q->rear = (QueuePtr)malloc(sizeof(QNode));
    if( !q->front )
        exit(0);

    q->front->next = NULL;
}

InsertQueue(LinkQueue *q, ElemType e)
{
    QueuePtr p;

    p = (QueuePtr)malloc(sizeof(QNode));
    if( !q->front )
        exit(0);

    p->data = e;
    p->next = NULL;
    q->rear->next = p;
    q->rear = p;
}

DeleteQueue(LinkQueue *q, ElemType *e)
{
    QueuePtr p;

    if( q->front == q->rear )
        return;

    p = q->front->next;
    *e = p->data;
    q->front->next = p->next;

    if( q->rear == p )
    {
        q->rear = q->front;
    }

    free(p);
}

int main()
{
    ElemType e;
    LinkQueue q;

    initQueue(&q);
    printf("������һ���ַ������Ծ��ż��������룺");
    scanf("%c", &e);

    while( e != '#' )
    {
        InsertQueue( &q, e );
        scanf("%c", &e);
    }

    printf("��ӡ�����е�Ԫ�أ�");
    while( q.front != q.rear )
    {
        DeleteQueue( &q, &e );
        printf("%c", e);
    }

    return 0;
}
