#include"../head/SERVER.h"
DWORD WINAPI fun(LPVOID new_fd)
{
    SOCKET *a=(SOCKET *)new_fd;
    char recv_buf[BUFSIZ];
    while(1)
    {
        scanf("%s",recv_buf);///¸Ä
        int len = send(*a, recv_buf, sizeof(recv_buf)+sizeof(char), 0);
        if(len<=0) break;
    }
    return 0;
}
