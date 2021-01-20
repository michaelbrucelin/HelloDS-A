// �������Ķ���������ṹ����
typedef struct BiTNode
{
    int data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

// �ݹ���Ҷ��������� T ���Ƿ���� key
// ָ�� f ָ�� T ��˫�ף����ʼֵ����ֵΪ NULL
// �����ҳɹ�����ָ�� p ָ�������Ԫ�ؽ�㣬������ TRUE
// ����ָ�� p ָ�����·���Ϸ��ʵ����һ����㣬������ FALSE
Status SearchBST(BiTree T, int key, BiTree f, BiTree *p)
{
    if( !T )    // ���Ҳ��ɹ�
    {
        *p = f;
        return FALSE;
    }
    else if( key == T->data )   // ���ҳɹ�
    {
        *p = T;
        return TRUE;
    }
    else if( key < T->data )
    {
        return SearchBST( T->lchild, key, T, p );   // ����������������
    }
    else
    {
        return SearchBST( T->rchild, key, T, p );   // ����������������
    }
}