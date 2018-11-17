#include"../head/SERVER.h"
int main()
{
    initServer();
    printf("服务器初始化成功！");
    AcceptClient();
    return 0;
}
