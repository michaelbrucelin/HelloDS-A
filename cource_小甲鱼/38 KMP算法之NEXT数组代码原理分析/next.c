void get_next(String T, int *next)
{
	int j = 0; //前缀
	int i = 1; //后缀
	next[1] = 0;
	while (i < T[0])
	{
		if (0 == j || T[i] == T[j])
		{
			i++;
			j++;
			next[i] = j;
		}
		else
		{
			j = next[j];
		}
	}

	// 因为前缀是固定的，后缀是相对的。
}