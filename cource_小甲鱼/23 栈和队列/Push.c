#define SATCKINCREMENT 10

Push(sqStack *s, ElemType e)
{
    // ���ջ����׷�ӿռ�
    if( s->top �C s->base >= s->stackSize )
    {
        s->base = (ElemType *)realloc(s->base, (s->stackSize + STACKINCREMENT) * sizeof(ElemType));
        if( !s->base )
            exit(0);

        s->top = s->base + s->stackSize;              // ����ջ��
        s->stackSize = s->stackSize + STACKINCREMENT; // ����ջ���������
    }

    *(s->top) = e;
    s->top++;
}
