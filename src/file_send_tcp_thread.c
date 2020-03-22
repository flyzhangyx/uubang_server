#include"../head/SERVER.h"
DWORD WINAPI file_tcp_thread(LPVOID interface_send)
{
    tcp_send_interface* tcp_interface=(tcp_send_interface*) interface_send;
    char filepath[64]={0};
    int flag=0;
    strcpy(filepath,tcp_interface->file_path);
    strcat(filepath,tcp_interface->filename);
    FILE* file=fopen(filepath,"r");
    if(file==NULL)
    {
        return -1;
    }
    flag=file_tcp_send(&(tcp_interface->a),file,tcp_interface->file_lx,tcp_interface->filename);
    if(flag==0)
    {
        printf("Send success\n");
    }
    else
    {
        printf("Send fail\n");
    }
    return 0;
}
