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
                printf("\nCheckidpwd:��ע���û��б����û�%s�˺Ż����������,�������\n",a.USERID);
                return -1;
            }
        }
        else
        {
            printf("\nCheckidpwd:��ע���û��б����û�%s�˺Ż����������,�������\n",a.USERID);
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
                        //printf("\ncheckidpwd:��ע���û��б����д��û�%s,��ֹע��\n",a.USERID);
                        return 1;
                    }
                    else
                    {
                        Tag=Tag->next;
                    }
                }
                //printf("\ncheckidpwd:��ע���û��б����޴��û�%s,׼��ע��\n",a.USERID);
                return -1;
            }
        }
        else
        {
            printf("\ncheckidpwd:��ע���û��б����޴��û�%s,׼��ע��\n",a.USERID);
            return -1;
        }
    }
    return 5;
}
