#include"../head/SERVER.h"
int Check_Id_Pwd(int n,cln a)
{
    USER Tag= RegistedUserHead->next;
    if(n==0)
    {
        if(Tag!=NULL)
        {
            if(!strcmp(a.USERID,Tag->USERID)&&!strcmp(a.USERPASSWORD,Tag->USERPASSWORD))
            {
                return 1;
            }
            else
            {
                while(Tag->next!=NULL)
                {
                    if(!strcmp(a.USERID,Tag->next->USERID)&&!strcmp(a.USERPASSWORD,Tag->next->USERPASSWORD))
                    {
                        return 1;
                    }
                    else
                    {
                        Tag=Tag->next;
                    }
                }
                printf("\nCheckidpwd:已注册用户列表中用户%s账号或者密码错误,请检查服务\n",a.USERID);
                return -1;
            }
        }
        else
        {
            printf("\nCheckidpwd:已注册用户列表中用户%s账号或者密码错误,请检查服务\n",a.USERID);
            return -1;
        }
    }
    else
    {
        if(Tag!=NULL)
        {
            if(!strcmp(a.USERID,Tag->USERID))
            {
                return 1;
            }
            else
            {
                while(Tag->next!=NULL)
                {
                    if(!strcmp(a.USERID,Tag->USERID))
                    {
                        //printf("\ncheckidpwd:已注册用户列表中有此用户%s,禁止注册\n",a.USERID);
                        return 1;
                    }
                    else
                    {
                        Tag=Tag->next;
                    }
                }
                //printf("\ncheckidpwd:已注册用户列表中无此用户%s,准许注册\n",a.USERID);
                return -1;
            }
        }
        else
        {
            printf("\ncheckidpwd:已注册用户列表中无此用户%s,准许注册\n",a.USERID);
            return -1;
        }
    }
    return 5;
}
