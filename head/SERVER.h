#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED
#include <stdio.h>
#include <WinSock2.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <direct.h>
#include <time.h>
#define BUFSIZ 512
///**************�����û��ڵ�****************
struct user
{
    SOCKET USER_socket;
    SOCKADDR_IN USER_socket_udp;
    //SOCKADDR_IN USER_ADDR;
    char USERID[12];
    char USERPASSWORD[33];
    //char DATE[513];
    char info[100];
    struct user *next;
};
typedef struct user * USER;
 struct contact
{
    char checkcode[18];
    char USERID[12];
    char USERPASSWORD[33];
    char TalktoID[12];
    char info[10];
}contact ;
typedef struct contact * Contact;
 struct message
{
    char checkcode[18];
    char USERID[12];
    char USERPASSWORD[33];
    char TalktoID[12];
    char data[513];
} ;
typedef struct message * Message;
struct OnlineUserHead
{
    char DATE[100];
    char TIME[18];
    char info[100];
    int OnlineUserNum;
    USER  next;
};
///*******************************************
struct OnlineUserHead * onlineUserHead;
struct OnlineUserHead * RegistedUserHead;
///*****************�ӿ�**********************
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
///********�����ӿ�*************
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
    char info[100];//[0]�Ƿ�ע����¼,N_Y;
} cln;
typedef struct
{
    cln a;
    char filename[32];
    char file_lx[8];
    char file_path[32];
} tcp_send_interface;

///*****************************
///*******��������**************
DWORD WINAPI talk(LPVOID);
DWORD WINAPI fun(LPVOID);
DWORD WINAPI Check_alive(LPVOID);
DWORD WINAPI UdpPackResolve(LPVOID);
DWORD WINAPI file_tcp_thread(LPVOID);
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
void RequestContact(cln*,FILE*);
void RequestMessage(cln*,FILE*);
void logwrite(char*);
int IoTtalk(char*,char*,cln*);
int Stringcut(char* str,int m,int n,char *des);
int BitmapSize(FILE*);
int bitmapfigure(cln*,FILE*,char*);
int UdpInit(int);
int file_tcp_send(cln*,FILE*,char*,char*);
///*****************************
///***************�����־��**********************
char CHECK[3];///Ӧ�ý���ʱ��½����Ƿ��Ѿ�ע��
char SIGN_IN[3];///��½��
char REGISTER[3];///ע����
char MESSAGE[3];///��Ϣ������
char TALK_TO[3];///ͨ��Ŀ���ַ��
char SIGN_OUT[3];///ע��
char CONTACT[3];///��ϵ����
char REPWD[3];
///************************************************
///**********ȫ�ֱ���****************
SOCKET server_sockfd;//TCP���������׽���
SOCKET server_sockfd_udp;//UDP���������׽���
HANDLE cln_thread[200];
int cln_num;
int warnfile;
int logflag;
FILE* REGISTERlocal;
FILE* loginfo;
char app_version[4];
///**********************************
#endif // SERVER_H_INCLUDED
