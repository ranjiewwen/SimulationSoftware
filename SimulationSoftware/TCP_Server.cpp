#include "stdafx.h"
#include "TCP_Server.h"


TCP_Server::TCP_Server(USHORT port, ULONG ip)
{
	//�����׽��ֶ��󣬲���Ϊ������ģʽ
	ULONG ul = 1;
	sListen = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //TCP
	if (sListen == INVALID_SOCKET)
	{
		printf("socket����ʧ�ܣ�....");
	}
	::ioctlsocket(sListen, FIONBIO, (ULONG*)&ul);//��Ϊ������ģʽ

	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.S_un.S_addr = ip;//INADDR_ANY

	if (::bind(sListen, (sockaddr*)&sin, sizeof(sin)) == SOCKET_ERROR)  //ϸ��
	{
		printf(" Failed bind() \n");
		return;
	}
	// �������ģʽ
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
	//if (nRet == 0)//��ʱ
	//{
	//	//qDebug() << ("overtime...\n");		 
	//}
	//if (nRet > 0)
	//{
	//	for (int i = 0; i < (int)fdSocket.fd_count; i++)
	//	{
	//		if (FD_ISSET(fdSocket.fd_array[i], &fdRead))
	//		{
	//			if (fdSocket.fd_array[i] == sListen)		// ��1�������׽��ֽ��յ�������
	//			{
	//				if (fdSocket.fd_count < FD_SETSIZE)
	//				{
	//					sNew = ::accept(sListen, (SOCKADDR*)&addrRemote, &nAddrLen);   //���ڽ��յ���������
	//					FD_SET(sNew, &fdSocket);
	//					printf("���յ����ӣ�%s��\n", ::inet_ntoa(addrRemote.sin_addr));
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
	//				if (nRecv > 0)						// ��2���ɶ�
	//				{
	//					szText[nRecv] = '\0';
	//					printf("���յ����ݣ�%s \n", szText);
	//				}
	//				else								// ��3�����ӹرա����������ж�
	//				{
	//					::closesocket(fdSocket.fd_array[i]);
	//					printf("���ӹر�....");
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
	if (nRet == 0)//��ʱ
	{
		//qDebug() << ("overtime...\n");		 
	}
	if (nRet > 0)
	{
		sNew = ::accept(sListen, (SOCKADDR*)&addrRemote, &nAddrLen);   //���ڽ��յ���������
		//FD_SET(sNew, &fdSocket);
		printf("���յ����ӣ�%s��\n", ::inet_ntoa(addrRemote.sin_addr));
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
		printf("���մ���...");
	}
	if (nRecv > 0)						// ��2���ɶ�
	{
		szText[nRecv] = '\0';
		printf("���յ����ݣ�%s \n", szText);
	}
	else								// ��3�����ӹرա����������ж�
	{
		::closesocket(sListen);
		printf("���ӹر�....");
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