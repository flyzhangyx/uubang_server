#include"../head/SERVER.h"
void RequestMessage(cln *a,FILE *file)
{
    sendbag reccln;
    int len=0;
    char sendbuf[sizeof(sendbag)]= {0};
    Message d=(Message)malloc(sizeof(struct message));
    rewind(file);
    while(!feof(file) && fread(d,sizeof(struct message),1,file)&&a->info[0]!='N')
    {
        memset(&reccln,0,sizeof(sendbag));
        memset(sendbuf,0,sizeof(sendbag));
        if(!strcmp(d->checkcode,"NCA"))
        {
            strcpy(reccln.checkcode,"NCA");
            //new contact to be added
        }
        else
        {
            strcpy(reccln.checkcode,"NME");
            //new message to be read
        }
        strcpy(reccln.TalktoID,d->TalktoID);
        strcpy(reccln.USERID,d->USERID);
        strcpy(reccln.DATA,d->data);
        reccln.save[99]='\n';
        memcpy(sendbuf,&reccln,sizeof(reccln));
        len=send(a->remote_socket,sendbuf,sizeof(sendbag),0);
        // free(sendbuf);
        if(len==SOCKET_ERROR||len==0)
        {
            //printf("\nÁ¬½Ó%dÍË³ö\n",a->remote_socket);
            closesocket(a->remote_socket);
            delete_out_user(*a);
            return ;
        }
    }
    fclose(file);
}
