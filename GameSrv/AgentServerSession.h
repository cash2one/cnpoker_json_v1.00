#ifndef _AGENTSERVERSESSION_H_INCLUDED_
#define _AGENTSERVERSESSION_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include <Network.h>
#include "ServerSession.h"

class AgentServerSession : public ServerSession
{
public:
	AgentServerSession();
	virtual ~AgentServerSession();

	eSERVER_TYPE    GetServerType() { return GAME_SERVER; }

	virtual void    Init();
	virtual void    Release();
	virtual void    Update();

public:
    virtual void    OnConnect( BOOL bSuccess, DWORD dwSessionIndex );
	virtual void	OnDisconnect( );
	virtual void	OnRecv( BYTE *pMsg, WORD wSize );
	virtual void	OnLogString( char * pszLog );
};

#endif // _AGENTSERVERSESSION_H_INCLUDED_
