#include"../head/SERVER.h"
int StartThread(cln *a)
{
    cln_thread[cln_num]=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)talk,a,0,NULL);
    printf("�û�%d�ѽ���,�߳��ѿ���",cln_num);
    return AcceptClient();
}
