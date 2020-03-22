#include"../head/SERVER.h"
int delete_out_user(cln a)
{
    USER Tag= onlineUserHead->next;
    if(Tag==NULL)
    {
        printf("\n在线用户列表中无此用户%s,请检查服务器\n",a.USERID);
        return 0;
    }
    else
    {
        if(!strcmp(a.USERID,Tag->USERID))
        {
            onlineUserHead->next=Tag->next;
            free(Tag);
            printf("\n已从在线列表中删除该用户%s\n",a.USERID);
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
                    printf("\n已从在线列表中删除该用户%s\n",a.USERID);
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
    printf("\n在线用户列表中无此用户%s,请检查服务器\n",a.USERID);
    return 0;
}
