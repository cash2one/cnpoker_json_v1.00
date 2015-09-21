#include "GameTable.h"
#include "GameServer.h"

GameTable::GameTable() {
    memset( this, 0x0, sizeof(this) );
}

GameTable::~GameTable() {
}

int GameTable::JoinWatch( GameUser * pUser ) {
    if ( m_watchUser.size() < MAX_WATCH ) {
        m_watchUser.push_back( pUser );
        return true;
    }
    return false;
}

int GameTable::QuitWatch( GameUser * pUser ) {
    m_watchUser.remove( pUser );
}

int GameTable::JoinTable( WORD tSeat, GameUser * pUser )
{
    // 离开其他房间通知
    pUser->LeaveTable();

    if ( m_pSeatUser[tSeat] == NULL ) {
        m_pSeatUser[tSeat] = pUser;
        ++m_byJoinCount;
    }
    else {
        m_pSeatUser[tSeat]->LeaveTable();
        m_pSeatUser[tSeat] = pUser;
    }
}

int GameTable::QuitTable( GameUser * pUser )
{
   BYTE tSeat = pUser->m_bySeat;
   if ( m_pSeatUser[tSeat] != NULL ) {
        m_pSeatUser[tSeat]->LeaveTable();
        m_pSeatUser[tSeat] = NULL;
        ++m_byJoinCount;
   }
}

/* 判断有没有空坐位 */
int GameTable::hasEmptySeat()
{
    int i = 0;
    for (i = 0; i < 3; ++i )
    {
        if ( m_pSeatUser[i] == NULL ) {
            return i+1;
        }
    }
    return 0;
}

/* 判断某座位是否为空 */
int GameTable::hasEmptySeat(WORD tSeat) {
    if ( m_pSeatUser[tSeat - 1] == NULL ) {
        return tSeat;
    }
    return 0;
}

/* 取得空座位ID */
BYTE GameTable::getEmptySeat() {
    return hasEmptySeat();
}

/* 取得桌面ID */
int GameTable::getTableId() {
    return m_uiTableIndex;
}

/* 开始游戏 */
int GameTable::StartGame()
{
    if ( m_byJoinCount == MAX_SEAT)
    {
        for ( int i = 0; i < m_byJoinCount; ++i ) {
            if ( m_pSeatUser[i]->IsReady() == 0 ) {
                  return FALSE;  // 有人没准备好
            }
        }

        // 把坐位串起来
        GameUser * pUser = m_pSeatUser[0];
        for ( int i = 1; i < m_byJoinCount; ++i ) {
            pUser->set_next( m_pSeatUser[i] );
            m_pSeatUser[i]->set_prev( pUser );
            pUser = m_pSeatUser[i];
        }
        m_pSeatUser[m_byJoinCount - 1]->set_next(pUser);
        pUser->set_prev( m_pSeatUser[m_byJoinCount - 1] );

        // 洗牌
        m_dealer.Deal();
        pUser = m_pSeatUser[0];
        for ( int i = 0; i < m_byJoinCount; ++i ) {
            m_dealer.Alloc( m_pSeatUser[i] );
        }

        // 发消息给所有人已经开始了;

        return TRUE;  // 都准备好了
    }
    return FALSE; // 不够人数
}

/* 出牌 */
int GameTable::Discards( GameUser * thanUser )
{
    GameUser * next = NULL;
    next = thanUser->get_next();
    if ( next ) {

        // 比较牌面值
        int retV = m_dealer.Parser( thanUser );
        if ( retV == PH_MAX ) {
            thanUser->Discards();
        }

        // 比较双方大小 | 防止客户端作弊
        if ( m_dealer.Than( m_privUser, thanUser ) ) {
            // 发送错误消息
            return false;
        }

        if (thanUser->poker_size() == 0) {
            return this->Settlement( thanUser );
        }

        // 通知下一位出牌;
        m_privUser = thanUser;
        return next->Discards();
    }

    return false;
}

/* 不要 */
int GameTable::Pass( GameUser * pUser )
{
    GameUser * next = NULL;

    next = pUser->get_next();
    if ( next ) {
        m_privUser = pUser;
        return next->Discards();
    }

    return false;
}

/* 结算 */
int GameTable::Settlement( GameUser * winUser )
{
    for ( int i = 0; i < m_byJoinCount; ++i ) {
        if ( m_pSeatUser[i] == winUser ) {
            m_pSeatUser[i]->Accountant(1);
        }

        if ( m_pSeatUser[i] ==  winUser) {

        }
    }
    return TRUE;
}

// 向所有人发送Json数据
int GameTable::Broadcast(BYTE * msg, WORD wSize)
{
    for ( int i = 0; i < m_byJoinCount; ++i ) {
        m_pSeatUser[i]->SendToClient(msg, wSize);
    }

    GameUser * pUser = m_watchUser.get_frist();
    for ( ; pUser ; pUser = pUser->get_next() ) {
        pUser->SendToClient(msg, wSize);
    }
}
