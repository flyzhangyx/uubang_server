#include"../head/SERVER.h"
int AcceptClient()
{
    int sin_size;
    SOCKET clnt;
    SOCKADDR_IN a;
    sin_size=sizeof(struct sockaddr_in);
    while(1)
    {
        listen(server_sockfd,1);
        /*等待客户端连接请求到达*/
        if((clnt=accept(server_sockfd,(struct sockaddr *)&a,&sin_size))==-1)
        {
            perror("accept");
            return -1;
        }
        cln_num++;
        printf("\naccept num %d client %s\n",cln_num,inet_ntoa(a.sin_addr));
        if(cln_num<200)
        {
            cln b;
            b.remote_socket=clnt;
            b.ADDR=a;
            StartThread(&b);

           //Print_onlineuser(1,NULL);
        }

        else
        {
        printf("在线用户已满！");

        }///
    }
    return 1;
}
