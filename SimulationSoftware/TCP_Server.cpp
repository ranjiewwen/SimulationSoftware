#include "stdafx.h"
#include "TCP_Server.h"


TCP_Server::TCP_Server(USHORT port, ULONG ip)
{
	//创建套接字对象，并设为非阻塞模式
	ULONG ul = 1;
	sListen = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //TCP
	if (sListen == INVALID_SOCKET)
	{
		printf("socket创建失败！....");
	}
	::ioctlsocket(sListen, FIONBIO, (ULONG*)&ul);//设为非阻塞模式

	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.S_un.S_addr = ip;//INADDR_ANY

	if (::bind(sListen, (sockaddr*)&sin, sizeof(sin)) == SOCKET_ERROR)  //细心
	{
		printf(" Failed bind() \n");
		return;
	}
	// 进入监听模式
	if (::listen(sListen, 5) == SOCKET_ERROR)
	{
		printf("failed listen()\n");
		return;
	}
}

SOCKET TCP_Server::process()
{
	FD_ZERO(&fdSocket);
	FD_SET(sListen, &fdSocket);
	int nAddrLen = sizeof(addrRemote);

	//fd_set fdRead = fdSocket;
	//int nRet = ::select(0, &fdRead, NULL, NULL, NULL);
	//if (nRet == SOCKET_ERROR)
	//{
	//	//printf("failed select()...\n");		   
	//}
	//if (nRet == 0)//超时
	//{
	//	//qDebug() << ("overtime...\n");		 
	//}
	//if (nRet > 0)
	//{
	//	for (int i = 0; i < (int)fdSocket.fd_count; i++)
	//	{
	//		if (FD_ISSET(fdSocket.fd_array[i], &fdRead))
	//		{
	//			if (fdSocket.fd_array[i] == sListen)		// （1）监听套节字接收到新连接
	//			{
	//				if (fdSocket.fd_count < FD_SETSIZE)
	//				{
	//					sNew = ::accept(sListen, (SOCKADDR*)&addrRemote, &nAddrLen);   //用于接收到来的链接
	//					FD_SET(sNew, &fdSocket);
	//					printf("接收到连接（%s）\n", ::inet_ntoa(addrRemote.sin_addr));
	//					return sNew;
	//				}
	//				else
	//				{
	//					printf(" Too much connections! \n");
	//					continue;
	//				}
	//			}
	//			else
	//			{
	//				char szText[256];
	//				int nRecv = ::recv(fdSocket.fd_array[i], szText, strlen(szText), 0);
	//				if (nRecv > 0)						// （2）可读
	//				{
	//					szText[nRecv] = '\0';
	//					printf("接收到数据：%s \n", szText);
	//				}
	//				else								// （3）连接关闭、重启或者中断
	//				{
	//					::closesocket(fdSocket.fd_array[i]);
	//					printf("链接关闭....");
	//					FD_CLR(fdSocket.fd_array[i], &fdSocket);
	//					return INVALID_SOCKET;
	//				}
	//			}
	//		}
	//	}
	//}
	//else
	//{
	//	printf(" Failed select() \n");
	//	return INVALID_SOCKET;
	//}

	//fd_set fdRead = fdSocket;
	int nRet = ::select(sListen + 1, &fdSocket, NULL, NULL, NULL);
	if (nRet == SOCKET_ERROR)
	{
		//printf("failed select()...\n");		   
	}
	if (nRet == 0)//超时
	{
		//qDebug() << ("overtime...\n");		 
	}
	if (nRet > 0)
	{
		sNew = ::accept(sListen, (SOCKADDR*)&addrRemote, &nAddrLen);   //用于接收到来的链接
		//FD_SET(sNew, &fdSocket);
		printf("接收到连接（%s）\n", ::inet_ntoa(addrRemote.sin_addr));
		return sNew;
	}
	else
	{
		printf(" Failed select() \n");
		return INVALID_SOCKET;
	}
}

bool TCP_Server::clientIsClose()
{
	char szText[256];
	int nRecv = ::recv(sListen, szText, strlen(szText), 0);
	if (nRecv==SOCKET_ERROR)
	{
		printf("接收错误...");
	}
	if (nRecv > 0)						// （2）可读
	{
		szText[nRecv] = '\0';
		printf("接收到数据：%s \n", szText);
	}
	else								// （3）连接关闭、重启或者中断
	{
		::closesocket(sListen);
		printf("链接关闭....");
		FD_CLR(sListen, &fdSocket);
		return true;
	}

}


TCP_Server::~TCP_Server()
{
	Close();
}

void TCP_Server::Close() {
	if (sListen != INVALID_SOCKET) {
		closesocket(sListen);
		sListen = INVALID_SOCKET;
	}
}

int TCP_Server::SocketConnected(int sock)
{
	return 0;
}