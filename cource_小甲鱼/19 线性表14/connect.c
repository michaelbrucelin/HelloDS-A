//����A��BΪ�ǿ�ѭ�������βָ��
LinkList Connect(LinkList A,LinkList B)
{	
	LinkList p = A->next;		//����A���ͷ���λ��
	
	A->next = B->next->next;	//B��Ŀ�ʼ������ӵ�A��β
	
	free(B->next);	//�ͷ�B���ͷ���,��ѧ����������
	
	B->next = p;		
	
	return B;		//������ѭ�������βָ��
} 
