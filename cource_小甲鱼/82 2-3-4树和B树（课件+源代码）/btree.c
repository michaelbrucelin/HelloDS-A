//�������ԣ���������ϸ�½��⣩��http://blog.csdn.net/v_july_v/article/details/6735293
//ʵ�ֶ�order��(��)��B-TREE�ṹ���������ķ�װ��  
//���ң�search�����룺insert��ɾ����remove��  
//������create�����٣�destory����ӡ��print��  
#include <stdlib.h>  
#include <stdio.h>  
#include <assert.h>  
#include "btree.h"  
  
//#define max(a, b) (((a) > (b)) ? (a) : (b))  
#define cmp(a, b) ( ( ((a)-(b)) >= (0) ) ? (1) : (0) ) //�Ƚ�a��b��С  
#define DEBUG_BTREE  
  
  
// ģ�������д��ڵ�  
void disk_write(BTNode* node)  
{  
//��ӡ������е�ȫ��Ԫ�أ�������Բ鿴keynum֮���Ԫ���Ƿ�Ϊ0(���Ƿ������������)��������keynum��Ԫ�ء�  
    printf("�����д��ڵ�");  
    for(int i=0;i<ORDER-1;i++){  
        printf("%c",node->key[i]);  
    }  
    printf("\n");  
}  
  
// ģ��Ӵ��̶�ȡ�ڵ�  
void disk_read(BTNode** node)  
{  
//��ӡ������е�ȫ��Ԫ�أ�������Բ鿴keynum֮���Ԫ���Ƿ�Ϊ0(���Ƿ������������)��������keynum��Ԫ�ء�  
    printf("����̶�ȡ�ڵ�");  
    for(int i=0;i<ORDER-1;i++){  
        printf("%c",(*node)->key[i]);  
    }  
    printf("\n");  
}  
  
// ����δ�ӡ B ��  
void BTree_print(const BTree tree, int layer)  
{  
    int i;  
    BTNode* node = tree;  
  
    if (node) {  
        printf("�� %d �㣬 %d node : ", layer, node->keynum);  
  
        //��ӡ������е�ȫ��Ԫ�أ�������Բ鿴keynum֮���Ԫ���Ƿ�Ϊ0(���Ƿ������������)��������keynum��Ԫ�ء�  
        for (i = 0; i < ORDER-1; ++i) {  
        //for (i = 0; i < node->keynum; ++i) {  
            printf("%c ", node->key[i]);  
        }  
  
        printf("\n");  
  
        ++layer;  
        for (i = 0 ; i <= node->keynum; i++) {  
            if (node->child[i]) {  
                BTree_print(node->child[i], layer);  
            }  
        }  
    }  
    else {  
        printf("��Ϊ�ա�\n");  
    }  
}  
  
// ���node�ڶԹؼ��ֽ��ж��ֲ��ҡ�  
int binarySearch(BTNode* node, int low, int high, KeyType Fkey)  
{  
    int mid;  
    while (low<=high)  
    {  
        mid = low + (high-low)/2;  
        if (Fkey<node->key[mid])  
        {  
            high = mid-1;  
        }  
        if (Fkey>node->key[mid])  
        {  
            low = mid+1;  
        }  
        if (Fkey==node->key[mid])  
        {  
            return mid;//�����±ꡣ  
        }  
    }  
    return 0;//δ�ҵ�����0.  
}  
  
