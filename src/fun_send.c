#include"../head/SERVER.h"
DWORD WINAPI fun(LPVOID qn)
{
    char sendbuf[sizeof(sendbag)]= {0};
    SOCKADDR_IN remoteAddr;
    sendbag reccln_udp,rec;
    int nAddrLen = sizeof(remoteAddr);
    while(1)
    {
        int ret = recvfrom(server_sockfd_udp,(char*)&reccln_udp, sizeof(reccln_udp), 0, (SOCKADDR*)&remoteAddr, &nAddrLen);
        if (ret > 0)
        {
            if(strcmp(reccln_udp.checkcode,"UD1"))///�������
            {
                rec=reccln_udp;
                printf("%s:%d",inet_ntoa(remoteAddr.sin_addr),remoteAddr.sin_port);
                CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)UdpPackResolve,&rec,0,NULL);
            }
            else if(!strcmp(reccln_udp.checkcode,"UD1"))///��ʾ�״�����
            {
                USER talktouser=Print_onlineuser(0,reccln_udp.USERID);
                if(talktouser!=NULL)
                {
                    printf("%s:%d",inet_ntoa(remoteAddr.sin_addr),remoteAddr.sin_port);
                    talktouser->USER_socket_udp=remoteAddr;///������Ӧ����
                    strcpy(reccln_udp.checkcode,"UDP");///
                    memset(sendbuf,0,sizeof(sendbag));
                    reccln_udp.save[99]='\n';
                    memcpy(sendbuf,&reccln_udp,sizeof(reccln_udp));
                    //printf("qwqw");
                    sendto(server_sockfd_udp, sendbuf, sizeof(reccln_udp), 0, (SOCKADDR *)&remoteAddr, nAddrLen);
                }
                else
                {
                    strcpy(reccln_udp.checkcode,"udp");///Сд��ʾ����ʧ��
                    memset(sendbuf,0,sizeof(sendbag));
                    reccln_udp.save[99]='\n';
                    memcpy(sendbuf,&reccln_udp,sizeof(reccln_udp));
                    sendto(server_sockfd_udp, sendbuf, sizeof(reccln_udp), 0, (SOCKADDR *)&remoteAddr, nAddrLen);
                }
            }
            else
            {
                printf("\nUDP �쳣:%s,�û�:%s\n",reccln_udp.checkcode,reccln_udp.USERID);
            }
        }
    }
    /*FILE *f=fopen("pic.png","r");
                    strcpy(a->TalktoID,"12345678908");
                    printf("|%d",bitmapfigure(a,f,"PNG"));
                    fclose(f);*/
    return 0;
}

