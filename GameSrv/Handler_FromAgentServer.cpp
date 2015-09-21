#include "Handler_FromAgentServer.h"
#include "GameServer.h"
#include "GameRoom.h"
#include "GameUser.h"

Handler_FromAgentServer::Handler_FromAgentServer()
{
}

Handler_FromAgentServer::~Handler_FromAgentServer()
{
}

HANDLER_IMPL( Login_REQ )
{
	printf("Login_REQ\n");

	MSG_BASE_FORWARD * recvMsg = (MSG_BASE_FORWARD *)pMsg;
	printf(">>> User Port = %d\n", recvMsg->m_wUserPort );

	char json_msgs[1024] = {0};
	memcpy(json_msgs, ((BYTE*)pMsg)+sizeof( recvMsg ), wSize-sizeof(recvMsg) );

	GameUser * pUser = g_pGameRoom.AllocUser( recvMsg->m_wUserPort );
    if ( pUser == NULL ) {
        return;
    }

    if ( pUser->Parser_Login( json_msgs, wSize-sizeof(recvMsg)) )
    {
        MSG_LOGIN_REQ sendDB;
        pUser->Makeup_Login(&sendDB);
        g_GameServer->SendToDBServer( (BYTE*)&sendDB, sizeof( sendDB ) );
    }
}

HANDLER_IMPL( Logout_REQ )
{
    // 直接发送给DB;
	printf("Logout_REQ\n");
	// g_GameServer->SendToDBServer( (BYTE*) pMsg, wSize );
}

HANDLER_IMPL( JoinWatch_REQ )
{
	printf("[JoinWatch_REQ]\n");

	MSG_BASE_FORWARD * recvMsg = (MSG_BASE_FORWARD *)pMsg;
	printf(">>> User Port = %d\n", recvMsg->m_wUserPort );

	char json_msgs[1024] = {0};
	memcpy(json_msgs, ((BYTE*)pMsg)+sizeof(recvMsg), wSize-sizeof(recvMsg) );

	GameUser * pUser = g_pGameRoom.FindUser(recvMsg->m_wUserPort);
    if ( pUser == NULL ) {
        return;
    }

    if ( pUser->Parser_JoinWatch(json_msgs, wSize-sizeof(recvMsg)) ) {
        pUser->JoinWatch();
        int wLen = pUser->Makeup_JoinWatch( json_msgs, sizeof(json_msgs) );
        pUser->SendToTable( json_msgs,  wLen);
    }
}

HANDLER_IMPL( QuitWatch_REQ )
{
    printf("[QuitWatch_REQ]\n");

	MSG_BASE_FORWARD * recvMsg = (MSG_BASE_FORWARD *)pMsg;
	printf(">>> User Port = %d\n", recvMsg->m_wUserPort );

	char json_msgs[1024] = {0};
	memcpy(json_msgs, (( BYTE*)pMsg)+sizeof( recvMsg ), wSize-sizeof(recvMsg) );

	GameUser * pUser = g_pGameRoom.FindUser( recvMsg->m_wUserPort );
    if ( pUser == NULL ) {
        return;
    }

    if ( pUser->Parser_QuitWatch( json_msgs, wSize-sizeof(recvMsg)) ) {
        pUser->QuitWatch();
        int wLen = pUser->Makeup_QuitWatch( json_msgs, sizeof(json_msgs) );
        pUser->SendToTable( json_msgs,  wLen);
    }
}

HANDLER_IMPL( JoinTable_REQ )
{
    printf("[JoinTable_REQ]\n");

	MSG_BASE_FORWARD * recvMsg = (MSG_BASE_FORWARD *)pMsg;
	printf(">>> User Port = %d\n", recvMsg->m_wUserPort );

	char json_msgs[1024] = {0};
	memcpy(json_msgs, (( BYTE*)pMsg)+sizeof( recvMsg ), wSize-sizeof(recvMsg) );

	GameUser * pUser = g_pGameRoom.FindUser( recvMsg->m_wUserPort );
    if ( pUser == NULL ) {
        return;
    }

    if ( pUser->Parser_JoinTable( json_msgs, wSize-sizeof(recvMsg)) ) {
        pUser->JoinTable();
        int wLen = pUser->Makeup_JoinTable( json_msgs, sizeof(json_msgs) );
        pUser->SendToTable( json_msgs,  wLen);
    }
}

