#include"../head/SERVER.h"
USER Print_onlineuser(int n,char *USERID)///nΪ��鷽����0Ϊ����USERID�û������ظ��û��ڵ㣻����Ϊ��ӡȫ���û���
{
    USER Tag= onlineUserHead->next;
    if(Tag==NULL)
    {
        //printf("\n1.Printonlineuser:�����û��б����޴��û�%s\n",USERID);
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
           // printf("\n2.Printonlineuser:�����û��б����޴��û�%s\n",USERID);
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

