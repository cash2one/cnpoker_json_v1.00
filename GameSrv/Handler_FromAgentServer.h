#ifndef _HANDLER_FROMAGENTSERVER_H_INCLUDED_
#define _HANDLER_FROMAGENTSERVER_H_INCLUDED_

#include <Common.h>

#include "ServerSession.h"

#define HANDLER_DECL( p )			static VOID On##p( ServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
#define HANDLER_IMPL( p )			VOID Handler_FromAgentServer::On##p( ServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )

class Handler_FromAgentServer
{
public:
	Handler_FromAgentServer(void);
	~Handler_FromAgentServer(void);

#if 0
	HANDLER_DECL( Heartbeat_SYN );

	HANDLER_DECL( Logout_REQ );
	HANDLER_DECL( Relogin_SYN );
#endif

	HANDLER_DECL( Login_REQ ); 	        // 登录
	HANDLER_DECL( Logout_REQ ); 	    // 登出
	HANDLER_DECL( JoinWatch_REQ );      // 加入观察
	HANDLER_DECL( QuitWatch_REQ );      // 退出观察
	HANDLER_DECL( JoinTable_REQ );      // 加入桌子
	HANDLER_DECL( QuitTable_REQ );      // 退出桌子
	HANDLER_DECL( StartGame_REQ );      // 开始游戏
	HANDLER_DECL( ShowCards_REQ );      // 显示牌
	HANDLER_DECL( Called_REQ );         // 叫地主
	HANDLER_DECL( Discards_REQ );       // 出牌
};

#endif
