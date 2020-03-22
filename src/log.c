#include"../head/SERVER.h"
void logwrite(char* log)
{
    char *timenow;
    time_t t;//定义一个时间变量
    t=time(NULL);
    timenow=ctime(&t);
    while(logflag)
    {
        Sleep(1000);
    }
    logflag=1;
    fputs("\n",loginfo);
    fputs(timenow,loginfo);
    fputs(log,loginfo);
    fflush(loginfo);
    logflag=0;
}
