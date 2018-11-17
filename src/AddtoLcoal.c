#include"../head/SERVER.h"
int AddtoLocal(cln a)
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
    newuser->USER_ADDR=a.ADDR;
    newuser->USER_socket=a.remote_socket;
    newuser->next=RegistedUserHead->next;
    RegistedUserHead->next=newuser;
    RegistedUserHead->OnlineUserNum++;
    ///***********************************
    return 1;

}
