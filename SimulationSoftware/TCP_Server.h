#pragma once

#include "CInitSock.h"

class TCP_Server
{
protected:
	CInitSock c;
	SOCKET sListen;
	sockaddr_in sin;
	fd_set fdSocket;  // 所有可用套节字集合
	sockaddr_in addrRemote;
	SOCKET sNew;
public:
	TCP_Server(USHORT port = 1234, ULONG ip = INADDR_ANY);
	~TCP_Server();
public:
	 SOCKET process();
	 bool clientIsClose();
	 void Close();
	 int SocketConnected(int sock);
};

