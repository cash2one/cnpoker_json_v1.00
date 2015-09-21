#include "DBServerSession.h"

#include "PacketHandler.h"

DBServerSession::DBServerSession()
{

}

DBServerSession::~DBServerSession()
{
	
}

void DBServerSession::Init()
{
	ServerSession::Init();
}

void DBServerSession::Release()
{
	ServerSession::Release();
}

void DBServerSession::Update()
{
	ServerSession::Update();
}

void DBServerSession::OnRecv(BYTE *pMsg, WORD wSize)
{
	printf("[DBServerSession::OnRecv]\n");
	printf("call g_PacketHandler.ParsePacket_GD function.\n");
	g_PacketHandler.ParsePacket_DG( this, (MSG_BASE *)pMsg, wSize );
}

void DBServerSession::OnDisconnect()
{
	ServerSession::OnDisconnect();
}
	
void DBServerSession::OnConnect( BOOL bSuccess, DWORD dwNetworkIndex )
{
	printf("[GameServer] : DBServerSession::OnConnect\n");
	ServerSession::OnConnect( bSuccess, dwNetworkIndex );
	if ( bSuccess ) {
		printf("[DBServerSession::OnConnect] success.\n");
		printf("Send Server Type.\n");		
		ServerSession::SendServerType();
	}
	else
		printf("[GameServer] : DBServerSession::OnConnect fail\n");
}

void DBServerSession::OnLogString( char * pszLog)
{
	
}
