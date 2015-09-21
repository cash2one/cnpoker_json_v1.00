#ifndef _GameRoom_H_INCLUDED_
#define _GameRoom_H_INCLUDED_

#include <Network.h>
#include <Utility.h>
#include <Common.h>
#include <Public.h>
#include "GameTable.h"
#include "GameUserList.h"

#define DF_TABLE_PS     3
#define DF_MAX_TABLES   (0xFFFF/3)
#define DF_MAX_USERS    0xFFFF

class GameRoom
{
public:

    enum
    {
        eGR_OK              = 0,         // ok
        eGR_ROOMFULL           ,         // 房间满了
        eGR_FOUNDTABLE         ,         // 找不到桌子
    };

public:
    GameRoom();

    virtual ~GameRoom();

    int Create(WORD wTables);

    GameUser *  AllocUser( WORD _userKey ); //分配一个用户
    GameUser *  FindUser( WORD _userKey);  // 查找一个用户
    void        FreeUser( WORD _userKey);  // 查找一个用户

    GameTable * SearchSeat(); // 查找一个空坐位
    GameTable * SearchSeat(WORD tIndex, WORD tSeat);    // 查找一个指定空坐位

protected:

    // Table
    WORD m_TableSize;
    GameTable * m_pTable[DF_MAX_TABLES];      // 开始的桌子

    WORD m_pUserSize;
    GameUser * m_pUser[DF_MAX_USERS];
};

extern GameRoom g_pGameRoom;

#endif
