#include"../head/SERVER.h"
int initServer()
{
    int scan;
    cln_num=0;
    strcpy(CHECK,"ZY");
    strcpy(SIGN_IN,"SI");//��½��
    strcpy(REGISTER,"RE");//ע����
    strcpy(MESSAGE,"ME");//��Ϣ������
    strcpy(TALK_TO,"TA");//ͨ��Ŀ���ַ��
    strcpy(SIGN_OUT,"SO");//ע����¼��
    strcpy(REPWD,"RP");
    warnfile=0;
    logflag=0;
    ///***********socket��ʼ��***********************
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
    SOCKADDR_IN my_addr; //�����������ַ�ṹ��
    memset(&my_addr,0,sizeof(my_addr)); //���ݳ�ʼ��--����
    my_addr.sin_family=AF_INET; //����ΪIPͨ��
    my_addr.sin_addr.s_addr=htonl(INADDR_ANY);//������IP��ַ--�������ӵ����б��ص�ַ��
    my_addr.sin_port=htons(3566); //�������˿ں� /*�������������׽���--IPv4Э�飬��������ͨ�ţ�TCPЭ��*/
    if((server_sockfd=socket(AF_INET,SOCK_STREAM,0))==INVALID_SOCKET)
    {
        perror("socket");    /*���׽��ְ󶨵��������������ַ��*/
        return -1;
    }
    if (bind(server_sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))==SOCKET_ERROR)
    {
        perror("bind");
        return -1;
    }
    ///*******�����û�����ͷ��ʼ��********
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
        perror("������ע���û��б��ȡʧ��");
        exit(-1);
    }
    else
    {
        do
        {
            RegistedUserHead=(struct OnlineUserHead *)malloc(sizeof(struct OnlineUserHead));///��Onlineͬ���ķ�ʽ����
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
        printf("����ע�����سɹ���");
    }
    FILE* updversion=fopen("update","r");
    if(updversion)
    {
        fgets(app_version,4,updversion);
        fclose(updversion);
        app_version[3]='\0';
        printf("APP�汾-%s\n",app_version);
    }
    else
    {
        printf("�����ļ���ȡʧ��!");
        return -1;
    }
    return 1;
}