//insert  
/*************************************************************************************** 
   �����ѵĽ���е�һ��Ԫ�ظ��½��Ľ�㣬���ҽ����ѽ���е��м�ؼ���Ԫ�����������ڵ��С� 
   parent ��һ�������ĸ��ڵ� 
   node �� tree ���ӱ����±�Ϊ index �ĺ��ӽڵ㣬�������ģ�����ѡ� 
*******************************************************************/  
void BTree_split_child(BTNode* parent, int index, BTNode* node)  
{  
#ifdef DEBUG_BTREE  
    printf("BTree_split_child!\n");  
#endif  
    assert(parent && node);  
    int i;  
  
    // �����½ڵ㣬�洢 node �к�벿�ֵ�����  
    BTNode* newNode = (BTNode*)calloc(sizeof(BTNode), 1);  
    if (!newNode) {  
        printf("Error! out of memory!\n");  
        return;  
    }  
  
    newNode->isLeaf = node->isLeaf;  
    newNode->keynum = BTree_D - 1;  
  
    // ���� node ��벿�ֹؼ���,Ȼ��node��벿����Ϊ0��  
    for (i = 0; i < newNode->keynum; ++i){  
        newNode->key[i] = node->key[BTree_D + i];  
        node->key[BTree_D + i] = 0;  
    }  
  
    // ��� node ����Ҷ�ӽڵ㣬���� node ��벿�ֵ�ָ���ӽڵ��ָ�룬Ȼ��node��벿��ָ���ӽڵ��ָ����ΪNULL��  
    if (!node->isLeaf) {  
        for (i = 0; i < BTree_D; i++) {  
            newNode->child[i] = node->child[BTree_D + i];  
            node->child[BTree_D + i] = NULL;  
        }  
    }  
  
    // �� node ���ѳ� newNode ֮����������ݼ���  
    node->keynum = BTree_D - 1;  
  
    // �������ڵ��е�ָ���ӵ�ָ��͹ؼ���Ԫ�ء�����ʱ���ڵ�����ָ���ӵ�ָ��͹ؼ�Ԫ�ء�  
    for (i = parent->keynum; i > index; --i) {  
        parent->child[i + 1] = parent->child[i];  
    }  
  
    parent->child[index + 1] = newNode;  
  
    for (i = parent->keynum - 1; i >= index; --i) {  
        parent->key[i + 1] = parent->key[i];  
    }  
  
    parent->key[index] = node->key[BTree_D - 1];  
    ++parent->keynum;  
  
    node->key[BTree_D - 1] = 0;  
  
    // д�����  
     disk_write(parent);  
     disk_write(newNode);  
     disk_write(node);  
}  
  
void BTree_insert_nonfull(BTNode* node, KeyType key)  
{  
    assert(node);  
  
    int i;  
  
    // �ڵ���Ҷ�ӽڵ㣬ֱ�Ӳ���  
    if (node->isLeaf) {  
        i = node->keynum - 1;  
        while (i >= 0 && key < node->key[i]) {  
            node->key[i + 1] = node->key[i];  
            --i;  
        }  
  
        node->key[i + 1] = key;  
        ++node->keynum;  
  
        // д�����  
        disk_write(node);  
    }  
  
    // �ڵ����ڲ��ڵ�  
    else {  
        /* ���Ҳ����λ��*/  
        i = node->keynum - 1;  
        while (i >= 0 && key < node->key[i]) {  
            --i;  
        }  
  
        ++i;  
  
        // �Ӵ��̶�ȡ���ӽڵ�  
        disk_read(&node->child[i]);  
  
        // ����ú��ӽڵ����������ѵ���ֵ  
        if (node->child[i]->keynum == (ORDER-1)) {  
            BTree_split_child(node, i, node->child[i]);  
            // ���������Ĺؼ��ִ��ڸ÷��ѽ�������Ƶ����ڵ�Ĺؼ��֣��ڸùؼ��ֵ��Һ��ӽ���н��в��������  
            if (key > node->key[i]) {  
                ++i;  
            }  
        }  
        BTree_insert_nonfull(node->child[i], key);  
    }  
}  
  
