#include"../head/SERVER.h"
int UpdateRegistedUser(USER a)
{
    char *timenow;
    time_t t;//定义一个时间变量
    t=time(NULL);
    timenow=ctime(&t);
    cln b;
    strcpy(b.info,a->info);
    b.ADDR=a->USER_socket_udp;
    b.remote_socket=a->USER_socket;
    strcpy(b.USERID,a->USERID);
    strcpy(b.USERPASSWORD,a->USERPASSWORD);
    strcpy(b.DATE,timenow);
    AddtoLocal(b);
    while(1)
    {
        if(!warnfile)
        {
            warnfile=1;
            if(fwrite(a,sizeof(struct user),1,REGISTERlocal)!=1)
            {
                warnfile=0;
                return -1;
            }
        fflush(REGISTERlocal);
        warnfile=0;
        break;
        }
    }
    return 1;
}
