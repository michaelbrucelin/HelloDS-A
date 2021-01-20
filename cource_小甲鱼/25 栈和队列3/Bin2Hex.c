/*****************************/
/** ������/ʮ������ת����  **/
/** By www.fishc.com С���� **/
/*****************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STACK_INIT_SIZE 20
#define STACKINCREMENT  10

typedef char ElemType;
typedef struct
{
    ElemType *base;
    ElemType *top;
    int stackSize;
}sqStack;

// �������ܣ���ʼ��ջ
// ����*s��ջ�ĵ�ַ
void InitStack(sqStack *s)
{
    s->base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
    if( !s->base )
    {
        exit(0);
    }

    s->top = s->base;
    s->stackSize = STACK_INIT_SIZE;
}

// �������ܣ���ջ����
// ����*s��ջ�ĵ�ַ
// ����e����ѹ��ջ��Ԫ��
void Push(sqStack *s, ElemType e)
{
    if( s->top - s->base >= s->stackSize )
    {
        s->base = (ElemType *)realloc(s->base, (s->stackSize + STACKINCREMENT) * sizeof(ElemType));
        if( !s->base )
        {
            exit(0);
        }

        s->top = s->base + s->stackSize;
        s->stackSize = s->stackSize + STACKINCREMENT;
    }

    *(s->top) = e;
    s->top++;
}

// �������ܣ���ջ����
// ����*s��ջ�ĵ�ַ
// ����e����Ŵ�ջ�ﵯ��������
void Pop(sqStack *s, ElemType *e)
{
    if( s->top == s->base )
    {
        return;
    }
    *e = *--(s->top);
}

// �������ܣ�����ջs�ĵ�ǰ����
// ����s��ջ
int StackLen(sqStack s)
{
    return (s.top - s.base);
}

int main()
{
    ElemType c;
    sqStack s1;
    sqStack s2;
    int len, i, j, sum = 0;

    InitStack(&s1); // ��ʼ��ջs1��������Ŷ���������

    printf("������������������롮#���ű�ʾ������\n\n");
    scanf("%c", &c);
    while( c != '#' )
    {
        if( c=='0' || c=='1' )  // ��������Ƿ������
            Push(&s1, c);
        scanf("%c", &c);
    }
    getchar();      // ��'\n'�ӻ�����ȥ��
    len = StackLen(s1);

    InitStack(&s2); // ��ʼ��ջs2���������ת���İ˽���

    for( i=0; i < len; i+=4 )
    {
        for( j=0; j < 4; j++ )
        {
            Pop( &s1, &c ); // ȡ��ջ��Ԫ��
            sum = sum + (c-48) * pow(2, j);

            if( s1.base == s1.top )
            {
                break;
            }
        }

        switch( sum )
        {
            case 10: sum = 'A'; break;
            case 11: sum = 'B'; break;
            case 12: sum = 'C'; break;
            case 13: sum = 'D'; break;
            case 14: sum = 'E'; break;
            case 15: sum = 'F'; break;
            default: sum += 48;
        }

        Push( &s2, sum );
        sum = 0;
    }

    printf("\nת��Ϊʮ����������: ");
    while( s2.base != s2.top )
    {
        Pop( &s2, &c );
        printf("%c", c);
    }
    printf("(H)\n");

    return 0;
}
