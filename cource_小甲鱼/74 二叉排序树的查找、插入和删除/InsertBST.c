// ������������ T �в����ڹؼ��ֵ��� key ������Ԫ��ʱ��
// ���� key ������ TRUE�����򷵻� FALSE
Status InsertBST(BiTree *T, int key)
{
    BiTree p, s;
    if( !SearchBST(*T, key, NULL, &p) )
    {
        s = (BiTree)malloc(sizeof(BiTNode));
        s->data = key;
        s->lchild = s->rchild = NULL;
        
        if( !p )       
        {
            *T = s;     // ���� s Ϊ�µĸ����
        }
        else if( key < p->data )
        {
            p->lchild = s;  // ���� s Ϊ����
        }
        else
        {
            p->rchild = s;  // ���� s Ϊ�Һ���
        }
        return TRUE;
    }
    else
    {
        return FALSE;   // �������йؼ�����ͬ�Ľ�㣬���ٲ���
    }
}