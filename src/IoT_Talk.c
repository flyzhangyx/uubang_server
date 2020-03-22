#include"../head/SERVER.h"
int IoTtalk(char* Contacta,char* Messagea,cln* b)
{
    char *timenow;
    time_t t;//定义一个时间变量
   // USER user=NULL;
    char IoTdata[30]="";
    FILE* usercontact=NULL;
    FILE* usermessage=NULL;
    int len,signIN=0;
    cln* a=(cln*)b;
    SOCKET c=a->remote_socket;
    sendbag reccln;
    char sendbuf[sizeof(sendbag)]= {0};
    char tag[4];
    ///*************IoT*************
    while(1)
    {
        memset(tag,0,4);
        memset(&reccln,0,sizeof(reccln));
        len=recv(c,IoTdata,30*sizeof(char),0);///*****************************1
        if(len==SOCKET_ERROR||len==0)
        {
            printf("\n连接%d退出\n",c);
            closesocket(c);
            if(signIN)
            {
                printf("SIGNIN?2TIMES?");
                delete_out_user(*a);
            }
            return 0;
        }
        strncpy(tag,IoTdata,3);///************************2
        /*if(!strcmp(tag,"RCO"))
        {
            usercontact=fopen(Contacta,"a+");
            RequestContact(a,usercontact);
            fclose(usercontact);
        }*/
        if(!strcmp(tag,"RMI"))///******请求任务///*****暂时废弃
        {
            usermessage=fopen(Messagea,"a+");
            RequestMessage(a,usermessage);
            usermessage=fopen(Messagea,"w+");//clear
            fclose(usermessage);
        }
        else if(!strcmp(tag,"TAI"))///****请求通知知任务情况
        {
            //printf("TA");

            Stringcut(IoTdata,3,13,reccln.TalktoID);
            Stringcut(IoTdata,14,29,reccln.DATA);
            USER iot=Print_onlineuser(0,a->USERID);
            if(iot!=NULL)
            {
                strcpy(iot->info,reccln.DATA);
            }
            if(Check_Id_Pwd(0,*a)!=-1)
            {
                USER talktouser=Print_onlineuser(0,reccln.TalktoID);
                //user=Print_onlineuser(0,a->USERID);
                if(talktouser==NULL)
                {
                    Message mes=(Message)malloc(sizeof(struct message));
                    memset(mes,0,sizeof(contact));

                    strcpy(mes->checkcode,"NMI");
                    strcpy(mes->TalktoID,a->USERID);
                    strcpy(mes->USERID,reccln.TalktoID);
                    strcpy(mes->data,reccln.DATA);
                    printf("用户%s不在线TAN",reccln.TalktoID);
                    char talkto[15]= {'0'};
                    strcpy(talkto,reccln.TalktoID);
                    strcat(talkto,"ME");
                    FILE* ss=fopen(talkto,"a+");///**********dakai
                    fwrite(mes,sizeof(struct message),1,ss);
                    fflush(ss);
                    fclose(ss);
                    free(mes);
                    strcpy(IoTdata,"TAN");
                    strcat(IoTdata,reccln.TalktoID);
                    len=send(c,IoTdata,30*sizeof(char),0);
                    // free(sendbuf);
                    if(len==SOCKET_ERROR||len==0)
                    {
                        printf("\n连接%d退出\n",c);
                        closesocket(c);
                        delete_out_user(*a);
                        return 0;
                    }
                }
                else
                {
                    //memset(reccln.checkcode,0,sizeof(contact));
                    memset(sendbuf,0,sizeof(sendbag));
                    strcpy(reccln.checkcode,"TAI");
                    reccln.save[99]='\n';
                    char temp[12]= {0};
                    strcpy(temp,reccln.USERID);
                    printf("%s",temp);
                    strcpy(reccln.USERID,reccln.TalktoID);
                    strcpy(reccln.TalktoID,a->USERID);
                    //strcpy(mes->data,reccln.DATA);
                    memcpy(sendbuf,&reccln,sizeof(reccln));
                    len=send(talktouser->USER_socket,sendbuf,sizeof(sendbag),0);
                    if(len==SOCKET_ERROR||len==0)
                    {
                        printf("\n连接%d退出\n",c);
                        closesocket(talktouser->USER_socket);
                        //delete_out_user(*a);
                        return 0;
                    }
                    strcpy(IoTdata,"TAS");
                    strcat(IoTdata,reccln.USERID);
                    len=send(c,IoTdata,30*sizeof(char),0);
                    if(len==SOCKET_ERROR||len==0)
                    {
                        printf("\n连接%d退出\n",c);
                        closesocket(c);
                        delete_out_user(*a);
                        return 0;
                    }
                }
            }
            else
            {
                printf("用户%s不存在",reccln.TalktoID);
                strcpy(IoTdata,"Taa");
                strcat(IoTdata,reccln.TalktoID);
                len=send(c,IoTdata,30*sizeof(char),0);
                // free(sendbuf);
                if(len==SOCKET_ERROR||len==0)
                {
                    printf("\n连接%d退出\n",c);
                    closesocket(c);
                    delete_out_user(*a);
                    return 0;
                }
            }
        }
        else if(!strcmp(tag,"ADS"))///****only reply****
        {
             //char rep[18]="";
            Stringcut(IoTdata,3,13,a->TalktoID);
            a->TalktoID[11]='\0';
            //strcpy(a->TalktoID,rep);
            usercontact=fopen(Contacta,"a+");
            Contact mes=(Contact)malloc(sizeof(struct contact));
            memset(mes,0,sizeof(contact));
            memset(sendbuf,0,sizeof(sendbag));
            strcpy(mes->checkcode,"RCO");
            strcpy(mes->TalktoID,reccln.TalktoID);
            strcpy(mes->USERID,a->USERID);
            fwrite(mes,sizeof(struct contact),1,usercontact);
            fflush(usercontact);
            fclose(usercontact);
            reccln.save[99]='\n';
            memset(mes,0,sizeof(contact));
            strcpy(mes->checkcode,"RCI");///****物联网设备添加成功
            strcpy(mes->TalktoID,a->USERID);
            strcpy(mes->USERID,a->TalktoID);
            ///**********dakai

            char talkto[15]= "";
            strcpy(talkto,a->TalktoID);
            strcat(talkto,"CO");
            FILE* ss=fopen(talkto,"a+");///****dakai***

            fwrite(mes,sizeof(struct contact),1,ss);
            fflush(ss);
            fclose(ss);
            strcpy(IoTdata,"ADS");
            strcat(IoTdata,reccln.TalktoID);
            len=send(c,IoTdata,30*sizeof(char),0);
            if(len==SOCKET_ERROR||len==0)
            {
                printf("\n连接%d退出\n",c);
                closesocket(c);
                delete_out_user(*a);
                return 0;
            }
        }
        else if(!strcmp(tag,"HBI"))///**************************************
        {
            t=time(NULL);
            timenow=ctime(&t);
            /*memset(&reccln,0,sizeof(sendbag));
            memset(sendbuf,0,sizeof(sendbag));
            strcpy(reccln.checkcode,"HBI");
            strcpy(reccln.DATA,timenow);
            reccln.save[99]='\n';*/
            strcpy(IoTdata,"HBI");
            strncat(IoTdata,timenow,24);
            /*memcpy(sendbuf,&reccln,sizeof(reccln));*/
            len=send(c,IoTdata,30*sizeof(char),0);
            // free(sendbuf);
            printf("\nHBI\n");
            if(len==SOCKET_ERROR||len==0)
            {
                printf("\n连接%d退出\n",c);
                closesocket(c);
                delete_out_user(*a);
                return 0;
            }
        }
        else if(!strcmp(tag,"STO"))
        {
            closesocket(c);
            delete_out_user(*a);
        }
        else
        {
            printf("%s",IoTdata);
        }
    }
}
