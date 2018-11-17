#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED
#include <stdio.h>
#include <WinSock2.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include<time.h>
#define BUFSIZ 512
///**************在线用户节点****************
struct user
{
    SOCKET USER_socket;
    SOCKADDR_IN USER_ADDR;
    char USERID[12];
    char USERPASSWORD[33];
    //char DATE[513];
    char info[100];
    struct user *next;
};
typedef struct user * USER;
struct OnlineUserHead
{
    char DATE[100];
    char TIME[18];
    char info[100];
    int OnlineUserNum;
    USER  next;
};
struct OnlineUserHead * onlineUserHead;
struct OnlineUserHead * RegistedUserHead;
///*****************接受**********************
typedef struct
{
    char checkcode[18];
    char USERID[12];
    char USERPASSWORD[33];
    char TalktoID[12];
    char REUSERPASSWORD[33];
    char DATA[513];
    char save[100];
} sendbag;
///********函数接口*************
typedef struct
{
    SOCKET remote_socket;
    SOCKADDR_IN ADDR;
    char USERID[12];
    char USERPASSWORD[33];
    char checkcode[18];
    char DATE[100];
    char TalktoID[12];
    char REUSERPASSWORD[33];
    char data[513];
    char info[100];
} cln;
///*****************************
///*******函数声明**************
DWORD WINAPI talk(LPVOID);
DWORD WINAPI fun(LPVOID );
int StartThread(cln* );
int AcceptClient();
int initServer();
int newOnlineUser(cln);
int delete_out_user(cln);
USER Print_onlineuser();
int SIGNIN(cln*);
int AddtoLocal(cln);
int Check_Id_Pwd(int,cln);
USER Print_onlineuser(int,char*);
int UpdateRegistedUser(USER);
int Register(cln*);
int DeleteFileUser(cln );
///*****************************
///***************各类标志码**********************
char CHECK[3];///应用进入时登陆检测是否已经注册
char SIGN_IN[3];///登陆码
char REGISTER[3];///注册码
char MESSAGE[3];///信息发送码
char TALK_TO[3];///通信目标地址码
char SIGN_OUT[3];///注销
char CONTACT[3];///联系人码
char REPWD[3];
///************************************************
///**********全局变量****************
SOCKET server_sockfd;//服务器端套接字
HANDLE cln_thread[200];
int cln_num;
FILE* REGISTERlocal;
///**********************************
#endif // SERVER_H_INCLUDED
