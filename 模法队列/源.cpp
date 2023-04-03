#include <iostream>
using namespace std;



int main(void)
{
	int n, stu, pos;
	scanf("%d", &n);
	int *l = new int[n + 1], *r = new int[n + 1];
	for (int i = 1; i <= n; i++)
	{
		l[i] = r[i] = 0;
	}
	r[0] = 1;
	for (int i = 2; i <= n; i++)
	{
		scanf("%d %d", &stu, &pos);
		if (pos == 0)
		{
			l[i] = l[stu];
			r[i] = stu;
			r[l[stu]] = i;
			l[stu] = i;
		}
		else
		{
			l[i] = stu;
			r[i] = r[stu];
			l[r[stu]] = i;
			r[stu] = i;
		}
	}

	scanf("%d", &n);
	while (n--)
	{
		scanf("%d", &stu);
		if (r[stu] != -1)
		{
			l[r[stu]] = l[stu];
			r[l[stu]] = r[stu];
			r[stu] = -1;
		}
	}
	for (pos = r[0]; pos; pos = r[pos])
	{
		printf("%d ", pos);
	}
	fflush(stdin);
	getchar();
	

	return 0;
}