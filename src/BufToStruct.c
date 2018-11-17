#include"../head/SERVER.h"
sendbag BufToStruct(char *buf)
{
    sendbag a;
    memcpy(&a,buf,sizeof(sendbag)+1);
    return a;
}
char* StructToBuf(sendbag a)
{
    char *clnTobuf;
    clnTobuf =(char*)malloc(sizeof(sendbag));
    memcpy(clnTobuf,(char*)&a,sizeof(sendbag));
    return clnTobuf;
}
