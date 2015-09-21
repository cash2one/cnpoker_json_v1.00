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
        eGR_ROOMFULL           ,         // ��������
        eGR_FOUNDTABLE         ,         // �Ҳ�������
    };

public:
    GameRoom();

    virtual ~GameRoom();

    int Create(WORD wTables);

    GameUser *  AllocUser( WORD _userKey ); //����һ���û�
    GameUser *  FindUser( WORD _userKey);  // ����һ���û�
    void        FreeUser( WORD _userKey);  // ����һ���û�

    GameTable * SearchSeat(); // ����һ������λ
    GameTable * SearchSeat(WORD tIndex, WORD tSeat);    // ����һ��ָ������λ

protected:

    // Table
    WORD m_TableSize;
    GameTable * m_pTable[DF_MAX_TABLES];      // ��ʼ������

    WORD m_pUserSize;
    GameUser * m_pUser[DF_MAX_USERS];
};

extern GameRoom g_pGameRoom;

#endif