void BTree_insert(BTree* tree, KeyType key)  
{  
#ifdef DEBUG_BTREE  
    printf("BTree_insert:\n");  
#endif  
    BTNode* node;  
    BTNode* root = *tree;  
  
    // ��Ϊ��  
    if (NULL == root) {  
        root = (BTNode*)calloc(sizeof(BTNode), 1);  
        if (!root) {  
            printf("Error! out of memory!\n");  
            return;  
        }  
        root->isLeaf = true;  
        root->keynum = 1;  
        root->key[0] = key;  
  
        *tree = root;  
  
        // д�����  
        disk_write(root);  
  
        return;  
    }  
  
    // ���ڵ�����������ǰ��Ҫ���з��ѵ���  
    if (root->keynum == (ORDER-1)) {  
        // �����½ڵ㵱����  
        node = (BTNode*)calloc(sizeof(BTNode), 1);  
        if (!node) {  
            printf("Error! out of memory!\n");  
            return;  
        }  
  
        *tree = node;  
        node->isLeaf = false;  
        node->keynum = 0;  
        node->child[0] = root;  
  
        BTree_split_child(node, 0, root);  
  
        BTree_insert_nonfull(node, key);  
    }  
  
    // ���ڵ�δ�����ڵ�ǰ�ڵ��в��� key  
    else {  
        BTree_insert_nonfull(root, key);  
    }  
}  
//remove   
// �� tree �еĽڵ� node ���кϲ����ӽڵ㴦��.  
// ע�⣺���ӽڵ�� keynum ������Ѵﵽ���ޣ��������� BTree_D - 1  
// �� tree ������Ϊ index �� key ���������ӽ���У�  
// �� node ������Ϊ index + 1 �ĺ��ӽڵ�ϲ�������Ϊ index �ĺ��ӽڵ��У��Һ��Ӻϲ������ӽ���С�  
// ������ص� key ��ָ�롣</p>void BTree_merge_child(BTree* tree, BTNode* node, int index)  
{  
#ifdef DEBUG_BTREE  
    printf("BTree_merge_child!\n");  
#endif  
    assert(tree && node && index >= 0 && index < node->keynum);  
  
    int i;  
  
    KeyType key = node->key[index];  
    BTNode* leftChild = node->child[index];  
    BTNode* rightChild = node->child[index + 1];  
  
    assert(leftChild && leftChild->keynum == BTree_D - 1  
        && rightChild && rightChild->keynum == BTree_D - 1);  
  
    // �� node�йؼ����±�Ϊindex �� key ���������ӽ���У���key����Ӧ���Һ��ӽ��ָ��node���Һ��ӽ���еĵ�һ�����ӡ�  
    leftChild->key[leftChild->keynum] = key;  
    leftChild->child[leftChild->keynum + 1] = rightChild->child[0];  
    ++leftChild->keynum;  
  
    // �Һ��ӵ�Ԫ�غϲ������ӽ���С�  
    for (i = 0; i < rightChild->keynum; ++i) {  
        leftChild->key[leftChild->keynum] = rightChild->key[i];  
        leftChild->child[leftChild->keynum + 1] = rightChild->child[i + 1];  
        ++leftChild->keynum;  
    }  
  
    // �� node �����Ƶ� key�����Ԫ��ǰ��  
    for (i = index; i < node->keynum - 1; ++i) {  
        node->key[i] = node->key[i + 1];  
        node->child[i + 1] = node->child[i + 2];  
    }  
    node->key[node->keynum - 1] = 0;  
    node->child[node->keynum] = NULL;  
    --node->keynum;  
  
    // ������ڵ�û�� key �ˣ��������ڵ����Ϊ�ϲ�������ӽڵ㣻Ȼ��ɾ���ͷſռ䡣  
    if (node->keynum == 0) {  
        if (*tree == node) {  
            *tree = leftChild;  
        }  
  
        free(node);  
        node = NULL;  
    }  
  
    free(rightChild);  
    rightChild = NULL;  
}  
  
