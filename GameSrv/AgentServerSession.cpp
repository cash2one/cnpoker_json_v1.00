#include "AgentServerSession.h"

#include "PacketHandler.h"

AgentServerSession::AgentServerSession()
{	
}

AgentServerSession::~AgentServerSession()
{
}

void AgentServerSession::Init()
{
	ServerSession::Init();
}

void AgentServerSession::Release()
{
	ServerSession::Release();
}

void AgentServerSession::Update()
{
	ServerSession::Update();
}

void AgentServerSession::OnRecv(BYTE *pMsg, WORD wSize)
{
	printf("[AgentServerSession::OnRecv]\n");
	printf("call g_PacketHandler.ParsePacket_AG function.\n");
	g_PacketHandler.ParsePacket_AG( this, (MSG_BASE *)pMsg, wSize);
}

void AgentServerSession::OnDisconnect()
{
	ServerSession::OnDisconnect();
}
	
void AgentServerSession::OnConnect( BOOL bSuccess, DWORD dwNetworkIndex )
{
	printf("[GameServer] : AgentServerSession::OnConnect\n");
	ServerSession::OnConnect( bSuccess, dwNetworkIndex );
	if ( bSuccess ) {
		printf("[AgentServerSession::OnConnect] success.\n");
		printf("Send Server Type.\n");
		ServerSession::SendServerType();
	}
	else
		printf("[GameServer] : AgentServerSession::OnConnect fail\n");
}

void AgentServerSession::OnLogString( char * pszLog)
{
	
}