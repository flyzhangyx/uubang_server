#include"../head/SERVER.h"
USER Print_onlineuser(int n,char *USERID)///nΪ��鷽����0Ϊ����USERID�û������ظ��û��ڵ㣻����Ϊ��ӡȫ���û���
{
    USER Tag= onlineUserHead->next;
    if(Tag==NULL)
    {
        printf("\nPrintonlineuser:�����û��б����޴��û�%s\n",USERID);
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
            printf("\nPrintonlineuser:�����û��б����޴��û�%s\n",USERID);
            return NULL;
        }

    }
    else
    {
        while(Tag!=NULL)
        {
            printf("\n|USERID|:%s|IP|:%s\n",Tag->USERID,inet_ntoa(Tag->USER_ADDR.sin_addr));
            Tag=Tag->next;
        }
    }
    return NULL;
}

