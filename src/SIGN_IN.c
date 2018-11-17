#include"../head/SERVER.h"
int SIGNIN(cln *a)
{
    SOCKET asocket=a->remote_socket;
    int check=Check_Id_Pwd(0,*a);
    USER checkuser= Print_onlineuser(0,a->USERID);
    if(check==-1)
    {
        return -1;
    }
    else if(check!=-1&&(checkuser==NULL))
    {
        newOnlineUser(*a);
        return 1;
    }
    else if(check!=-1&&(checkuser!=NULL))
    {
        perror("online");
        closesocket(checkuser->USER_socket);
        checkuser->USER_socket=asocket;
        checkuser->USER_ADDR=a->ADDR;
        return 1;
    }
    return 5;
}
