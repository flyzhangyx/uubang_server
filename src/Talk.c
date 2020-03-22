#include"../head/SERVER.h"
DWORD WINAPI talk(LPVOID b)
{
    FILE* usercontact=NULL;
    FILE* usermessage=NULL;
    int len,signIN=0,creat_check_alive=0;
    cln* a=(cln*)b;
    char IoTdata[30]="";
    char logcat[256]="";
    char Contacta[30]= {'0'};
    char Messagea[30]= {'0'};
    char rec[15]="";
    SOCKET c=a->remote_socket;
    sendbag reccln;
    char sendbuf[sizeof(sendbag)]= {0};
    char tag[4],tag1[18]="ZYXX1226";
    memset(tag,0,3);
    memset(&reccln,0,sizeof(reccln));
    ///*************************************
    len=recv(c,(char*)&reccln,8*sizeof(char),0);
    if(len==SOCKET_ERROR||len==0)
    {
        printf("\n连接%d退出\n",c);
        closesocket(c);
        return 0;
    }
    ///*******************************
    strncpy(tag,reccln.checkcode,2);
    printf("--%s--%s--",reccln.checkcode,tag);
    memset(logcat,0,100*sizeof(char));
    strcpy(logcat,inet_ntoa(a->ADDR.sin_addr));
    strcat(logcat,"|");
    strcat(logcat,reccln.checkcode);
    logwrite(logcat);
    int isRedo=0;
    ///**********************验证是否为合法用户***************************
    if(!strcmp(tag,CHECK))
    {
        if(!strcmp(tag1,reccln.checkcode))
        {
            printf("\nNOMAL CLIENT:|%s\n",inet_ntoa(a->ADDR.sin_addr));///改
            ///************************循环接受用户请求******************************
            while(1)
            {
                memset(tag,0,4);
                memset(&reccln,0,sizeof(reccln));
                if(!isRedo)
                {
                    len=recv(c,(char*)&reccln,sizeof(reccln),0);
                    if(len==SOCKET_ERROR||len==0)
                    {
                        printf("\n连接%d退出\n",c);
                        closesocket(c);
                        if(signIN)
                        {
                            printf("?TEST>");
                            //delete_out_user(*a);
                            //newOnlineUser(*a);
                        }
                        return 0;
                    }
                }
                isRedo=0;
                strncpy(tag,reccln.checkcode,4);
                tag[3]='\0';
                //printf("%s\n",reccln.checkcode);
                ///***********************************************************************
                if(signIN&&a->info[0]!='N'&&!creat_check_alive)
                {
                    creat_check_alive=1;
                    CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Check_alive,a,0,NULL);
                }
                if(!strcmp(tag,REGISTER))
                {
                    strcpy(a->USERID,reccln.USERID);
                    strcpy(a->USERPASSWORD,reccln.USERPASSWORD);
                    if (Register(a)==1)
                    {
                        printf("\n注册成功\n");
                        memset(&reccln,0,sizeof(sendbag));
                        memset(sendbuf,0,sizeof(sendbag));
                        strcpy(reccln.checkcode,"RE");
                        reccln.save[99]='\n';
                        memcpy(sendbuf,&reccln,sizeof(reccln));
                        len=send(c,sendbuf,sizeof(reccln),0);
                        if(len==SOCKET_ERROR||len==0)
                        {
                            printf("\n连接%d退出\n",c);
                            closesocket(c);
                            return 0;
                        }
                    }
                    else
                    {
                        printf("\n注册失败\n");
                        memset(&reccln,0,sizeof(sendbag));
                        memset(sendbuf,0,sizeof(sendbag));
                        strcpy(reccln.checkcode,"Re");
                        reccln.save[99]='\n';
                        memcpy(sendbuf,&reccln,sizeof(reccln));
                        len=send(c,sendbuf,sizeof(sendbag),0);
                        if(len==SOCKET_ERROR||len==0)
                        {
                            printf("\n连接%d退出\n",c);
                            closesocket(c);
                            return 0;
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
                ///****************************登录请求***********************************
                else if(!strcmp(tag,SIGN_IN))
                {
                    strcpy(a->USERID,reccln.USERID);
                    strcpy(a->USERPASSWORD,reccln.USERPASSWORD);
                    printf("%s/%s/",a->USERID,a->USERPASSWORD);
                    if (SIGNIN(a)==1)
                    {
                        printf("\n登陆成功\n");
                        signIN=1;
                        a->info[0]='Y';
                        memset(&reccln,0,sizeof(sendbag));
                        memset(sendbuf,0,sizeof(sendbag));
                        strcpy(reccln.checkcode,SIGN_IN);
                        reccln.save[99]='\n';
                        memcpy(sendbuf,&reccln,sizeof(reccln));
                        strcpy(Contacta,a->USERID);
                        strcat(Contacta,"/");
                        strcat(Contacta,a->USERID);
                        strcat(Contacta,"CO");
                        //usercontact=fopen(Contact,"a+");

                        strcpy(Messagea,a->USERID);
                        strcat(Messagea,"/");
                        strcat(Messagea,a->USERID);
                        strcat(Messagea,"ME");
                        len=send(c,sendbuf,sizeof(sendbag),0);

                        if(len==SOCKET_ERROR||len==0)
                        {
                            printf("\n连接%d退出\n",c);
                            closesocket(c);
                            delete_out_user(*a);
                            return 0;
                        }


                        //
                    }
                    else
                    {
                        printf("\n登录失败\n");
                        memset(&reccln,0,sizeof(sendbag));
                        memset(sendbuf,0,sizeof(sendbag));
                        strcpy(reccln.checkcode,"Si");
                        reccln.save[99]='\n';
                        memcpy(sendbuf,&reccln,sizeof(reccln));
                        len=send(c,sendbuf,sizeof(sendbag),0);
                        // free(sendbuf);
                        if(len==SOCKET_ERROR||len==0)
                        {
                            printf("\n连接%d退出\n",c);
                            closesocket(c);
                            return 0;
                        }
                    }
                }
                ///****************************************************
                else if(!strcmp(tag,"RCO"))
                {
                    usercontact=fopen(Contacta,"a+");
                    RequestContact(a,usercontact);
                    fclose(usercontact);

                }
                else if(!strcmp(tag,"UPD"))
                {
                    memset(&reccln,0,sizeof(sendbag));
                    memset(sendbuf,0,sizeof(sendbag));
                    strcpy(reccln.checkcode,"UPD");
                    strcpy(reccln.DATA,app_version);
                    reccln.save[99]='\n';
                    memcpy(sendbuf,&reccln,sizeof(reccln));
                    len=send(c,sendbuf,sizeof(sendbag),0);
                    //printf("\nupdate\n");
                }
                else if(!strcmp(tag,"RME"))
                {
                    usermessage=fopen(Messagea,"a+");
                    RequestMessage(a,usermessage);
                    usermessage=fopen(Messagea,"w+");//clear
                    fclose(usermessage);
                }
                ///****************************************************
                else if(!strcmp(tag,REPWD))
                {
                    strcpy(a->USERID,reccln.USERID);
                    strcpy(a->USERPASSWORD,reccln.USERPASSWORD);
                    strcpy(a->REUSERPASSWORD,reccln.REUSERPASSWORD);
                    if (DeleteFileUser(*a)==1)
                    {
                        printf("\n改密成功\n");
                        memset(&reccln,0,sizeof(sendbag));
                        memset(sendbuf,0,sizeof(sendbag));
                        strcpy(reccln.checkcode,"RP");
                        reccln.save[99]='\n';
                        memcpy(sendbuf,&reccln,sizeof(reccln));
                        len=send(c,sendbuf,sizeof(reccln),0);
                        if(len==SOCKET_ERROR||len==0)
                        {
                            printf("\n连接%d退出\n",c);
                            closesocket(c);
                            return 0;
                        }
                    }
                    else
                    {
                        printf("\n改密失败\n");
                        memset(&reccln,0,sizeof(sendbag));
                        memset(sendbuf,0,sizeof(sendbag));
                        strcpy(reccln.checkcode,"Rp");
                        reccln.save[99]='\n';
                        memcpy(sendbuf,&reccln,sizeof(reccln));
                        len=send(c,sendbuf,sizeof(sendbag),0);
                        if(len==SOCKET_ERROR||len==0)
                        {
                            printf("\n连接%d退出\n",c);
                            closesocket(c);
                            return 0;
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
                ///*****************************讨论to******************************
                else if(!strcmp(tag,"TAI")&&signIN)
                {
                    if(Check_Id_Pwd(0,*a)!=-1)
                    {
                        USER talktouser=Print_onlineuser(0,reccln.TalktoID);
                        if(talktouser==NULL)
                        {
                            memset(&reccln,0,sizeof(sendbag));
                            memset(sendbuf,0,sizeof(sendbag));
                            strcpy(reccln.checkcode,"TNI");//TA but not online
                            reccln.save[99]='\n';
                            memcpy(sendbuf,&reccln,sizeof(sendbag));
                            len=send(c,sendbuf,sizeof(sendbag),0);
                            if(len==SOCKET_ERROR||len==0)
                            {
                                printf("\n连接%d退出\n",c);
                                closesocket(c);
                                delete_out_user(*a);
                                return 0;
                            }
                            ///**********Do nothing************
                        }
                        else
                        {
                            //strcpy(talktouser.info,reccln.TalktoID);
                            ///******如果是对物联设备CD=TA123457///******************************************************
                            strcpy(IoTdata,"CMD");
                            //strncat(IoTdata,a->USERID,11);
                            strncat(IoTdata,reccln.DATA,26);
                            //printf("%s",reccln.DATA);
                            /*memcpy(sendbuf,&reccln,sizeof(reccln));*/
                            len=send(talktouser->USER_socket,IoTdata,30*sizeof(char),0);
                            // free(sendbuf);

                            if(len==SOCKET_ERROR||len==0)
                            {
                                printf("\n连接%d退出\n",c);
                                closesocket(talktouser->USER_socket);
                                return 0;
                            }
                            //memset(&reccln,0,sizeof(sendbag));
                            memset(sendbuf,0,sizeof(sendbag));
                            strcpy(reccln.checkcode,"TAi");
                            strcpy(reccln.DATA,talktouser->info);
                            reccln.save[99]='\n';
                            memcpy(sendbuf,&reccln,sizeof(reccln));
                            /*len=send(c,sendbuf,sizeof(sendbag),0);
                            if(len==SOCKET_ERROR||len==0)
                            {
                                printf("\n连接%d退出\n",c);
                                closesocket(c);
                                delete_out_user(*a);
                                return 0;
                            }*/
                        }
                    }
                }
                else if(!strcmp(tag,TALK_TO)&&signIN)
                {
                    if(Check_Id_Pwd(0,*a)!=-1)
                    {
                        cln d;
                        strcpy(d.USERID,reccln.TalktoID);
                        USER talktouser=Print_onlineuser(0,reccln.TalktoID);
                        if(talktouser==NULL)
                        {
                            Message mes=(Message)malloc(sizeof(struct message));
                            memset(mes,0,sizeof(contact));
                            strcpy(mes->checkcode,"NME");
                            strcpy(mes->TalktoID,a->USERID);
                            strcpy(mes->USERID,reccln.TalktoID);
                            strcpy(mes->data,reccln.DATA);
                            printf("用户%s不在线TAN",reccln.TalktoID);
                            char talkto[30]= {'0'};
                            strcpy(talkto,reccln.TalktoID);
                            strcat(talkto,"/");
                            strcat(talkto,reccln.TalktoID);
                            strcat(talkto,"ME");
                            FILE* ss=fopen(talkto,"a+");///**********dakai
                            fwrite(mes,sizeof(struct message),1,ss);
                            fflush(ss);
                            fclose(ss);
                            memset(&reccln,0,sizeof(sendbag));
                            memset(sendbuf,0,sizeof(sendbag));
                            strcpy(reccln.checkcode,"TAN");//TA but not online
                            reccln.save[99]='\n';
                            memcpy(sendbuf,&reccln,sizeof(sendbag));
                            len=send(c,sendbuf,sizeof(sendbag),0);
                            free(mes);
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
                            strcpy(reccln.checkcode,"TAT");
                            //strcpy(reccln.DATA,"isharelifeHB");
                            reccln.save[99]='\n';
                            char temp[12]= {0};
                            strcpy(temp,reccln.USERID);
                            printf("%s",temp);
                            strcpy(reccln.USERID,reccln.TalktoID);
                            strcpy(reccln.TalktoID,temp);
                            memcpy(sendbuf,&reccln,sizeof(reccln));
                            len=2;
                            //send(talktouser->USER_socket,"isharelife",11*sizeof(char),0);
                            if(len==SOCKET_ERROR||len==0)
                            {
                                printf("\n连接%d退出\n",c);
                                closesocket(talktouser->USER_socket);
                                printf("\nTAI return to redo\n");
                                delete_out_user(d);
                                isRedo=1;
                                strcpy(temp,reccln.USERID);
                                strcpy(reccln.USERID,reccln.TalktoID);
                                strcpy(reccln.TalktoID,temp);
                                strcpy(reccln.checkcode,"TAI");
                                continue;
                            }
                            else
                            {
                                len=send(talktouser->USER_socket,sendbuf,sizeof(sendbag),0);

                            }
                            memset(&reccln,0,sizeof(sendbag));
                            memset(sendbuf,0,sizeof(sendbag));
                            strcpy(reccln.checkcode,"TAS");
                            strcpy(reccln.TalktoID,a->TalktoID);
                            strcpy(reccln.USERID,a->USERID);
                            reccln.save[99]='\n';
                            memcpy(sendbuf,&reccln,sizeof(reccln));
                            len=send(c,sendbuf,sizeof(sendbag),0);
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
                        memset(&reccln,0,sizeof(sendbag));
                        memset(sendbuf,0,sizeof(sendbag));
                        strcpy(reccln.checkcode,"Taa");//TA but not online
                        reccln.save[99]='\n';
                        memcpy(sendbuf,&reccln,sizeof(reccln));
                        len=send(c,sendbuf,sizeof(sendbag),0);
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
                else if(!strcmp(tag,"ADD")&&signIN)
                {
                    cln d;
                    char IoTdevice[5]="";
                    int F=0;
                    strcpy(d.USERID,reccln.TalktoID);
                    if(Check_Id_Pwd(1,d)!=-1)
                    {
                        strncpy(IoTdevice,reccln.checkcode,4);
                        IoTdevice[4]='\0';
                        if(!strcmp(IoTdevice,"ADDI"))
                        {
                            F=1;
                        }
                        USER talktouser=Print_onlineuser(0,reccln.TalktoID);
                        if(talktouser==NULL&&F!=1)
                        {
                            Message mes=(Message)malloc(sizeof(struct message));
                            memset(mes,0,sizeof(contact));
                            memset(mes,0,sizeof(contact));
                            strcpy(mes->checkcode,"NCA");
                            strcpy(mes->TalktoID,a->USERID);
                            strcpy(mes->USERID,reccln.TalktoID);
                            strcpy(mes->data,reccln.DATA);
                            printf("用户%s不在线ADD",reccln.TalktoID);
                            char talkto[30]= {'0'};
                            strcpy(talkto,reccln.TalktoID);
                            strcat(talkto,"/");
                            strcat(talkto,reccln.TalktoID);
                            strcat(talkto,"ME");
                            memset(&reccln,0,sizeof(sendbag));
                            memset(sendbuf,0,sizeof(sendbag));
                            strcpy(reccln.checkcode,"ADN");
                            //TA but not online
                            strcpy(reccln.TalktoID,a->TalktoID);
                            strcpy(reccln.USERID,a->USERID);
                            reccln.save[99]='\n';
                            memcpy(sendbuf,&reccln,sizeof(reccln));
                            FILE* ss=fopen(talkto,"a+");///**********dakai
                            fwrite(mes,sizeof(struct message),1,ss);
                            fflush(ss);
                            fclose(ss);
                            free(mes);
                            len=send(c,sendbuf,sizeof(sendbag),0);
                            if(len==SOCKET_ERROR||len==0)
                            {
                                printf("\n连接%d退出\n",c);
                                closesocket(c);
                                delete_out_user(*a);
                                return 0;
                            }
                        }
                        else if(talktouser!=NULL&&F!=1)
                        {

                            //memset(&reccln,0,sizeof(sendbag));
                            memset(sendbuf,0,sizeof(sendbag));
                            strcpy(reccln.checkcode,"ADT");
                            reccln.save[99]='\n';
                            char temp[12]= {0};
                            strcpy(temp,reccln.USERID);
                            strcpy(reccln.USERID,reccln.TalktoID);
                            strcpy(reccln.TalktoID,temp);
                            reccln.save[99]='\n';
                            memcpy(sendbuf,&reccln,sizeof(reccln));
                            len=send(talktouser->USER_socket,sendbuf,sizeof(sendbag),0);
                            if(len==SOCKET_ERROR||len==0)
                            {
                                printf("\n连接%d退出\n",c);
                                closesocket(talktouser->USER_socket);
                                delete_out_user(d);
                                isRedo=1;
                                strcpy(temp,reccln.USERID);
                                strcpy(reccln.USERID,reccln.TalktoID);
                                strcpy(reccln.TalktoID,temp);
                                continue;
                            }
                            memset(&reccln,0,sizeof(sendbag));
                            memset(sendbuf,0,sizeof(sendbag));
                            strcpy(reccln.TalktoID,a->TalktoID);
                            strcpy(reccln.USERID,a->USERID);
                            strcpy(reccln.checkcode,"ADD");
                            reccln.save[99]='\n';
                            memcpy(sendbuf,&reccln,sizeof(reccln));
                            len=send(c,sendbuf,sizeof(sendbag),0);
                            if(len==SOCKET_ERROR||len==0)
                            {
                                printf("\n连接%d退出\n",c);
                                closesocket(c);
                                delete_out_user(*a);
                                return 0;
                            }
                            ///********************

                        }
                        else if(F==1&&talktouser!=NULL)
                        {
                            char IoTcommand[30]="";
                            strcpy(IoTcommand,"ADD");
                            strncat(IoTcommand,a->USERID,20);
                            len=send(talktouser->USER_socket,IoTcommand,30*sizeof(char),0);
                            // free(sendbuf);
                            if(len==SOCKET_ERROR||len==0)
                            {
                                printf("\n连接%d退出\n",c);
                                closesocket(talktouser->USER_socket);
                                return 0;
                            }
                        }
                    }
                    else
                    {
                        printf("用户%s不存在ADD",reccln.TalktoID);
                        //memset(&reccln,0,sizeof(sendbag));
                        memset(sendbuf,0,sizeof(sendbag));
                        strcpy(reccln.checkcode,"Add");//TA but not online
                        reccln.save[99]='\n';
                        memcpy(sendbuf,&reccln,sizeof(reccln));
                        len=send(c,sendbuf,sizeof(sendbag),0);
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
                ///*******************************************
                else if(!strcmp(tag,"ADS"))///****only reply****
                {
                    usercontact=fopen(Contacta,"a+");
                    Contact mes=(Contact)malloc(sizeof(struct contact));
                    memset(mes,0,sizeof(contact));
                    memset(sendbuf,0,sizeof(sendbag));

                    strcpy(mes->checkcode,"RCO");
                    strcpy(mes->TalktoID,reccln.TalktoID);
                    strcpy(mes->USERID,reccln.USERID);

                    fwrite(mes,sizeof(struct contact),1,usercontact);
                    fflush(usercontact);
                    fclose(usercontact);
                    reccln.save[99]='\n';
                    memset(mes,0,sizeof(contact));
                    strcpy(mes->checkcode,"RCO");
                    strcpy(mes->TalktoID,reccln.USERID);
                    strcpy(mes->USERID,reccln.TalktoID);
                    ///**********dakai

                    char talkto[30]= {'0'};
                    strcpy(talkto,reccln.TalktoID);
                    strcat(talkto,"/");
                    strcat(talkto,reccln.TalktoID);
                    strcat(talkto,"CO");
                    FILE* ss=fopen(talkto,"a+");///**********dakai

                    fwrite(mes,sizeof(struct contact),1,ss);
                    fflush(ss);
                    fclose(ss);
                    strcpy(reccln.checkcode,"ADS");
                    reccln.save[99]='\n';
                    memcpy(sendbuf,&reccln,sizeof(reccln));
                    len=send(c,sendbuf,sizeof(sendbag),0);
                    if(len==SOCKET_ERROR||len==0)
                    {
                        printf("\n连接%d退出\n",c);
                        closesocket(c);
                        delete_out_user(*a);
                        return 0;
                    }
                }
                ///*********************************************
                else if(!strcmp(tag,"HB"))
                {
                    memset(&reccln,0,sizeof(sendbag));
                    memset(sendbuf,0,sizeof(sendbag));
                    strcpy(reccln.checkcode,"HB");
                    reccln.save[99]='\n';
                    memcpy(sendbuf,&reccln,sizeof(reccln));
                    len=send(c,sendbuf,sizeof(sendbag),0);
                    // free(sendbuf);
                    printf("\nHB\n");
                    if(len==SOCKET_ERROR||len==0)
                    {
                        printf("\n连接%d退出\n",c);
                        closesocket(c);
                        return 0;
                    }
                }
                else if(!strcmp(tag,"STO"))
                {
                    memset(&reccln,0,sizeof(sendbag));
                    memset(sendbuf,0,sizeof(sendbag));
                    strcpy(reccln.checkcode,"STO");
                    reccln.save[99]='\n';
                    memcpy(sendbuf,&reccln,sizeof(reccln));
                    len=send(a->remote_socket,sendbuf,sizeof(sendbag),0);
                    if(len==SOCKET_ERROR||len==0)
                    {
                        printf("\n连接%d退出\n",c);
                        closesocket(c);
                        delete_out_user(*a);
                        return 0;
                    }
                    delete_out_user(*a);
                    printf("\n%s\n",reccln.checkcode);
                    a->info[0]='N';
                    creat_check_alive=0;
                }
///***************************************IOT**************************************
            }
        }
        else if(!strcmp("ZYXX1227",reccln.checkcode))
        {
            ///************************************
            printf("\nNOMAL IoT_CLIENT:|%s\n",inet_ntoa(a->ADDR.sin_addr));///改
            //len=recv(c,rec,1*sizeof(char),0);
            //send(c,"123456789012345678901234567890",30*sizeof(char),0);
            recv(c,rec,12*sizeof(char),0);
            strncpy(a->USERID,rec,12);
            printf("%s",rec);
            a->USERID[11] ='\0';
            printf("--%s",a->USERID);
            recv(c,rec,10*sizeof(char),0);
            strncpy(a->USERPASSWORD,rec,10);
            a->USERPASSWORD[9]='\0';
            printf("/%s\n",a->USERPASSWORD);
            printf("\nUnecessary Regist\n");
            ///*************************************
            Register(a);
            if (SIGNIN(a)==1)
            {
                printf("\n登陆成功\n");
                signIN=1;
                strcpy(IoTdata,"SII");
                strcat(IoTdata,a->USERID);
                len=send(c,IoTdata,30*sizeof(char),0);
                if(len==SOCKET_ERROR||len==0)
                {
                    printf("\n连接%d退出\n",c);
                    closesocket(c);
                    delete_out_user(*a);
                    return 0;
                }
                strcpy(Contacta,a->USERID);
                strcat(Contacta,"CO");
                //usercontact=fopen(Contact,"a+");
                strcpy(Messagea,a->USERID);
                strcat(Messagea,"ME");
                ///*************进入
                IoTtalk(Contacta,Messagea,a);
                //
            }
            else
            {
                printf("\n登录失败\n");
                memset(&reccln,0,sizeof(sendbag));
                memset(sendbuf,0,sizeof(sendbag));
                strcpy(IoTdata,"Sii");
                strcat(IoTdata,a->USERID);
                len=send(c,IoTdata,30*sizeof(char),0);
                if(len==SOCKET_ERROR||len==0)
                {
                    printf("\n连接%d退出\n",c);
                    closesocket(c);
                    return 0;
                }
            }
        }
        else
        {
            //printf("%s",reccln.USERID);
            closesocket(c);
            printf("\nIllegal user\n ");
            return 0;
        }
    }
    else
    {
        closesocket(c);
        printf("\nIllegal user\n ");
        return 0;
    }

    return 0;
}
