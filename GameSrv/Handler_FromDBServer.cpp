#include "Handler_FromDBServer.h"
#include "GameServer.h"
#include "CommStruct.h"

Handler_FromDBServer::Handler_FromDBServer()
{

}

Handler_FromDBServer::~Handler_FromDBServer()
{

}

HANDLER_IMPL( Login_ANC )
{
    //MSG_LOGIN_ANC
	printf(">>> Login_ANC.\n");
#if 0
	MSG_GD_LOGIN_ANC * pRecvMsg = (MSG_GD_LOGIN_ANC *)pMsg;
	DWORD dwUserID = pRecvMsg->m_dwParameter;
	printf("UserID = %d\n", dwUserID);

	// 分配 GameUser 用户
	GameUser * pUser = GameFactory::Instance()->AllocGameUser();
	if ( pUser == NULL ) {
		printf("GameFactory::Instance()->AllocGameUser() fail\n");
		return;
	}
	pUser->SetHashKey( dwUserID );
	printf("[GameFactory::Instance()->AllocGameUser()] Success.\n");

	// GameUserManager 添加记录
	BOOL bRet = g_GameUserManager.AddUser( pUser );
	if ( !bRet ) {
		printf("[g_GameUserManager.AddUser()] Fail.\n");
		return;
	}
	printf("[g_GameUserManager.AddUser] Success.\n");

	// 返回消息给 AgentSrv
	MSG_AG_LOGIN_ANC msg2;
	msg2.m_dwParameter 					= pRecvMsg->m_dwParameter; // UserID
	msg2.m_playerInfo.m_dwUserID 		= dwUserID;
	msg2.m_playerInfo.m_uiDBUserID 		= pRecvMsg->m_uiRootID;
	msg2.m_playerInfo.m_uiFaileds 		= pRecvMsg->m_uiFaileds;
	msg2.m_playerInfo.m_uiWons 			= pRecvMsg->m_uiWons;
	msg2.m_playerInfo.m_uiEscape 		= pRecvMsg->m_uiEscape;
	msg2.m_playerInfo.m_uiScore 		= pRecvMsg->m_uiScore;

	// 保存GamePlayer 信息
	pUser->SetPlayerInfo(msg2.m_playerInfo);

	g_GameServer->SendToAgentServer( (BYTE *)&msg2, sizeof(msg2) );
#endif
}

HANDLER_IMPL( Login_NAK )
{
	printf("Login_NAK.\n");

}

HANDLER_IMPL( Logout_ANC )
{
	printf(">>> Logout_ANC\n");
#if 0
	MSG_GD_LOGOUT_ANC * pRecvMsg = (MSG_GD_LOGOUT_ANC *)pMsg;
	DWORD dwUserID = pRecvMsg->m_dwParameter;
	printf("UserID = %d\n", dwUserID);

	// GameUserManager 清楚记录
	GameUser * pUser = g_GameUserManager.Find( pRecvMsg->m_dwParameter );
	if ( pUser == NULL ) {
		printf("g_GameUserManager.Find(%d) Fail\n", pRecvMsg->m_dwParameter);
		return;
	}

	// 释放 GameUser 资源
	GameFactory::Instance()->FreeGameUser( pUser );

	// GameUserManager 清除记录
	BOOL bRet = g_GameUserManager.Remove( dwUserID );
	if ( !bRet ) {
		printf("[g_GameUserManager.Remove()]: UserID (%d) Fail.\n", dwUserID);
		return;
	}

	// 返回信息给 AgentSrv
	MSG_AG_LOGOUT_ANC msg2;
	msg2.m_dwParameter = dwUserID;
	msg2.m_uiRootID = pRecvMsg->m_uiRootID;
	g_GameServer->SendToAgentServer( (BYTE *)&msg2, sizeof(msg2) );
#endif
}