void BTree_recursive_remove(BTree* tree, KeyType key)  
{  
    // B-���ı�������֮һ��  
    // �Ǹ��ڵ���ڲ��ڵ�Ĺؼ�����Ŀ�������� BTree_D - 1  
  
    int i, j, index;  
    BTNode *root = *tree;  
    BTNode *node = root;  
  
    if (!root) {  
        printf("Failed to remove %c, it is not in the tree!\n", key);  
        return;  
    }  
  
    // �������key��  
    index = 0;  
    while (index < node->keynum && key > node->key[index]) {  
        ++index;  
    }  
  
/*======================����key�ĵ�ǰ���ʱ�����==================== 
node: 
index of Key:            i-1  i  i+1 
                        +---+---+---+---+ 
                          *  key   * 
                    +---+---+---+---+---+ 
                           /     \ 
index of Child:           i      i+1 
                         /         \ 
                    +---+---+      +---+---+ 
                      *   *           *   *    
                +---+---+---+  +---+---+---+ 
                    leftChild     rightChild 
============================================================*/  
    /*һ��������ҵ��˹ؼ���key�����.*/  
    BTNode *leftChild, *rightChild;  
    KeyType leftKey, rightKey;  
    if (index < node->keynum && node->key[index] == key) {  
        /* 1�����ڽڵ���Ҷ�ӽڵ㣬ֱ��ɾ��*/  
        if (node->isLeaf) {  
            for (i = index; i < node->keynum-1; ++i) {  
                node->key[i] = node->key[i + 1];  
                //node->child[i + 1] = node->child[i + 2];Ҷ�ӽڵ�ĺ��ӽ��Ϊ�գ������ƶ�����  
            }  
            node->key[node->keynum-1] = 0;  
            //node->child[node->keynum] = NULL;  
            --node->keynum;  
  
            if (node->keynum == 0) {  
                assert(node == *tree);  
                free(node);  
                *tree = NULL;  
            }  
  
            return;  
        }  
        /*2.ѡ����ƶ�¸��ĺ��ӽ�㡣*/  
        // 2a��ѡ����Ը��е����ӽ�㡣  
        // ���λ�� key ǰ�����ӽ��� key ��Ŀ >= BTree_D��  
        // �������� key �����ӽ������һ��Ԫ�����������ڵ�key��λ�á�  
        // Ȼ�������ӽڵ��еݹ�ɾ��Ԫ��leftKey��  
        else if (node->child[index]->keynum >= BTree_D) {  
            leftChild = node->child[index];  
            leftKey = leftChild->key[leftChild->keynum - 1];  
            node->key[index] = leftKey;  
  
            BTree_recursive_remove(&leftChild, leftKey);  
        }  
        // 2b��ѡ����Ը��е��Һ��ӽ�㡣  
        // ���λ�� key ����Һ��ӽ��� key ��Ŀ >= BTree_D��  
        // �������� key ���Һ��ӽ��ĵ�һ��Ԫ�����������ڵ�key��λ��  
        // Ȼ�����Һ��ӽڵ��еݹ�ɾ��Ԫ��rightKey��  
        else if (node->child[index + 1]->keynum >= BTree_D) {  
            rightChild = node->child[index + 1];  
            rightKey = rightChild->key[0];  
            node->key[index] = rightKey;  
  
            BTree_recursive_remove(&rightChild, rightKey);  
        }  
        /*���Һ��ӽ�㶼����ƶ��ɾ��ǰ��Ҫ���ӽ��ĺϲ�����*/  
        // 2c�����Һ��ӽ��ֻ���� BTree_D - 1 ���ڵ㣬  
        // �ϲ��ǽ� key ���������ӽڵ㣬�����Һ��ӽڵ�ϲ������ӽڵ��У�  
        // ɾ���Һ��ӽڵ㣬�ڸ��ڵ�node���Ƴ� key ��ָ���Һ��ӽڵ��ָ�룬  
        // Ȼ���ںϲ��˵����ӽڵ��еݹ�ɾ��Ԫ��key��  
        else if (node->child[index]->keynum == BTree_D - 1  
            && node->child[index + 1]->keynum == BTree_D - 1){  
            leftChild = node->child[index];  
  
            BTree_merge_child(tree, node, index);  
  
            // �ںϲ��˵����ӽڵ��еݹ�ɾ�� key  
            BTree_recursive_remove(&leftChild, key);  
        }  
    }  
  
/*======================δ����key�ĵ�ǰ���ʱ�����==================== 
node: 
index of Key:            i-1  i  i+1 
                        +---+---+---+---+ 
                          *  keyi * 
                    +---+---+---+---+---+ 
                       /    |    \ 
index of Child:      i-1    i     i+1 
                     /      |       \ 
            +---+---+   +---+---+      +---+---+ 
             *   *        *   *          *   *    
        +---+---+---+   +---+---+---+  +---+---+---+ 
        leftSibling       Child        rightSibling  
============================================================*/  
    /*���������δ�ҵ��˹ؼ���key�����.*/  
    else {  
        BTNode *leftSibling, *rightSibling, *child;  
        // 3. key �����ڽڵ� node �У���Ӧ����ĳ������ key ���ӽڵ��С�  
        //  key < node->key[index], ���� key Ӧ���ں��ӽڵ� node->child[index] ��  
        child = node->child[index];  
        if (!child) {  
            printf("Failed to remove %c, it is not in the tree!\n", key);  
            return;  
        }  
        /*������ҵĸú��ӽ�����ƶ�����*/  
        if (child->keynum == BTree_D - 1) {  
            leftSibling = NULL;  
            rightSibling = NULL;  
  
            if (index - 1 >= 0) {  
                leftSibling = node->child[index - 1];  
            }  
  
            if (index + 1 <= node->keynum) {  
                rightSibling = node->child[index + 1];  
            }  
            /*ѡ���¸��������ֵܽ�㡣*/  
            // 3a��������ں��ӽڵ����ڵ��ֵܽڵ����нڵ����ٰ��� BTree_D ���ؼ���  
            // �� node ��һ���ؼ���key[index]���Ƶ� child �У�����Ը��е������ֵܽڵ���һ���ؼ������Ƶ�  
            // node �У�Ȼ���� child ���ӽڵ��еݹ�ɾ�� key��  
            if ((leftSibling && leftSibling->keynum >= BTree_D)  
                || (rightSibling && rightSibling->keynum >= BTree_D)) {  
                int richR = 0;  
                if(rightSibling) richR = 1;  
                if(leftSibling && rightSibling) {  
                    richR = cmp(rightSibling->keynum,leftSibling->keynum);  
                }  
                if (rightSibling && rightSibling->keynum >= BTree_D && richR) {  
        //�������ֵ���Ը��У���ú������򸸽ڵ��һ��Ԫ�أ����ֵ��еĵ�һ��Ԫ�����������ڵ�����λ�ã���������Ӧ������  
                    child->key[child->keynum] = node->key[index];  
                    child->child[child->keynum + 1] = rightSibling->child[0];  
                    ++child->keynum;  
  
                    node->key[index] = rightSibling->key[0];  
  
                    for (j = 0; j < rightSibling->keynum - 1; ++j) {//Ԫ��ǰ��  
                        rightSibling->key[j] = rightSibling->key[j + 1];  
                        rightSibling->child[j] = rightSibling->child[j + 1];  
                    }  
                    rightSibling->key[rightSibling->keynum-1] = 0;  
                    rightSibling->child[rightSibling->keynum-1] = rightSibling->child[rightSibling->keynum];  
                    rightSibling->child[rightSibling->keynum] = NULL;  
                    --rightSibling->keynum;  
                }  
                else {//�������ֵ���Ը��У���ú����򸸽ڵ��һ��Ԫ�أ����ֵ��е����Ԫ�����������ڵ�����λ�ã���������Ӧ������  
                    for (j = child->keynum; j > 0; --j) {//Ԫ�غ���  
                        child->key[j] = child->key[j - 1];  
                        child->child[j + 1] = child->child[j];  
                    }  
                    child->child[1] = child->child[0];  
                    child->child[0] = leftSibling->child[leftSibling->keynum];  
                    child->key[0] = node->key[index - 1];  
                    ++child->keynum;  
  
                    node->key[index - 1] = leftSibling->key[leftSibling->keynum - 1];  
  
                    leftSibling->key[leftSibling->keynum - 1] = 0;  
                    leftSibling->child[leftSibling->keynum] = NULL;  
  
                    --leftSibling->keynum;  
                }  
            }  
            /*�����ֵܽ�㶼����ƶ��ɾ��ǰ��Ҫ�ֵܽ��ĺϲ�����,*/  
            // 3b, ������ں��ӽڵ����ڵ��ֵܽڵ㶼ֻ���� BTree_D - 1 ���ؼ��֣�  
            // �� child ����һ���ڽڵ�ϲ������� node �е�һ���ؼ����½����ϲ��ڵ��У�  
            // ���� node ��ɾ���Ǹ��ؼ��ֺ����ָ�룬�� node �� key Ϊ�գ�ɾ֮����������Ϊ�ϲ���㡣  
            // �������غ��ӽڵ�child�еݹ�ɾ�� key��  
            else if ((!leftSibling || (leftSibling && leftSibling->keynum == BTree_D - 1))  
                && (!rightSibling || (rightSibling && rightSibling->keynum == BTree_D - 1))) {  
                if (leftSibling && leftSibling->keynum == BTree_D - 1) {  
  
                    BTree_merge_child(tree, node, index - 1);//node�е��Һ���Ԫ�غϲ��������С�  
  
                    child = leftSibling;  
                }  
  
                else if (rightSibling && rightSibling->keynum == BTree_D - 1) {  
  
                    BTree_merge_child(tree, node, index);//node�е��Һ���Ԫ�غϲ��������С�  
                }  
            }  
        }  
  
        BTree_recursive_remove(&child, key);//��������key���ں��ӽ���м����ݹ�ɾ��key��  
    }  
}  
  
