#include <iostream>
#include <cstring>
using namespace std;

char s[1000002], t[1000002];

int main()
{
    scanf("%s", s);
    scanf("%s", t);
    int *next = new int[strlen(t) + 100];

    int i = 0, k = -1;
    next[i] = k;
    while (t[i] != '\0')
    {
        if (k == -1 || t[i] == t[k])
        {
            i++;
            k++;
            next[i] = k;
        }
        else
            k = next[k];
    }
    k = 0; i = 0;

    while (s[i] != '\0')
    {
        if (s[i] == t[k])
        {
            i++;
            k++;
        }
        else if (next[k] == -1)
            i++;
        else
            k = next[k];

        if (t[k] == '\0')
        {
            printf("%d\n", i - k + 1);
            i = i - k + 2;
            k = 0;
        }

    }

    k = strlen(t);
    for (i = 1; i < k + 1; i++)
    {
        printf("%d ", next[i]);
    }

    return 0;
}