#include"../head/SERVER.h"
USER Print_onlineuser(int n,char *USERID)///n为检查方法，0为查找USERID用户并返回该用户节点；其他为打印全部用户。
{
    USER Tag= onlineUserHead->next;
    if(Tag==NULL)
    {
        //printf("\n1.Printonlineuser:在线用户列表中无此用户%s\n",USERID);
        return NULL;
    }
    if(n==0)
    {
        if(!strcmp(USERID,Tag->USERID))
        {
            return Tag;
        }
        else
        {
            while(Tag->next!=NULL)
            {
                if(!strcmp(USERID,Tag->next->USERID))
                {
                    return Tag->next;
                }
                else
                {
                    Tag=Tag->next;
                }
            }
           // printf("\n2.Printonlineuser:在线用户列表中无此用户%s\n",USERID);
            return NULL;
        }
    }
    else
    {
        int paixu=1;
        while(Tag!=NULL)
        {
            printf("\n%d_USERID:%s_IP:%s\n",paixu,Tag->USERID,inet_ntoa(Tag->USER_socket_udp.sin_addr));
            Tag=Tag->next;
            paixu++;
        }
    }
    return NULL;
}