void BTree_remove(BTree* tree, KeyType key)  
{  
#ifdef DEBUG_BTREE  
    printf("BTree_remove:\n");  
#endif  
    if (*tree==NULL)  
    {     
        printf("BTree is NULL!\n");  
        return;  
    }  
  
    BTree_recursive_remove(tree, key);  
}  
  
//=====================================search====================================  
  
BTNode* BTree_recursive_search(const BTree tree, KeyType key, int* pos)  
{  
    int i = 0;  
  
    while (i < tree->keynum && key > tree->key[i]) {  
        ++i;  
    }  
  
    // Find the key.  
    if (i < tree->keynum && tree->key[i] == key) {  
        *pos = i;  
        return tree;  
    }  
  
    // tree ΪҶ�ӽڵ㣬�Ҳ��� key������ʧ�ܷ���  
    if (tree->isLeaf) {  
        return NULL;  
    }  
  
    // �ڵ��ڲ���ʧ�ܣ��� tree->key[i - 1]< key < tree->key[i]��  
    // ��һ�����ҵĽ��ӦΪ child[i]  
  
    // �Ӵ��̶�ȡ�� i �����ӵ�����  
    disk_read(&tree->child[i]);  
  
    // �ݹ�ؼ����������� tree->child[i]  
    return BTree_recursive_search(tree->child[i], key, pos);  
}  
  
