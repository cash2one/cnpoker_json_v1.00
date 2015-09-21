#ifndef _GAMEDEALER_H_INCLUDED_
#define _GAMEDEALER_H_INCLUDED_

#include <Common.h>
#include "GameUser.h"
#include "GamePokerList.h"

#define PK_MAX_STRING   ( 20 )
#define CNPOKER_LEN_1   ( 54 )

#define CNPOKER_USER1 			( 0 )
#define CNPOKER_USER2 			( 1 )
#define CNPOKER_USER3 			( 2 )
#define CNPOKER_HOLE			( 3 )

// Error Msg
/*
#define DE_TABLE_EMPTY  0xF0   // 桌子为空
#define DE_SEAT_EMPTY   0xF1   // 坐位已满
#define DE_SEAT_FULL    0xF1   // 坐位已满
#define DE_PLAYING      0xF2   // 正在游戏
*/

enum ePK_TYPE   // 出牌的类型
{
    PH_0 	= 0    , 		// 无效
    PH_1 	= 100  , 		// 单牌
    PH_2 	       , 		// 对子
    PH_3 	       ,		// 三个
    PH_31 	       ,		// 三带一
    PH_32 	       ,		// 三带二
    PH_41 	       ,		// 四带一
    PH_411 	       ,		// 四带两单
    PH_42 	       ,		// 四带一对
    PH_422 	       ,		// 四带两对
    PH_C1 	= 200  , 		// 顺子
    PH_C2 	       ,		// 连对
    PH_C3 	       ,		// 飞机
    PH_4 	= 500  ,		// 炸弹
    PH_MAX 	       ,		// 王炸
    PH_End 	= 1000 ,		// 无效
};

enum ePK_POWER
{
    PH_INVALID = 0 , 		// 无效牌集
    PH_PASS    = 10, 		// 转出牌权
    PH_AGAIN       , 		// 再出牌权
    PH_THAN        , 		// 等待比较
};

class GameDealer
{
public:

	GameDealer();
	virtual ~GameDealer(void);

	// 发牌
    int Deal( BYTE div = 3, BYTE reserver = 3 );

    // 分配牌
    int Alloc(  GameUser * pUser  );

    // 比较牌值
    int Than( GameUser * pUser, GameUser * thanObj );

    // 分析牌值
	int Parser( GameUser * pUser );

private:
    GameUser * m_tokenUser;                 // 持有令牌用户
    GamePoker  m_byPoker[CNPOKER_LEN_1];    // 所有的牌
    GamePoker  m_byExtra[CNPOKER_HOLE];     // 额外的牌
};


#endif // _POKER_H_INCLUDED_
