#ifndef _HANDLER_FROMDBSERVER_H_INCLUDED_
#define _HANDLER_FROMDBSERVER_H_INCLUDED_

#include <Common.h>

#include "ServerSession.h"

#define HANDLER_DECL( p )			static VOID On##p( ServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
#define HANDLER_IMPL( p )			VOID Handler_FromDBServer::On##p( ServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )

class Handler_FromDBServer
{
public:
	Handler_FromDBServer(void);
	~Handler_FromDBServer(void);

	HANDLER_DECL( Login_ANC );
	HANDLER_DECL( Login_NAK );
	
	HANDLER_DECL( Logout_ANC );
};


#endif

