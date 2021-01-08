#include <stdio.h>
#include <stdlib.h>
#define MAX_NODE_NUM 100
#define TRUE 1U
#define FALSE 0U

typedef struct NodeType
{
    int id;
    int cipher;
    struct NodeType *next;
} NodeType;

/* ��������ѭ������ */
static void CreaList(NodeType **, const int);
/* ����"Լɪ��"���� */
static void StatGame(NodeType **, int);
/* ��ӡѭ������ */
static void PrntList(const NodeType *);
/* �õ�һ����� */
static NodeType *GetNode(const int, const int);
/* ���������Ƿ�Ϊ��, ��ΪTRUE���ǿ�ΪFALSE */
static unsigned EmptyList(const NodeType *);

int main(void)
{
    int n, m;
    NodeType *pHead = NULL;
    while (1)
    {
        printf("����������n�����%d����: ", MAX_NODE_NUM);
        scanf("%d", &n);
        printf("�ͳ�ʼ����m: ");
        scanf("%d", &m);
        if (n > MAX_NODE_NUM)
        {
            printf("����̫�࣬���������룡\n");
            continue;
        }
        else
            break;
    }
    CreaList(&pHead, n);
    printf("\n------------ ѭ������ԭʼ��ӡ -------------\n");
    PrntList(pHead);
    printf("\n-------------ɾ�����������ӡ -------------\n");
    StatGame(&pHead, m);
}

static void CreaList(NodeType **ppHead, const int n)
{
    int i, iCipher;
    NodeType *pNew, *pCur;
    for (i = 1; i <= n; i++)
    {
        printf("�����%d���˵�����: ", i);
        scanf("%d", &iCipher);
        pNew = GetNode(i, iCipher);
        if (*ppHead == NULL)
        {
            *ppHead = pCur = pNew;
            pCur->next = *ppHead;
        }
        else
        {
            pNew->next = pCur->next;
            pCur->next = pNew;
            pCur = pNew;
        }
    }
    printf("��ɵ���ѭ������Ĵ���!\n");
}

static void StatGame(NodeType **ppHead, int iCipher)
{
    int iCounter, iFlag = 1;
    NodeType *pPrv, *pCur, *pDel;
    pPrv = pCur = *ppHead;
    /* ��pPrv��ʼΪָ��β��㣬Ϊɾ������׼�� */
    while (pPrv->next != *ppHead)
        pPrv = pPrv->next;
    while (iFlag)
    {
        for (iCounter = 1; iCounter < iCipher; iCounter++)
        {
            pPrv = pCur;
            pCur = pCur->next;
        }
        if (pPrv == pCur)
            iFlag = 0;
        pDel = pCur; /* ɾ��pCurָ��Ľ�㣬�����˳��� */
        pPrv->next = pCur->next;
        pCur = pCur->next;
        iCipher = pDel->cipher;
        printf("��%d���˳���, ����: %d\n", pDel->id, pDel->cipher);
        free(pDel);
    }
    *ppHead = NULL;
    getchar();
}

static void PrntList(const NodeType *pHead)
{
    const NodeType *pCur = pHead;
    if (EmptyList(pHead))
        return;
    do
    {
        printf("��%d����, ����: %d\n", pCur->id, pCur->cipher);
        pCur = pCur->next;
    }
    while (pCur != pHead);
    getchar();
}

static NodeType *GetNode(const int iId, const int iCipher)
{
    NodeType *pNew;
    pNew = (NodeType *)malloc(sizeof(NodeType));
    if(!pNew)
    {
        printf("Error, the memory is not enough!\n");
        exit(-1);
    }
    pNew->id = iId;
    pNew->cipher = iCipher;
    pNew->next = NULL;
    return pNew;
}

static unsigned EmptyList(const NodeType *pHead)
{
    if(!pHead)
    {
        printf("The list is empty!\n");
        return TRUE;
    }
    return FALSE;
}

