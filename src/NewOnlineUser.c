#include"../head/SERVER.h"
int newOnlineUser(cln a)
{

    USER newuser=NULL;
    int n=0;
    do
    {
        newuser=(USER)malloc(sizeof(struct user));
        n++;
    }
    while(newuser==NULL&&n<100);
    if(n>99)
    {
        printf("can't add newuser");
        return -1;
    }
    ///******根据接口给节点初始化********
    strcpy(newuser->USERID,a.USERID);
    strcpy(newuser->USERPASSWORD,a.USERPASSWORD);
    newuser->USER_socket_udp=a.ADDR;
    newuser->USER_socket=a.remote_socket;
    newuser->next=onlineUserHead->next;
    onlineUserHead->next=newuser;
    onlineUserHead->OnlineUserNum++;
    ///***********************************
    return 1;
}
