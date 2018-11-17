#include"../head/SERVER.h"
int DeleteFileUser(cln a)
{
    USER Tag= RegistedUserHead->next;
    if(Check_Id_Pwd(0,a)==1)
    {
        if(Tag==NULL)
        {
            printf("\n注册用户列表中无此用户%s,请检查服务器\n",a.USERID);
            return 0;
        }
        else
        {
            if(!strcmp(a.USERID,Tag->USERID))
            {
                strcpy(Tag->USERPASSWORD,a.REUSERPASSWORD) ;
                rewind(REGISTERlocal);
                USER d=(USER)malloc(sizeof(struct user));
                while(!feof(REGISTERlocal) && fread(d,sizeof(struct user),1,REGISTERlocal))
                {
                    if(!strcmp(d->USERID,a.USERID))
                    {
                        fseek(REGISTERlocal,ftell(REGISTERlocal)-sizeof(struct user),0);
                        fwrite(Tag,sizeof(struct user),1,REGISTERlocal);
                        fseek(REGISTERlocal,RegistedUserHead->OnlineUserNum*sizeof(struct user),0);
                        break;
                    }
                }
                free(d);
                return 1;
            }
            else
            {
                while(Tag->next!=NULL)
                {
                    if(!strcmp(a.USERID,Tag->next->USERID))
                    {
                        strcpy(Tag->USERPASSWORD,a.REUSERPASSWORD) ;
                        rewind(REGISTERlocal);
                        USER d=(USER)malloc(sizeof(struct user));
                        while(!feof(REGISTERlocal) && fread(d,sizeof(struct user),1,REGISTERlocal))
                        {
                            if(!strcmp(d->USERID,a.USERID))
                            {
                                fseek(REGISTERlocal,ftell(REGISTERlocal)-sizeof(struct user),0);
                                fwrite(Tag,sizeof(struct user),1,REGISTERlocal);
                                fseek(REGISTERlocal,RegistedUserHead->OnlineUserNum*sizeof(struct user),0);
                                break;
                            }
                        }
                        free(d);
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
    //printf("\n用户列表中无此用户%s,请检查服务器\n",a.USERID);
    return 0;
}