HANDLER_IMPL( QuitTable_REQ )
{
    printf("[QuitTable_REQ]\n");

	MSG_BASE_FORWARD * recvMsg = (MSG_BASE_FORWARD *)pMsg;
	printf(">>> User Port = %d\n", recvMsg->m_wUserPort );

	char json_msgs[1024] = {0};
	memcpy(json_msgs, (( BYTE*)pMsg)+sizeof( recvMsg ), wSize-sizeof(recvMsg) );

	GameUser * pUser = g_pGameRoom.FindUser( recvMsg->m_wUserPort );
    if ( pUser == NULL ) {
        return;
    }

    if ( pUser->Parser_QuitTable( json_msgs, wSize-sizeof(recvMsg)) ) {
        pUser->LeaveTable();
        int wLen = pUser->Makeup_QuitTable( json_msgs, sizeof(json_msgs) );
        pUser->SendToTable( json_msgs,  wLen);
    }
}

// 叫地主
HANDLER_IMPL( StartGame_REQ )
{
    printf("[StartGame_REQ]\n");

	MSG_BASE_FORWARD * recvMsg = (MSG_BASE_FORWARD *)pMsg;
	printf(">>> User Port = %d\n", recvMsg->m_wUserPort );

	char json_msgs[1024] = {0};
	memcpy(json_msgs, (( BYTE*)pMsg)+sizeof( recvMsg ), wSize-sizeof(recvMsg) );

	GameUser * pUser = g_pGameRoom.FindUser( recvMsg->m_wUserPort );
    if ( pUser == NULL ) {
        return;
    }

    if ( pUser->Parser_StartGame( json_msgs, wSize-sizeof(recvMsg)) ) {
        pUser->Ready();
        int wLen = pUser->Makeup_StartGame( json_msgs, sizeof(json_msgs) );
        pUser->SendToTable( json_msgs,  wLen);
    }
}

// 叫地主
HANDLER_IMPL( Called_REQ )
{
    printf("[Called_REQ]\n");

	MSG_BASE_FORWARD * recvMsg = (MSG_BASE_FORWARD *)pMsg;
	printf(">>> User Port = %d\n", recvMsg->m_wUserPort );

	char json_msgs[1024] = {0};
	memcpy(json_msgs, (( BYTE*)pMsg)+sizeof( recvMsg ), wSize-sizeof(recvMsg) );

	GameUser * pUser = g_pGameRoom.FindUser( recvMsg->m_wUserPort );
    if ( pUser == NULL ) {
        return;
    }

    if ( pUser->Parser_Called( json_msgs, wSize-sizeof(recvMsg)) ) {
        pUser->Called();
        int wLen = pUser->Makeup_Called( json_msgs, sizeof(json_msgs) );
        pUser->SendToTable( json_msgs,  wLen);
    }
}

HANDLER_IMPL( ShowCards_REQ )
{
	printf("[ShowCards_REQ]\n");

	MSG_BASE_FORWARD * recvMsg = (MSG_BASE_FORWARD *)pMsg;
	printf(">>> User Port = %d\n", recvMsg->m_wUserPort );

	char json_msgs[1024] = {0};
	memcpy(json_msgs, (( BYTE*)pMsg)+sizeof( recvMsg ), wSize-sizeof(recvMsg) );

	GameUser * pUser = g_pGameRoom.FindUser( recvMsg->m_wUserPort );
    if ( pUser == NULL ) {
        return;
    }

    if ( pUser->Parser_Showcard( json_msgs, wSize-sizeof(recvMsg)) ) {
        pUser->Showcards();
        int wLen = pUser->Makeup_Showcard( json_msgs, sizeof(json_msgs) );
        pUser->SendToTable( json_msgs,  wLen);
    }
}

HANDLER_IMPL( Discards_REQ )
{
	printf("Discards_REQ\n");


	MSG_BASE_FORWARD * recvMsg = (MSG_BASE_FORWARD *)pMsg;
	printf(">>> User Port = %d\n", recvMsg->m_wUserPort );

	char json_msgs[1024] = {0};
	memcpy(json_msgs, (( BYTE*)pMsg)+sizeof( recvMsg ), wSize-sizeof(recvMsg) );

	GameUser * pUser = g_pGameRoom.FindUser( recvMsg->m_wUserPort );
    if ( pUser == NULL ) {
        return;
    }

    if ( pUser->Parser_Discards( json_msgs, wSize-sizeof(recvMsg)) ) {
        pUser->Discards();
        int wLen = pUser->Makeup_Discards( json_msgs, sizeof(json_msgs) );
        pUser->SendToTable( json_msgs,  wLen);
    }

}

