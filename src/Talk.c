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
        printf("\n����%d�˳�\n",c);
        closesocket(c);
        return 0;
    }
    ///*******************************
    strncpy(tag,reccln.checkcode,2);
    printf("----%s--%s--%d",reccln.checkcode,tag,len);
    ///**********************��֤�Ƿ�Ϊ�Ϸ��û�***************************
    if(!strcmp(tag,CHECK))
    {
        if(!strcmp(tag1,reccln.checkcode))
        {
            printf("\nNOMAL CLIENT:|%s\n",inet_ntoa(a->ADDR.sin_addr));///��
            ///************************ѭ�������û�����******************************

            while(1)
            {
                memset(tag,0,3);
                memset(&reccln,0,sizeof(reccln));
                len=recv(c,(char*)&reccln,sizeof(reccln),0);
                if(len==SOCKET_ERROR||len==0)
                {
                    printf("\n����%d�˳�\n",c);
                    closesocket(c);
                    if(signIN)
                    {
                        delete_out_user(*a);
                    }
                    return 0;
                }
                strncpy(tag,reccln.checkcode,2);
                ///****************************��¼����***********************************
                if(!strcmp(tag,SIGN_IN))
                {
                    strcpy(a->USERID,reccln.USERID);
                    strcpy(a->USERPASSWORD,reccln.USERPASSWORD);
                    printf("%s/%s/",a->USERID,a->USERPASSWORD);
                    if (SIGNIN(a)==1)
                    {
                        printf("\n��½�ɹ�\n");
                        signIN=1;
                        memset(&reccln,0,sizeof(sendbag));
                        memset(sendbuf,0,sizeof(sendbag));
                        strcpy(reccln.checkcode,SIGN_IN);
                        reccln.save[99]='\n';
                        memcpy(sendbuf,&reccln,sizeof(reccln));
                        len=send(c,sendbuf,sizeof(sendbag),0);
                        if(len==SOCKET_ERROR||len==0)
                        {
                            printf("\n����%d�˳�\n",c);
                            closesocket(c);
                            delete_out_user(*a);
                            return 0;
                        }
                    }
                    else
                    {
                        printf("\n��¼ʧ��\n");
                        memset(&reccln,0,sizeof(sendbag));
                        memset(sendbuf,0,sizeof(sendbag));
                        strcpy(reccln.checkcode,"Si");
                        reccln.save[99]='\n';
                        memcpy(sendbuf,&reccln,sizeof(reccln));
                        len=send(c,sendbuf,sizeof(sendbag),0);
                        // free(sendbuf);
                        if(len==SOCKET_ERROR||len==0)
                        {
                            printf("\n����%d�˳�\n",c);
                            closesocket(c);
                            return 0;
                        }
                    }

                }
                ///******************************ע������*********************************
                else if(!strcmp(tag,REGISTER))
                {
                    strcpy(a->USERID,reccln.USERID);
                    strcpy(a->USERPASSWORD,reccln.USERPASSWORD);
                    if (Register(a)==1)
                    {
                        printf("\nע��ɹ�\n");
                        memset(&reccln,0,sizeof(sendbag));
                        memset(sendbuf,0,sizeof(sendbag));
                        strcpy(reccln.checkcode,"RE");
                        reccln.save[99]='\n';
                        memcpy(sendbuf,&reccln,sizeof(reccln));
                        len=send(c,sendbuf,sizeof(reccln),0);
                        if(len==SOCKET_ERROR||len==0)
                        {
                            printf("\n����%d�˳�\n",c);
                            closesocket(c);
                            return 0;
                        }
                    }
                    else
                    {
                        printf("\nע��ʧ��\n");
                        memset(&reccln,0,sizeof(sendbag));
                        memset(sendbuf,0,sizeof(sendbag));
                        strcpy(reccln.checkcode,"Re");
                        reccln.save[99]='\n';
                        memcpy(sendbuf,&reccln,sizeof(reccln));
                        len=send(c,sendbuf,sizeof(sendbag),0);
                        if(len==SOCKET_ERROR||len==0)
                        {
                            printf("\n����%d�˳�\n",c);
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
                        printf("\n���ܳɹ�\n");
                        memset(&reccln,0,sizeof(sendbag));
                        memset(sendbuf,0,sizeof(sendbag));
                        strcpy(reccln.checkcode,"RP");
                        reccln.save[99]='\n';
                        memcpy(sendbuf,&reccln,sizeof(reccln));
                        len=send(c,sendbuf,sizeof(reccln),0);
                        if(len==SOCKET_ERROR||len==0)
                        {
                            printf("\n����%d�˳�\n",c);
                            closesocket(c);
                            return 0;
                        }
                    }
                    else
                    {
                        printf("\n����ʧ��\n");
                        memset(&reccln,0,sizeof(sendbag));
                        memset(sendbuf,0,sizeof(sendbag));
                        strcpy(reccln.checkcode,"Rp");
                        reccln.save[99]='\n';
                        memcpy(sendbuf,&reccln,sizeof(reccln));
                        len=send(c,sendbuf,sizeof(sendbag),0);
                        if(len==SOCKET_ERROR||len==0)
                        {
                            printf("\n����%d�˳�\n",c);
                            closesocket(c);
                            return 0;
                        }
                        else
                        {
                            continue;
                        }

                    }

                }
                ///*****************************����to******************************
                else if(!strcmp(tag,TALK_TO)&&signIN)
                {
                    USER talktouser=Print_onlineuser(0,reccln.TalktoID);
                    if(talktouser==NULL)
                    {
                        printf("�û�%s������",reccln.TalktoID);
                        memset(&reccln,0,sizeof(sendbag));
                        memset(sendbuf,0,sizeof(sendbag));
                        strcpy(reccln.checkcode,"Ta");
                        reccln.save[99]='\n';
                        memcpy(sendbuf,&reccln,sizeof(reccln));
                        len=send(c,sendbuf,sizeof(sendbag),0);
                        // free(sendbuf);
                        if(len==SOCKET_ERROR||len==0)
                        {
                            printf("\n����%d�˳�\n",c);
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
                        printf("\n����%d�˳�\n",c);
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


    /*���տͻ��˵����ݲ����䷢�͸��ͻ���--recv���ؽ��յ����ֽ�����send���ط��͵��ֽ���*/
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