BTNode* BTree_search(const BTree tree, KeyType key, int* pos)  
{  
#ifdef DEBUG_BTREE  
    printf("BTree_search:\n");  
#endif  
    if (!tree) {  
        printf("BTree is NULL!\n");  
        return NULL;  
    }  
    *pos = -1;  
    return BTree_recursive_search(tree,key,pos);  
}  
  
//===============================create===============================  
void BTree_create(BTree* tree, const KeyType* data, int length)  
{  
    assert(tree);  
  
    int i;  
  
#ifdef DEBUG_BTREE  
    printf("\n ��ʼ���� B-�����ؼ���Ϊ:\n");  
    for (i = 0; i < length; i++) {  
        printf(" %c ", data[i]);  
    }  
    printf("\n");  
#endif  
  
    for (i = 0; i < length; i++) {  
#ifdef DEBUG_BTREE  
        printf("\n����ؼ��� %c:\n", data[i]);  
#endif  
        int pos = -1;  
        BTree_search(*tree,data[i],&pos);//���ĵݹ�������  
        if (pos!=-1)  
        {  
            printf("this key %c is in the B-tree,not to insert.\n",data[i]);  
        }else{  
            BTree_insert(tree, data[i]);//����Ԫ�ص�BTree�С�  
        }  
  
#ifdef DEBUG_BTREE  
        BTree_print(*tree);//������ȱ�����  
#endif  
    }  
  
    printf("\n");  
}  
//===============================destroy===============================  
void BTree_destroy(BTree* tree)  
{  
    int i;  
    BTNode* node = *tree;  
  
    if (node) {  
        for (i = 0; i <= node->keynum; i++) {  
            BTree_destroy(&node->child[i]);  
        }  
  
        free(node);  
    }  
  
    *tree = NULL;  
}  