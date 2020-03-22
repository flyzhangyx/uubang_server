#include"../head/SERVER.h"
void RequestContact(cln *a,FILE *file)
{
    sendbag reccln;
    int len=0;
    USER talktouser=NULL;
    char sendbuf[sizeof(sendbag)]= {0};
    Contact d=(Contact)malloc(sizeof(struct contact));
    printf("\nContact OK:");
    rewind(file);
    char rr[4]="ERR";
    while(!feof(file) && fread(d,sizeof(struct contact),1,file)&&a->info[0]!='N')
    {
        //printf("1-");
        memset(&reccln,0,sizeof(sendbag));
        memset(sendbuf,0,sizeof(sendbag));
        //strcpy(reccln.checkcode,d->checkcode);
        strncpy(rr,d->checkcode,3);
        //printf("%s",rr);
        rr[3]='\0';
        if(!strcmp(rr,"RCI"))///**************如果是RCI物联设备则对Ckcode ——> OUT或者ONL
        {
            talktouser=Print_onlineuser(0,d->TalktoID);
            if(talktouser==NULL)
            {
                strcpy(reccln.checkcode,"OUT");
            }
            else
            {
                char IoTdata[30]="";
                strcpy(IoTdata,"SSS00000000000000000000000000");
                len=send(talktouser->USER_socket,IoTdata,30*sizeof(char),0);
                if(len==SOCKET_ERROR||len==0)
                {
                    ///********************************
                    cln g;
                    strcpy(g.USERID,talktouser->USERID);
                    closesocket(talktouser->USER_socket);
                    delete_out_user(g);
                    ///********************************
                    strcpy(reccln.checkcode,"OUT");
                    strcpy(reccln.DATA,talktouser->info);
                }
                else
                {
                    strcpy(reccln.checkcode,"ONL");
                    strcpy(reccln.DATA,talktouser->info);
                }
            }
        }
        else
        {
            strcpy(reccln.checkcode,"RCO");
        }
        //printf("--%s\n",reccln.checkcode);
        strcpy(reccln.TalktoID,d->TalktoID);
        strcpy(reccln.USERID,a->USERID);
        reccln.save[99]='\n';
        memcpy(sendbuf,&reccln,sizeof(reccln));
        len=send(a->remote_socket,sendbuf,sizeof(sendbag),0);
        if(len==SOCKET_ERROR||len==0)
        {
            //printf("\nÁ¬½Ó%dÍË³ö\n",a->remote_socket);
            closesocket(a->remote_socket);
            delete_out_user(*a);
            return ;
        }
        Sleep(100);
    }
    free(d);

}
