#include"../head/SERVER.h"
int delete_out_user(cln a)
{
    USER Tag= onlineUserHead->next;
    if(Tag==NULL)
    {
        printf("\n�����û��б����޴��û�%s,���������\n",a.USERID);
        return 0;
    }
    else
    {
        if(!strcmp(a.USERID,Tag->USERID))
        {
            onlineUserHead->next=Tag->next;
            free(Tag);
            printf("\n�Ѵ������б���ɾ�����û�%s\n",a.USERID);
            //cln_num--;
            return 1;
        }
        else
        {
            while(Tag->next!=NULL)
            {
                if(!strcmp(a.USERID,Tag->next->USERID))
                {
                    Tag->next=Tag->next->next;
                    free(Tag->next);
                    printf("\n�Ѵ������б���ɾ�����û�%s\n",a.USERID);
                    //cln_num--;
                    return 1;
                }
                else
                {
                    Tag=Tag->next;
                }
            }
        }
    }
    printf("\n�����û��б����޴��û�%s,���������\n",a.USERID);
    return 0;
}
