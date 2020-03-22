#include"../head/SERVER.h"
int Stringcut(char* str,int m,int n,char *des)
{
    int i=m;
    for(;i<=n;i++)
    {
        des[i-m]=str[i];
    }
    des[i-m]='\0';
    return 1;
}
