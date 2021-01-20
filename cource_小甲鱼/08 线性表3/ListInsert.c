/* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1<=i<=ListLength(L)�� */
/* �����������L�е�i��λ��֮ǰ�����µ�����Ԫ��e��L����+1��*/

Status ListInsert(SqList *L, int i, ElemType e)
{
    int k;

    if( L->length == MAXSIZE )  // ˳�����Ա��Ѿ�����
    {
        return ERROR;
    }
    if( i<1 || i>L->length+1)   // ��i���ڷ�Χ��ʱ
    {
        return ERROR;
    }
    if( i <= L->length )   // ����������λ�ò��ڱ�β
    {
        /* ��Ҫ����λ�ú�����Ԫ������ƶ�һλ */
        for( k=L->length-1; k >= i-1; k-- )
        {
            L->data[k+1] = L->data[k];
        }
    }

    L->data[i-1] = e;  // ����Ԫ�ز���
    L->length++;

    return OK;
}
