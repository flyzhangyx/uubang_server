#include"../head/SERVER.h"
int main()
{
    initServer();
    UdpInit(3566);
    printf("��������ʼ���ɹ���");
    int s=100000;
    CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)fun,&s,0,NULL);
    AcceptClient();
    return 0;
}
