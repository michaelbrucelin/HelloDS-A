//ʵ�ֶ�order��(��)��B-TREE�ṹ���������ķ�װ��  
//���ң�search�����룺insert��ɾ����remove��  
//������create�����٣�destory����ӡ��print��  
#ifndef BTREE_H  
#define BTREE_H  
  
#ifdef __cplusplus  
extern "C" {  
#endif  
  
////* ����m��(��)B ������С����BTree_D=ceil(m)*/  
/// �����ﶨ��ÿ���ڵ��йؼ��ֵ������ĿΪ:2 * BTree_D - 1������(��)��2 * BTree_D.  
#define BTree_D        2  
#define ORDER        (BTree_D * 2) //����Ϊ4��B-tree,2-3-4�������Ϊ3��B-tree,2-3����  
//#define ORDER        (BTree_T * 2-1)  //���Ϊ3��B-tree,2-3����  
  
    typedef int KeyType;  
    typedef struct BTNode{  
        int keynum;                        /// ����йؼ��ֵĸ�����keynum <= BTree_N  
        KeyType key[ORDER-1];                /// �ؼ�������Ϊkey[0..keynum - 1]  
        struct BTNode* child[ORDER];        /// ����ָ������Ϊchild[0..keynum]  
        bool isLeaf;                    /// �Ƿ���Ҷ�ӽڵ�ı�־  
    }BTNode;  
      
    typedef BTNode* BTree;  ///����BTree  
      
    ///�������ݼ�data,����BTree��  
    void BTree_create(BTree* tree, const KeyType* data, int length);  
  
    ///����BTree���ͷ��ڴ�ռ䡣  
    void BTree_destroy(BTree* tree);  
      
    ///��BTree�в���ؼ���key��  
    void BTree_insert(BTree* tree, KeyType key);  
  
    ///��BTree���Ƴ��ؼ���key��  
    void BTree_remove(BTree* tree, KeyType key);  
  
    ///��ȱ���BTree��ӡ��������Ϣ��  
    void BTree_print(const BTree tree, int layer=1);  
      
    /// ��BTree�в��ҹؼ��� key��  
    /// �ɹ�ʱ�����ҵ��Ľڵ�ĵ�ַ�� key �����е�λ�� *pos  
    /// ʧ��ʱ���� NULL ������ʧ��ʱɨ�赽�Ľڵ�λ�� *pos  
    BTNode* BTree_search(const BTree tree, int key, int* pos);  
      
#ifdef __cplusplus  
}  
#endif  
  
#endif