#include"../head/SERVER.h"
int initServer()
{
    int scan;
    cln_num=0;
    strcpy(CHECK,"ZY");
    strcpy(SIGN_IN,"SI");//登陆码
    strcpy(REGISTER,"RE");//注册码
    strcpy(MESSAGE,"ME");//信息发送码
    strcpy(TALK_TO,"TA");//通信目标地址码
    strcpy(SIGN_OUT,"SO");//注销登录码
    strcpy(REPWD,"RP");
    warnfile=0;
    logflag=0;
    ///***********socket初始化***********************
    WSADATA wsaData;
    while(1)
    {
        if(!WSAStartup(MAKEWORD(1,1),&wsaData) )
        {
            printf("SOCKET ESTABLISHED SUCCESS!\n");
            break;
        }
        else
        {
            printf("socket not established! If continue to establish? Yes press 1;No press 0");
            scanf("%d",&scan);
            if(scan==0)
                exit(0);
            else if(scan==1)
                continue;
            else
            {
                printf("Input err! Late exit!");
                exit(0);
            }
        }
    }
    SOCKADDR_IN my_addr; //服务器网络地址结构体
    memset(&my_addr,0,sizeof(my_addr)); //数据初始化--清零
    my_addr.sin_family=AF_INET; //设置为IP通信
    my_addr.sin_addr.s_addr=htonl(INADDR_ANY);//服务器IP地址--允许连接到所有本地地址上
    my_addr.sin_port=htons(3566); //服务器端口号 /*创建服务器端套接字--IPv4协议，面向连接通信，TCP协议*/
    if((server_sockfd=socket(AF_INET,SOCK_STREAM,0))==INVALID_SOCKET)
    {
        perror("socket");    /*将套接字绑定到服务器的网络地址上*/
        return -1;
    }
    if (bind(server_sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))==SOCKET_ERROR)
    {
        perror("bind");
        return -1;
    }
    ///*******在线用户链表头初始化********
    do
    {
        onlineUserHead=(struct OnlineUserHead *)malloc(sizeof(struct OnlineUserHead));
    }
    while(onlineUserHead==NULL);
    strcpy(onlineUserHead->DATE,"\0");
    onlineUserHead->OnlineUserNum=0;
    onlineUserHead->next=NULL;
    loginfo=fopen("Loginfo.info","a+");
    REGISTERlocal=fopen("REGISTEDUSER.txt","a+");
    if(REGISTERlocal==NULL)
    {
        perror("本地已注册用户列表读取失败");
        exit(-1);
    }
    else
    {
        do
        {
            RegistedUserHead=(struct OnlineUserHead *)malloc(sizeof(struct OnlineUserHead));///跟Online同样的方式储存
        }
        while(RegistedUserHead==NULL);
        strcpy(RegistedUserHead->DATE,"\0");
        RegistedUserHead->OnlineUserNum=0;
        RegistedUserHead->next=NULL;
        USER d=(USER)malloc(sizeof(struct user));
        cln a;
        while(!feof(REGISTERlocal) && fread(d,sizeof(struct user),1,REGISTERlocal))
        {
            strcpy(a.USERID,d->USERID);
            strcpy(a.USERPASSWORD, d->USERPASSWORD);
            a.ADDR=d->USER_socket_udp;
            //a.remote_socket=d->USER_socket;
            strcpy(a.info,d->info) ;
            AddtoLocal(a);
        }
        free(d);
        printf("本地注册库加载成功！");
    }
    FILE* updversion=fopen("update","r");
    if(updversion)
    {
        fgets(app_version,4,updversion);
        fclose(updversion);
        app_version[3]='\0';
        printf("APP版本-%s\n",app_version);
    }
    else
    {
        printf("更新文件读取失败!");
        return -1;
    }
    return 1;
}
