/* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1<=i<=ListLength(L) */
/* ���������ɾ��L�ĵ�i������Ԫ�أ�����e������ֵ��L�ĳ���-1 */

Status ListDelete(LinkList *L, int i, ElemType *e)
{
    int j;
    LinkList p, q;

    p = *L;
    j = 1;

    while( p->next && j<i )
    {
        p = p->next;
        ++j;
    }

    if( !(p->next) || j>i )
    {
        return ERROR;
    }

    q = p->next;
    p->next = q->next;

    *e = q->data;
    free(q);

    return OK;
}
