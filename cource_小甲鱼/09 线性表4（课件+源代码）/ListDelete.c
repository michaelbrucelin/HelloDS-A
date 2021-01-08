/* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1<=i<=ListLength(L) */
/* ���������ɾ��L�ĵ�i������Ԫ�أ�����e������ֵ��L�ĳ���-1 */
Status ListDelete(SqList *L, int i, ElemType *e)
{
    int k;

    if( L->length == 0 )
    {
        return ERROR;
    }
    if( i<1 || i>L->length )
    {
        return ERROR;
    }

    *e = L->data[i-1];

    if( i < L->length )
    {
        for( k=i; k < L->length; k++ )
        {
            L->data[k-1] = L->data[k];
        }
    }

    L->length--;

    return OK;
}
