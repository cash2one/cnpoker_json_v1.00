#include "GameRoom.h"
#include "GameFactory.h"
#include "GameUserList.h"

GameRoom g_pGameRoom;

/*******************************/
GameRoom::GameRoom()
{

}

GameRoom::~GameRoom()
{

}

/*
 *  ��������
 */
int GameRoom::Create(WORD wTableSize)
{
    memset ( m_pTable, 0x0, sizeof(m_pTable) );
    memset ( m_pUser,  0x0, sizeof(m_pUser) );

    m_TableSize = wTableSize;

    GameFactory * pFactory = GameFactory::Instance();

    // init table
    if ( pFactory ) {
        GameTable * pGameTable = NULL;
        for( DWORD i = 0; i < wTableSize; ++i ) {
            pGameTable = pFactory->AllocGameTable();
            if ( pGameTable ) {
               pGameTable->m_uiTableIndex = i;
               m_pTable[i] = pGameTable;
            }
        }
    }

    return TRUE;
}

/*
 *  �����û�
 */
GameUser * GameRoom::AllocUser(WORD _userKey)
{
    GameFactory * pFactory = GameFactory::Instance();
    if ( pFactory ) {

        GameUser *_pUser = pFactory->AllocGameUser();

        if ( !_pUser ) {
            return NULL;
        }

        GameUser *_list = m_pUser[_userKey];
        if ( _list ) {
            // printf error
            pFactory->FreeGameUser(_list);
        }

        m_pUser[_userKey] = _pUser;
        _pUser->SetHashKey( _userKey );

        return _pUser;
    }
    return NULL;
}

/*
 *  �����û�
 */
GameUser * GameRoom::FindUser( WORD _userKey ) {
    return m_pUser[_userKey];
}

/*
 *  �ر��û�
 */
void GameRoom::FreeUser( WORD _userKey)
{
    GameUser *_list = m_pUser[_userKey];
    if ( _list ) {
        GameFactory::Instance()->FreeGameUser(_list);
    }
    m_pUser[_userKey] = NULL;
}

/*
 *  ���ҿ���λ
 */
GameTable * GameRoom::SearchSeat()
{
    for( int i = 0; i < m_TableSize; ++i ) {
        if ( m_pTable[i]->hasEmptySeat() ) {
            return m_pTable[i];
        }
    }
    return NULL;
}

/*
 *  ����ָ����λ
 */
GameTable * GameRoom::SearchSeat(WORD tIndex, WORD tSeat )
{
    if (tIndex < m_TableSize) {
        if ( m_pTable[tIndex]->hasEmptySeat(tSeat) ) {
            return m_pTable[tIndex];
        }
    }
    return NULL;
}
