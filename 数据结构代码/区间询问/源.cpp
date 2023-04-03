#include <iostream>
using namespace std;

int max(int a, int b)
{
    return a > b ? a : b;
}

int log(int x)
{
    int n = 0;
    while (x >>= 1)
        n++;
    return n;
}

int x[100000][30];
int main()
{
    int n, m, l, r;
    scanf("%d %d", &n, &m);
    // **x = new int*[n];
    for (int i = 0; i < n; i++)
    {
        //x[i] = new int[log(n - i + 1)];
        scanf("%d", &x[i][0]);
    }
    int tmp = log(n);
    for (int j = 1; j <= tmp; j++)
    {
        for (int i = 0; i + (1 << j) - 1 < n; i++)
        {
            x[i][j] = max(x[i][j - 1], x[i + (1 << (j - 1))][j - 1]);
        }
    }
    while (m--)
    {
        scanf("%d %d", &l, &r);
        l--;r--;
        int j = log(r - l + 1);
        printf("%d\n", max(x[l][j], x[r - (1 << j) + 1][j]));
    }
    //for (int i = 0; i < n; i++)
    //    delete [] x[i];
    //delete []x;

    return 0;
}