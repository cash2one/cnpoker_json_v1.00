#ifndef _PACKET_HANDLER_H_INCLUDED_
#define _PACKET_HANDLER_H_INCLUDED_

#include <Common.h>
#include <Network.h>
#include <Utility.h>
#include "ServerSession.h"
using namespace A;

typedef VOID (*fnHandler)( ServerSession * pSession, MSG_BASE * pMsg, WORD wSize );

class PacketHandler
{
public:
	PacketHandler(void);
	~PacketHandler(void);

public:
	BOOL RegisterHandler();
	void Register_AG();
	void Register_DG();
	
	BOOL AddHandler_AG( WORD category, WORD protocol, fnHandler fnHandler);
	BOOL AddHandler_DG( WORD category, WORD protocol, fnHandler fnHandler);

	void ParsePacket_AG( ServerSession * pSession, MSG_BASE * pMsg, WORD wSize );
	void ParsePacket_DG( ServerSession * pSession, MSG_BASE * pMsg, WORD wSize );

private:
	struct FUNC_AG : public BASE_FUNC
	{
		fnHandler	m_fnHandler;
	};

	struct FUNC_DG : public BASE_FUNC
	{
		fnHandler	m_fnHandler;
	};

	FunctionMap	*	m_pFuncMap_AG;
	FunctionMap	*	m_pFuncMap_DG;
};

extern PacketHandler g_PacketHandler;

#endif
