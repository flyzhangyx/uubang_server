#include"../head/SERVER.h"
int file_tcp_send(cln *a,FILE *file,char* lx,char *name)
{
    int filesize=0,i=0,flag=0,len;
    sendbag data_bag;
    char sendbuf[sizeof(sendbag)]= {0};
    filesize=BitmapSize(file);
    if(!filesize%512)
    {
        flag=filesize/512;
    }
    else
    {
        flag=filesize/512+1;
    }
    char* p=(char *)malloc(flag*512); /* 根据文件大小动态分配内存空间 */
    if(p==NULL)
    {
        return -1;
    }
    USER talktouser=Print_onlineuser(0,a->TalktoID);
    if(talktouser==NULL)
    {
        return -3;
    }
    fseek(file,0L,SEEK_SET); /* 定位到文件开头 */
    fread(p,filesize,1,file);
    USER talkuser=Print_onlineuser(0,a->TalktoID);
    printf("%d",filesize);
    Sleep(5*1000);
    for(i=1; i<=flag; i++)
    {
        memset(&data_bag,0,sizeof(sendbag));
        memset(sendbuf,0,sizeof(sendbag));
        strcpy(data_bag.checkcode,lx);//file info
        strcpy(data_bag.TalktoID,a->TalktoID);
        strcpy(data_bag.USERID,a->USERID);
        Stringcut(p,512*(i-1),512*i-1,data_bag.DATA);
        data_bag.save[99]='\0';
        data_bag.REUSERPASSWORD[0]=i;
        data_bag.REUSERPASSWORD[1]=flag;
        strcpy(data_bag.save,name);
        memcpy(sendbuf,&data_bag,sizeof(sendbag));
        if(talkuser!=NULL)
        {
            len=send(talktouser->USER_socket,sendbuf,sizeof(sendbag),0);
            if(len==SOCKET_ERROR||len==0)
            {
                printf("\n连接%d退出\n",talktouser->USER_socket);
                closesocket(talktouser->USER_socket);
                cln b;
                strcpy(b.USERID,a->TalktoID);
                delete_out_user(b);
                return -4;///表示此次发送失败
            }
            //sendto(server_sockfd_udp, sendbuf, sizeof(sendbag),0, (SOCKADDR*)&(talkuser->USER_socket_udp), sizeof(talkuser->USER_socket_udp));
            Sleep(100);
            //printf("%d_",sendto(server_sockfd_udp, sendbuf, sizeof(sendbag),0, (SOCKADDR*)&(talkuser->USER_socket_udp), sizeof(talkuser->USER_socket_udp)));
        }
        else
        {
            return -1;
        }
    }
    free(p);
    printf("\n");
    return 0;
}
