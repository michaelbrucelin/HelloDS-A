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