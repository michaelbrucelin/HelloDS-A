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

		for( ; j < i-1; ++j)
		{
			target = target->next;
		}
		
		temp = target->next;
        target->next = temp->next;
        free(temp);
    }
}