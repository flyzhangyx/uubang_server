#include"../head/SERVER.h"
int DeleteFileUser(cln a)
{
    USER Tag= RegistedUserHead->next;
    if(Check_Id_Pwd(0,a)==1)
    {
        if(Tag==NULL)
        {
            printf("\nע���û��б�%s��ƥ��,���������\n",a.USERID);
            return -1;
        }
        else
        {
            if(!strcmp(a.USERID,Tag->USERID))
            {
                strcpy(Tag->USERPASSWORD,a.REUSERPASSWORD) ;
                return 1;
            }
            else
            {
                while(Tag->next!=NULL)
                {
                    if(!strcmp(a.USERID,Tag->next->USERID))
                    {
                        strcpy(Tag->next->USERPASSWORD,a.REUSERPASSWORD) ;
                        return 1;
                    }
                    else
                    {
                        Tag=Tag->next;
                    }
                }
            }
        }
    }
    else
    {
        return -1;
    }
    return 0;
}
