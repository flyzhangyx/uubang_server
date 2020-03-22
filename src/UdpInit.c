#include"../head/SERVER.h"
int UdpInit(int port)
{
    SOCKADDR_IN my_addr; //�����������ַ�ṹ��
    memset(&my_addr,0,sizeof(my_addr)); //���ݳ�ʼ��--����
    my_addr.sin_family=AF_INET; //����ΪIPͨ��
    my_addr.sin_addr.s_addr=htonl(INADDR_ANY);//������IP��ַ--�������ӵ����б��ص�ַ��
    my_addr.sin_port=htons(port); //UDP�������˿ں� /*�������������׽���--IPv4Э�飬��������ͨ�ţ�TCPЭ��*/
    if((server_sockfd_udp=socket(AF_INET,SOCK_DGRAM,0))==INVALID_SOCKET)
    {
        perror("socket");    /*���׽��ְ󶨵��������������ַ��*/
        return -1;
    }
    if (bind(server_sockfd_udp,(SOCKADDR*)&my_addr,sizeof(SOCKADDR))==SOCKET_ERROR)
    {
        perror("bind");
        return -1;
    }
    return 0;
}
