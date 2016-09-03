#include "stdafx.h"
#include<winsock2.h>
#include<stdlib.h>
#include<fstream.h>
//
#define DEFAULT_PORT 4040
#define DEFAULT_IP "172.18.157.121"
#define MAX_LEN_BUFFER 50
//#define DEFAULT_ADDR "172.18.157.121"
//
class netTran{
public:
	void error(char *str){
		MessageBox(NULL,str,"error",0);
	} 
	int errorLevel;
	netTran(){
		bClient=false;
		bServer=false;
		//server:
		WSADATA wsd;
		if(WSAStartup(MAKEWORD(2,2),&wsd)!=0){
			error("Failed to load WinSock!\n");
			errorLevel= 1;return ;
		}
		listenSock=socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
		if(listenSock==SOCKET_ERROR){
			error("socket() failed! can't create listenSock.");
			errorLevel= 1;return ;
		}
		//
		
		//client:
		mySock=socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
		if(mySock==SOCKET_ERROR){
			error("socket() failed! can't create mySock.");
			errorLevel= 1;return ;
		}
		bReady=false;
	}
	~netTran(){
		closesocket(listenSock);
		closesocket(mySock);
		WSACleanup();
	}
	bool connectTo(char *ip,int port=0){
		bServer=false;
		bClient=true;
		//
		char serverIP[50];
		strcpy(serverIP,ip);
		if(strlen(serverIP)<7){strcpy(serverIP,DEFAULT_IP);}
		if(port==0)port=DEFAULT_PORT;
		sockaddr_in serverAddr;
		serverAddr.sin_port=htons(port);
		serverAddr.sin_addr.s_addr=inet_addr(serverIP);
		serverAddr.sin_family=AF_INET;
		bool bconnect=connect(mySock,(sockaddr *)&serverAddr,sizeof(serverAddr))!=SOCKET_ERROR;
		if(!bconnect){
			error("Connect failed!");errorLevel=1;return false;
		}
		bReady=true;
		return true;
	}
	bool wait(){
		bServer=true;
		bClient=false;
		//
		sockaddr_in localAddr;
		localAddr.sin_family=AF_INET;
		localAddr.sin_port=htons(DEFAULT_PORT);
		localAddr.sin_addr.s_addr=htonl(INADDR_ANY);
		if(bind(listenSock,(struct sockaddr *)&localAddr,sizeof(localAddr))==-1){
			error("bind() failed:");
			errorLevel=1;return false;
		}
		listen(listenSock,2);
		sockaddr_in clientAddr;
		int lenClientAddr=sizeof(clientAddr);
		mySock=accept(listenSock,(struct sockaddr *)&clientAddr,&lenClientAddr);
		if(mySock==INVALID_SOCKET){
			error("accept() failed:");errorLevel=1;
			return false;
		}
		errorLevel=0;
		bReady=true;
		return true;
	}
	bool sendMess(char *str){
		if(bReady){
			if(mySock==-1) error("fail");
			send(mySock,str,strlen(str),0);
		}
		return bReady;
	}
	bool recvMess(char *str,int maxlen){
		if(bReady){
			if(mySock==-1) error("fail");
			recv(mySock,str,maxlen,0);
		}
		return bReady;
	}
public:
	char buffer[MAX_LEN_BUFFER+1];
	bool bClient;
	bool bServer;
	bool bReady;
	SOCKET listenSock,mySock;//mySock:for client , listenand client for server
private:
	
};
/*
struct ClientInfo{
SOCKET socket;
char ip[20];
int id;
char nume[100];
};
unsigned long WINAPI recvServer(LPVOID lParam){
ClientInfo *clientInfo=(ClientInfo *)lParam;
SOCKET clientSock=clientInfo->socket;
int lenRec;
char buffer[DEFAULT_BUFFER+1];
while(1){
lenRec=recv(clientSock,buffer,DEFAULT_BUFFER,0);//×èÈû.
if(lenRec==0) break;
else if(lenRec==SOCKET_ERROR){
cout<<"recv() fialed:"<<WSAGetLastError()<<endl;
break;
}else if(lenRec>0){
buffer[lenRec]='\0';
cout<<"\nFrom server :"<<buffer<<endl;
Beep(5000,175);
}else{
cout<<"Error:in recv():lenRec <-1"<<endl;
break;
}
}
return 0;
}
int main(){
ClientInfo clientInfo;
clientInfo.socket=mySock;
DWORD dwThread;
HANDLE hThread=	CreateThread(NULL,0,recvServer,(LPVOID)&clientInfo,0,&dwThread);
CloseHandle(hThread);
while(1){
cout<<"Please input anything:";

  }
  //	CloseHandle(hThread);
  return 0;
  }
  */