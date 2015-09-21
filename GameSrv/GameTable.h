#ifndef _GAMETABLE_H_INCLUDED_
#define _GAMETABLE_H_INCLUDED_

#include <Network.h>
#include <Utility.h>
#include <Common.h>
#include <Public.h>
#include "GameUser.h"
#include "GameUserList.h"
#include "GameDealer.h"

using namespace A;

#define MAX_SEAT        (3)
#define MAX_WATCH       (9)

class GameTable
{
    enum eCHAIR
    {
        eGT_EMPTY       = 0,     // 坐位为空
        eGT_WAITING        ,     // 坐下
        eGT_CHAIR1         ,
        eGT_CHAIR2         ,
        eGT_CHAIR3         ,
    };

public:

	GameTable();
	virtual ~GameTable();

	int Init();
	int Update();                               // 超时处理

	int JoinWatch( GameUser * pUser );          // 加入观看
	int QuitWatch( GameUser * pUser );          // 退出观看

	int JoinTable( WORD tSeat,GameUser* pUser );// 坐下
    int QuitTable( GameUser * pUser );          // 退出

    int  hasEmptySeat();                        // 判断有没有空坐位
    int  hasEmptySeat(WORD tSeat);              // 判断某座位是否为空
    BYTE getEmptySeat();                        // 取得空座位ID
    int  getTableId();                          // 取得桌子ID

	int StartGame();                            // 判断都开始后游戏
    int Discards( GameUser * thanUser );        // 判断玩家出牌
    int Pass( GameUser * pUser );               // 判断玩家出牌

    int Settlement( GameUser * winUser );       // 结算
	int Broadcast( BYTE *pMsg, WORD wSize );    // 发送消息给所有在桌玩家

protected:
    friend class GameUser;
    friend class GameRoom;

    // 观看用户
    GameUserList m_watchUser;

    // 桌子的编号
    UINT m_uiTableIndex;

    // 参加的游戏用户数
    BYTE m_byJoinCount;

    // 参加的游戏用户
    GameUser * m_privUser;      // 上一个消息用户
	GameUser * m_pSeatUser[3];

	// 荷官
    GameDealer m_dealer;
};


#endif
