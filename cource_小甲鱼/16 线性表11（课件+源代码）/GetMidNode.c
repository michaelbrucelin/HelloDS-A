Status GetMidNode(LinkList L, ElemType *e)
{
    LinkList search, mid;
    mid = search = L;

    while (search->next != NULL)
    {
        //search�ƶ����ٶ��� mid ��2��
        if (search->next->next != NULL)
        {
            search = search->next->next;
            mid = mid->next;
        }
        else
        {
            search = search->next;
        }
    }

    *e = mid->data;

    return OK;
}
