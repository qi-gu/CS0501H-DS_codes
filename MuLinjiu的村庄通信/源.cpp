#include <iostream>
#include <cmath>
using namespace std;

int cnt;
double dis[505], line[505];
bool exist[505];

struct vil
{
	int x, y;
} v[505];

double pow(double x)
{
	return x * x;
}

double get_dis(vil &a, vil &b)
{
	return sqrt(pow(a.x - b.x) + pow(a.y - b.y));
}

void swap(double &a, double &b)
{
	double tmp = a;
	a = b;
	b = tmp;
}

void sort(int l, int r)
{
	if (l > r)
		return;
	int mid = l;
	double tmp = line[r];
	for (int i = l; i < r; ++i)
	{
		if (line[i] > tmp)
		{
			swap(line[i], line[mid++]);
		}
	}
	swap(line[mid], line[r]);
	sort(l, mid - 1);
	sort(mid + 1, r);
}

int main()
{
	int s, p;
	scanf("%d %d", &s, &p);
	for (int i = 1; i <= p; ++i)
	{
		dis[i] = 0x3f3f3f3f;
		scanf("%d %d", &v[i].x, &v[i].y);
	}
	dis[0] = 0x3f3f3f3f;
	dis[1] = 0;
	for (int i = 0; i < p; ++i)
	{
		int pos = 0;
		double new_dis = 3e9, new_v = 0;
		for (int j = 1; j <= p; ++j)
		{
			if (!exist[j] && dis[j] < dis[pos])
			{
				pos = j;
			}
		}
		exist[pos] = true;
		line[++cnt] = dis[pos];
		for (int j = 1; j <= p; ++j)
		{
			if (!exist[j])
			{
				double d = get_dis(v[j], v[pos]);
				dis[j] = dis[j] < d ? dis[j] : d;
			}
		}
	}
	sort(1, cnt);
	printf("%.2lf", line[s]);


	return 0;
}