#include"../head/SERVER.h"
DWORD WINAPI Check_alive(LPVOID qn)
{
    sendbag sendcln;
    int len=0;
    char sendbuf1[sizeof(sendbag)]= {0};
    cln* check_a=(cln*)qn;
    Sleep(10*1000);
    while(check_a->info[0]!='N')
    {
        Sleep(5*1000);
        //printf("\nCheck Alive\n");
        strcpy(sendcln.checkcode,"BTT");
        sendcln.save[99]='\n';
        memcpy(sendbuf1,&sendcln,sizeof(sendcln));
        len=send(check_a->remote_socket,sendbuf1,sizeof(sendcln),0);
        if(len==SOCKET_ERROR||len==0)
        {
            //printf("\nÁ¬½Ó%dÍË³ö\n",check_a->remote_socket);
            closesocket(check_a->remote_socket);
            printf("\nUser %s 's connection was Lost!\n",check_a->USERID);
            delete_out_user(*check_a);
            break;
        }
    }
    return 0;
}
