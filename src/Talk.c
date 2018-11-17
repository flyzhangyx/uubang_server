#include"../head/SERVER.h"
DWORD WINAPI talk(LPVOID b)
{
    int len,signIN=0;
    cln* a=(cln*)b;
    SOCKET c=a->remote_socket;
    sendbag reccln;
    char sendbuf[sizeof(sendbag)]= {0};
    char tag[3],tag1[18]="CH123456";
    memset(tag,0,3);
    memset(&reccln,0,sizeof(reccln));
    ///*************************************
    len=recv(c,(char*)&reccln,sizeof(reccln),0);
    if(len==SOCKET_ERROR||len==0)
    {
        printf("\n连接%d退出\n",c);
        closesocket(c);
        return 0;
    }
    ///*******************************
    strncpy(tag,reccln.checkcode,2);
    printf("----%s--%s--%d",reccln.checkcode,tag,len);
    ///**********************验证是否为合法用户***************************
    if(!strcmp(tag,CHECK))
    {
        if(!strcmp(tag1,reccln.checkcode))
        {
            printf("\nNOMAL CLIENT:|%s\n",inet_ntoa(a->ADDR.sin_addr));///改
            ///************************循环接受用户请求******************************

            while(1)
            {
                memset(tag,0,3);
                memset(&reccln,0,sizeof(reccln));
                len=recv(c,(char*)&reccln,sizeof(reccln),0);
                if(len==SOCKET_ERROR||len==0)
                {
                    printf("\n连接%d退出\n",c);
                    closesocket(c);
                    if(signIN)
                    {
                        delete_out_user(*a);
                    }
                    return 0;
                }
                strncpy(tag,reccln.checkcode,2);
                ///****************************登录请求***********************************
                if(!strcmp(tag,SIGN_IN))
                {
                    strcpy(a->USERID,reccln.USERID);
                    strcpy(a->USERPASSWORD,reccln.USERPASSWORD);
                    printf("%s/%s/",a->USERID,a->USERPASSWORD);
                    if (SIGNIN(a)==1)
                    {
                        printf("\n登陆成功\n");
                        signIN=1;
                        memset(&reccln,0,sizeof(sendbag));
                        memset(sendbuf,0,sizeof(sendbag));
                        strcpy(reccln.checkcode,SIGN_IN);
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
                ///******************************注册请求*********************************
                else if(!strcmp(tag,REGISTER))
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
                else if(!strcmp(tag,TALK_TO)&&signIN)
                {
                    USER talktouser=Print_onlineuser(0,reccln.TalktoID);
                    if(talktouser==NULL)
                    {
                        printf("用户%s不在线",reccln.TalktoID);
                        memset(&reccln,0,sizeof(sendbag));
                        memset(sendbuf,0,sizeof(sendbag));
                        strcpy(reccln.checkcode,"Ta");
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
                    else
                    {
                        ///********************

                    }
                }
                else if(!strcmp(tag,"HB"))
                {
                    memset(&reccln,0,sizeof(sendbag));
                    memset(sendbuf,0,sizeof(sendbag));
                    strcpy(reccln.checkcode,"HB");
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
///*****************************************************************************
            }
        }
        else
        {
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


    /*接收客户端的数据并将其发送给客户端--recv返回接收到的字节数，send返回发送的字节数*/
//    memset(buf,0,BUFSIZ);
//    while((recv(c,buf,BUFSIZ+sizeof(char),0))>0)
//    {
//        memset(tag,0,2);
//        strncpy(tag,buf,2);
//        len=strlen(buf);
//        for(i=2; i<=len; i++)
//        {
//            body[i-2]=buf[i];
//        }
//        // if(!strcmp(tag,TALK_TO))
//        {
//            printf("%s",body);
//            printf("\n......................");
//        }
//        memset(buf,0,BUFSIZ);
//    }
//    delete_out_user(*a);
    return 0;
}
