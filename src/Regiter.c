#include"../head/SERVER.h"
int Register(cln *a)
{
    USER d=(USER)malloc(sizeof(struct user));
    if(Check_Id_Pwd(1,*a)==1)
    {
        printf("\nUSER:%s has Registed\n",a->USERID);
        return -1;
    }
    else
    {
        strcpy(d->USERID,a->USERID);
        strcpy(d->USERPASSWORD,a->USERPASSWORD);
        d->USER_ADDR=a->ADDR;
        d->USER_socket=a->remote_socket;
        UpdateRegistedUser(d);
        printf("\nUSER:%s Registed Success !\n",a->USERID);
        free(d);
        return 1;
    }
}
