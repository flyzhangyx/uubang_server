#include"../head/SERVER.h"
int SIGNIN(cln *a)
{
    SOCKET asocket=a->remote_socket;
    int check=Check_Id_Pwd(0,*a);
    USER checkuser= Print_onlineuser(0,a->USERID);
    Sleep(200);
    if(check==-1)
    {
        return -1;
    }
    else if(check!=-1&&(checkuser==NULL))
    {
        newOnlineUser(*a);
        return 1;
    }
    else if(check!=-1&&(checkuser!=NULL)&&strcmp("CH123457",a->checkcode))
    {
        printf("%s|%s",a->checkcode,a->USERID);
        perror("online");
        sendbag as;
        char sendbuf[sizeof(sendbag)]= {0};
        memset(&as,0,sizeof(sendbag));
        memset(sendbuf,0,sizeof(sendbag));
        strcpy(as.checkcode,"STO");
        as.save[99]='\n';
        memcpy(sendbuf,&as,sizeof(sendbag));
        send(checkuser->USER_socket,sendbuf,sizeof(sendbag),0);
        closesocket(checkuser->USER_socket);
        checkuser->USER_socket=asocket;
        checkuser->USER_socket_udp=a->ADDR;
        return 1;
    }
    else if(check!=-1&&(checkuser!=NULL)&&!strcmp("CH123457",a->checkcode))
    {
        if(!strncmp(inet_ntoa(checkuser->USER_socket_udp.sin_addr),inet_ntoa(a->ADDR.sin_addr),8))
        {
            closesocket(checkuser->USER_socket);
            newOnlineUser(*a);
        }
        else
        {
            delete_out_user(*a);
            newOnlineUser(*a);
        }
        return 1;
    }
    return 5;
}
