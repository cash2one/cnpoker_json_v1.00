#ifndef _GAMESERVER_H_INCLUDED_
#define _GAMESERVER_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include <Network.h>
#include "GameFactory.h"

using namespace std;

class GameServer
{
	enum { CLIENT_SYNCHANDLER = 0, SERVER_SYNCHANDLER = 1, };
	
public:
	GameServer(void);
	~GameServer(void);

	BOOL Init();
	
	BOOL ConnectToServer( ServerSession * pSession, char * pszIP, WORD wPort );
	
	//void StartListen();
	
	BOOL MaintainConnection();
	
	BOOL Update( DWORD dwDeltaTick );
	
	BOOL SendToDBServer( BYTE * pMsg, WORD wSize);
	BOOL SendToAgentServer( BYTE * pMsg, WORD wSize);
	
private:
	BOOL m_bShutdown;
	
	IOCPServer * m_pIOCPServer;
	
	//
	ServerSession * m_pDBServerSession;
	ServerSession * m_pAgentServerSession;
	
};

extern GameServer * g_GameServer;

#endif // _GAMESERVER_H_INCLUDED_
