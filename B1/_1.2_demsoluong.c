#include<stdio.h>
#include<string.h>
#include<ctype.h>
int main()
{
    char c[10000];
    int max = 0;
    int a[257] = {0};
    scanf("%[^\n]s",c);
    for(int i=0;i<strlen(c);i++)
    {
        a[c[i]]++;
    }
    for(int i=0;i<strlen(c);i++)
    {
        if(max < c[i]) max = c[i];
    }
    for(int i=0;i<=max;i++)
    {
        if(a[i] != 0)
        {
            printf("%c-%d\n",i,a[i]);
        }
    }
}