#include"../head/SERVER.h"
int UdpInit(int port)
{
    SOCKADDR_IN my_addr; //服务器网络地址结构体
    memset(&my_addr,0,sizeof(my_addr)); //数据初始化--清零
    my_addr.sin_family=AF_INET; //设置为IP通信
    my_addr.sin_addr.s_addr=htonl(INADDR_ANY);//服务器IP地址--允许连接到所有本地地址上
    my_addr.sin_port=htons(port); //UDP服务器端口号 /*创建服务器端套接字--IPv4协议，面向连接通信，TCP协议*/
    if((server_sockfd_udp=socket(AF_INET,SOCK_DGRAM,0))==INVALID_SOCKET)
    {
        perror("socket");    /*将套接字绑定到服务器的网络地址上*/
        return -1;
    }
    if (bind(server_sockfd_udp,(SOCKADDR*)&my_addr,sizeof(SOCKADDR))==SOCKET_ERROR)
    {
        perror("bind");
        return -1;
    }
    return 0;
}
