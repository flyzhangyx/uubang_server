#include"../head/SERVER.h"
int bitmapfigure(cln *a,FILE *file,char* lx)
{
    int filesize=0,i=0,flag=0;
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
        memcpy(sendbuf,&data_bag,sizeof(sendbag));
        if(talkuser!=NULL)
        {
            sendto(server_sockfd_udp, sendbuf, sizeof(sendbag),0, (SOCKADDR*)&(talkuser->USER_socket_udp), sizeof(talkuser->USER_socket_udp));
            Sleep(100);
            printf("%d_",sendto(server_sockfd_udp, sendbuf, sizeof(sendbag),0, (SOCKADDR*)&(talkuser->USER_socket_udp), sizeof(talkuser->USER_socket_udp)));
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
