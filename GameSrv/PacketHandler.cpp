#include "PacketHandler.h"
#include "GameServer.h"
#include "Handler_FromAgentServer.h"
#include "Handler_FromDBServer.h"

PacketHandler g_PacketHandler;

PacketHandler::PacketHandler(void)
{
	m_pFuncMap_AG = new FunctionMap;
	m_pFuncMap_DG = new FunctionMap;
	RegisterHandler();
}

PacketHandler::~PacketHandler(void)
{
	SAFE_DELETE(m_pFuncMap_AG);
	SAFE_DELETE(m_pFuncMap_DG);
}

BOOL PacketHandler::RegisterHandler()
{
	Register_AG();
	Register_DG();
	return TRUE;
}

void PacketHandler::Register_AG()
{
	AddHandler_AG( Login_Protocol, Login_REQ, Handler_FromAgentServer::OnLogin_REQ );
	AddHandler_AG( Login_Protocol, Logout_REQ, Handler_FromAgentServer::OnLogout_REQ );

	AddHandler_AG( Games_Protocol, JoinWatch_REQ, Handler_FromAgentServer::OnJoinWatch_REQ );
	AddHandler_AG( Games_Protocol, QuitWatch_REQ, Handler_FromAgentServer::OnQuitWatch_REQ );
	AddHandler_AG( Games_Protocol, JoinTable_REQ, Handler_FromAgentServer::OnJoinTable_REQ );
	AddHandler_AG( Games_Protocol, QuitTable_REQ, Handler_FromAgentServer::OnQuitTable_REQ );
	AddHandler_AG( Games_Protocol, StartGame_REQ, Handler_FromAgentServer::OnStartGame_REQ );
	AddHandler_AG( Games_Protocol, ShowCards_REQ, Handler_FromAgentServer::OnShowCards_REQ );
	AddHandler_AG( Games_Protocol, Called_REQ,    Handler_FromAgentServer::OnCalled_REQ );
	AddHandler_AG( Games_Protocol, Discards_REQ,  Handler_FromAgentServer::OnDiscards_REQ );
}

void PacketHandler::Register_DG()
{
	AddHandler_DG( Login_Protocol, Login_ANC, Handler_FromDBServer::OnLogin_ANC );
	AddHandler_DG( Login_Protocol, Login_NAK, Handler_FromDBServer::OnLogin_NAK );
	AddHandler_DG( Login_Protocol, Logout_ANC, Handler_FromDBServer::OnLogout_ANC );
}

BOOL PacketHandler::AddHandler_AG( WORD category, WORD protocol, fnHandler fnHandler)
{
	FUNC_AG * pFuncInfo	= new FUNC_AG;
	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
	pFuncInfo->m_fnHandler		= fnHandler;
	return m_pFuncMap_AG->Add( pFuncInfo );
}

BOOL PacketHandler::AddHandler_DG( WORD category, WORD protocol, fnHandler fnHandler)
{
	FUNC_DG * pFuncInfo	= new FUNC_DG;
	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
	pFuncInfo->m_fnHandler		= fnHandler;
	return m_pFuncMap_DG->Add( pFuncInfo );
}

VOID PacketHandler::ParsePacket_AG( ServerSession * pSession, MSG_BASE * pMsg, WORD wSize )
{
	assert(NULL != pMsg);
	FUNC_AG * pFuncInfo = (FUNC_AG *)m_pFuncMap_AG->Find( MAKELONG( pMsg->m_byCategory, pMsg->m_byProtocol ) );
	pFuncInfo->m_fnHandler( pSession, pMsg, wSize );
}

VOID PacketHandler::ParsePacket_DG( ServerSession * pSession, MSG_BASE * pMsg, WORD wSize )
{
	assert(NULL != pMsg);
	FUNC_DG * pFuncInfo = (FUNC_DG *)m_pFuncMap_DG->Find( MAKELONG( pMsg->m_byCategory, pMsg->m_byProtocol ) );
	pFuncInfo->m_fnHandler( pSession, pMsg, wSize );
}

