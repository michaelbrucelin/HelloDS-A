// ********************************
// By 小甲鱼，http://www.fishc.com
// ********************************
#include <stdio.h>

int bin_search( int key[], int low, int high, int k )
{
	int mid;

	if( low > high )
	{
		return -1;
	}
	else
	{
		mid = (low + high) / 2;
		
		if( key[mid] == k )
		{
			return mid;
		}

		if( k > key[mid] )
		{
			return bin_search( key, mid+1, high, k );	// 在序列的后半部分查找
		}
		else
		{
			return bin_search( key, low, mid-1, k );	// 在序列的前半部分查找
		}

	}
}

int main()
{
        int str[11] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
        int n, addr;

        printf("请输入待查找的关键字: ");
        scanf("%d", &n);

        addr = bin_search(str, 0, 10, n);
        if( -1 != addr )
        {
                printf("查找成功，可喜可贺，可口可乐! 关键字 %d 所在的位置是: %d\n", n, addr);
        }
        else
        {
                printf("查找失败!\n");
        }

        return 0;
}