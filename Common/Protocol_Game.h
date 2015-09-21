#ifndef _PROTOCOLAG_H_INCLUDED_
#define _PROTOCOLAG_H_INCLUDED_

/***** 游戏服务器 -> 代理服务器 *****/
/***** Agent -> Game *****/


enum eGAME_PROTOCOL
{

	StartGame_REQ 		= 2000,
	StartGame_ANC,

	// JoinRoom_REQ, 			// 加入房间请求：【玩家X】
	// JoinRoom_BRD, 			// 加入房间应答：【房间ID, 玩家{1,2,3}】

	JoinGame_REQ, 			    // 快速加入游戏
	JoinGame_BRD, 			    // 快速加入游戏

	JoinWatch_REQ,             // 进入观察
	JoinWatch_BRD,             // 返回观察

	QuitWatch_REQ,             // 进入观察
	QuitWatch_BRD,             // 返回观察

	JoinTable_REQ, 			    // 加入桌子请求
	JoinTable_BRD, 			    // 加入桌子应答

	QuitTable_REQ, 			    // 加入桌子请求
	QuitTable_BRD, 			    // 加入桌子应答

	InitCards_BRD, 				// 服务器给所有玩家发牌

	Called_REQ, 			    // 叫庄
	Called_BRD, 			    // 叫庄广播

	ShowCards_REQ, 				// 明牌
	ShowCards_BRD,              // 明牌广播

	Discards_REQ, 				// 玩家出牌
	Discards_BRD, 				// 出牌广播

	Settlement_BRD, 			// 结算广播
	ErroNo_BRD                  // 错误广播
};

#endif // _PROTOCOLGA_H_INCLUDED_
