#include "GameServer.h"

#include "InfoParser.h"
//#include "GameFactory.h"

NetworkObject * CreateServerSideAcceptedObject();
VOID DestroyServerSideAcceptedObject( NetworkObject *pNetworkObject );
VOID DestroyServerSideConnectedObject( NetworkObject *pNetworkObject );

GameServer * g_GameServer = NULL;

GameServer::GameServer(void)
{
	m_bShutdown = FALSE;
	m_pIOCPServer = NULL;
	
	m_pDBServerSession = NULL;
	m_pAgentServerSession = NULL;
}

GameServer::~GameServer(void)
{
	if ( m_pIOCPServer )
		delete m_pIOCPServer;
}

BOOL GameServer::Init()
{
	GameFactory::Instance()->Init(); // Factory <GameUser>
	BOOL bRet = g_InfoParser.Init("./ServerInfo.ini");
	if ( !bRet ) {
		printf("Parse Server Info fail\n");
		return FALSE;
	}
	
	m_pIOCPServer = new IOCPServer;
	
	SYNCHANDLER_DESC desc;
	
	desc.dwSyncHandlerKey				= SERVER_SYNCHANDLER;
	desc.dwMaxAcceptSession				= 0;
	desc.dwMaxConnectSession			= 5;
	desc.dwSendBufferSize				= 2000000;
	desc.dwRecvBufferSize		 		= 2000000;
	desc.dwTimeOut						= 0;
	desc.dwNumberOfAcceptThreads		= 1; // 0
	desc.dwNumberOfIoThreads			= 8; // 开辟8个线程
	desc.dwNumberOfConnectThreads		= 1;
	desc.dwMaxPacketSize				= 60000; // 4096
	desc.fnCreateAcceptedObject			= CreateServerSideAcceptedObject;
	desc.fnDestroyAcceptedObject		= DestroyServerSideAcceptedObject;
	desc.fnDestroyConnectedObject		= DestroyServerSideConnectedObject;
	
	if ( !m_pIOCPServer->Init(&desc, 1) ) {
		return FALSE;
	}
	
	// 主动连接 Agent
	m_pAgentServerSession = GameFactory::Instance()->AllocAgentServerSession();
	if ( m_pAgentServerSession ) {
		SERVER_INFO info = g_InfoParser.GetServerInfo( AGENT_SERVER );
		m_pAgentServerSession->SetAddr( info.m_strIp, info.m_dwPort ); // Agent Port 8100
	}
	
	// 主动连接 DB
	m_pDBServerSession = GameFactory::Instance()->AllocDBServerSession();
	if ( m_pDBServerSession ) {
		SERVER_INFO info = g_InfoParser.GetServerInfo( DB_SERVER );
		m_pDBServerSession->SetAddr( info.m_strIp, info.m_dwPort ); // DB Port 7030
	}
	
	return TRUE;
}

BOOL GameServer::ConnectToServer( ServerSession * pSession, char * pszIP, WORD wPort )
{
	if (pSession == NULL) {
		return FALSE;
	}
	printf("IP = %s, Port = %d\n", pszIP, wPort);
	
	return m_pIOCPServer->Connect( SERVER_SYNCHANDLER, (NetworkObject *)pSession, pszIP, wPort );
	//return m_pIOCPServer->Connect( SERVER_SYNCHANDLER, (NetworkObject *)pSession, "127.0.0.1", 7000 );
}

#if 0
void GameServer::StartListen()
{
	if( !m_pIOCPServer->IsListening( SERVER_SYNCHANDLER) ) {
		if ( !m_pIOCPServer->StartListen(SERVER_SYNCHANDLER, "127.0.0.1", 7100) ) 
		{
			return;
		}
	}
}
#endif

BOOL GameServer::MaintainConnection()
{
	if (m_bShutdown) {
		return FALSE;
	}
	
	if ( m_pAgentServerSession ) {
		if ( m_pAgentServerSession->TryToConnect() ) {
			ConnectToServer( m_pAgentServerSession, (char *)m_pAgentServerSession->GetConnnectIP().c_str(), m_pAgentServerSession->GetConnnectPort() );
		}
	}
	
	if ( m_pDBServerSession ) {
		if ( m_pDBServerSession->TryToConnect() ) {
			ConnectToServer( m_pDBServerSession, (char *)m_pDBServerSession->GetConnnectIP().c_str(), m_pDBServerSession->GetConnnectPort() );
		}
	}
}

BOOL GameServer::Update( DWORD dwDeltaTick )
{
	if ( m_pIOCPServer ) {
		m_pIOCPServer->Update();
	}
	
	// Connect other Servers
	MaintainConnection();
	
	return TRUE;
}

BOOL GameServer::SendToDBServer( BYTE * pMsg, WORD wSize)
{
	printf("[GameServer::SendToDBServer]\n");
	
	if ( m_pDBServerSession ) {
		return m_pDBServerSession->Send( pMsg, wSize );
	}
	return FALSE;
}

BOOL GameServer::SendToAgentServer( BYTE * pMsg, WORD wSize)
{
	printf("[GameServer::SendToAgentServer]\n");
	
	if ( m_pAgentServerSession ) {
		return m_pAgentServerSession->Send( pMsg, wSize );
	}
	return FALSE;
}

//////////////////////////////////////////////////////

NetworkObject * CreateServerSideAcceptedObject() {
	printf("GameServer::CreateServerSideAcceptedObject \n");
	//ServerSession * obj = GameFactory::Instance()->AllocGameUser();
	//return obj;
}

VOID DestroyServerSideAcceptedObject( NetworkObject *pNetworkObject ) {
	printf("GameServer::DestroyServerSideAcceptedObject \n");
	//AgentFactory::Instance()->FreeUserSession(pNetworkObject);
}

VOID DestroyServerSideConnectedObject( NetworkObject *pNetworkObject ) {
	printf("GameServer::DestroyServerSideConnectedObject\n");
}

