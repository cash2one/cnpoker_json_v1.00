#include "GameUser.h"
#include "GameRoom.h"
#include "GameServer.h"

/*******************************/
GameUser::GameUser()
{
}

GameUser::~GameUser()
{
}

int GameUser::Init()
{
    m_uiStatus = eGU_EMPTY;
    return 0;
}

int GameUser::Update()
{
    return 0;
}

// 发送消息到客户端
void GameUser::SendToClient( BYTE * pMsg, WORD wSize ) {
    g_GameServer->SendToAgentServer( pMsg, wSize );
}

void GameUser::SendToTable( const char * pInput, WORD wSize )
{
    // g_GameServer->SendToAgentServer( msg, wSize );

    GameTable * pTable = NULL;
    pTable = g_pGameRoom.SearchSeat(m_wTable, m_bySeat);

    if (pTable != NULL) {

        MSG_BASE_FORWARD send;
        send.m_dwUserID  = m_uiUserid;
        send.m_wUserPort = m_wUserKey;

        BYTE send_msgs[1024] = {0};
        memcpy(send_msgs, (BYTE*)&send, sizeof(send));

        int nLen = sizeof(send);
        memcpy(send_msgs+nLen, (BYTE*)pInput, wSize);

        nLen += wSize;
        pTable->Broadcast(send_msgs, nLen);
    }
}

int GameUser::JoinWatch()
{
    GameTable * pTable = NULL;
    pTable = g_pGameRoom.SearchSeat(m_wTable, 0);
    if (pTable != NULL) {

        pTable->JoinWatch( this );

        char json_msgs[1024] = {0};
        int nLen = this->Makeup_JoinWatch(json_msgs, 1024);

        this->SendToTable(json_msgs, nLen);
        return true;
    }
    return false;
}

int GameUser::QuitWatch()
{
    GameTable * pTable = NULL;
    pTable = g_pGameRoom.SearchSeat(m_wTable, 0);
    if (pTable != NULL) {

        pTable->JoinWatch( this );

        char json_msgs[1024] = {0};
        int nLen = this->Makeup_QuitWatch(json_msgs, 1024);

        this->SendToTable(json_msgs, nLen);
        return true;
    }
    return false;
}

int GameUser::JoinTable()
{
    GameTable * pTable = NULL;
    pTable = g_pGameRoom.SearchSeat( m_wTable, 0 );
    if (pTable != NULL) {

        pTable->JoinTable( m_bySeat, this );

        char json_msgs[1024] = {0};
        int nLen = this->Makeup_JoinTable(json_msgs, 1024);

        this->SendToTable(json_msgs, nLen);
        return true;
    }
    return false;
}

int GameUser::LeaveTable()
{
    if ( m_uiStatus == eGU_LEAVE )
    {
        GameTable * pTable = NULL;
        pTable = g_pGameRoom.SearchSeat( m_wTable, 0 );

        if (pTable != NULL)
        {
            pTable->JoinTable( m_bySeat, this );

            char json_msgs[1024] = {0};
            int nLen = this->Makeup_JoinTable(json_msgs, 1024);

            this->SendToTable(json_msgs, nLen);

            m_wTable    = 0;
            m_bySeat    = 0;
            m_uiStatus  = eGU_LEAVE;

            return true;
        }
        return false;
    }
}

int GameUser::IsReady() {
    return (m_uiStatus | eGU_READY);
}

/*  游戏已经开始   */
void GameUser::Ready() {
    m_uiStatus = eGU_READY;

    GameTable * pTable = NULL;
    pTable = g_pGameRoom.SearchSeat(m_wTable, m_bySeat);
    if (pTable != NULL) {
        pTable->StartGame();
    }
}

/*  叫牌  */
int GameUser::Called()
{
    if ( m_uiStatus | eGU_PLAYING ) {

        GameTable * pTable = NULL;
        pTable = g_pGameRoom.SearchSeat( m_wTable, 0 );

        if (pTable != NULL)
        {
            pTable->JoinTable( m_bySeat, this );

            char json_msgs[1024] = {0};
            int nLen = this->Makeup_Called(json_msgs, 1024);

            this->SendToTable(json_msgs, nLen);

            return true;
        }
        return false;
    }
}

/* 发送显示牌 */
int GameUser::Showcards()
{
    GameTable * pTable = NULL;
    pTable = g_pGameRoom.SearchSeat( m_wTable, 0 );

    if (pTable != NULL)
    {
        char json_msgs[1024] = {0};
        int nLen = this->Makeup_Showcard(json_msgs, 1024);

        this->SendToTable(json_msgs, nLen);
        return true;
    }
    return false;
}

int GameUser::Discards()
{
    // 打牌通知;
    GameTable * pTable = NULL;
    pTable = g_pGameRoom.SearchSeat( m_wTable, 0 );

    if (pTable != NULL)
    {
        pTable->Discards( this );

        char json_msgs[1024] = {0};
        int nLen = this->Makeup_Showcard(json_msgs, 1024);

        this->SendToTable(json_msgs, nLen);
        return true;
    }
    return false;
}

int GameUser::Accountant( bool mult )  // 结算
{

    return 0;
}

int GameUser::SetPoker(const char * value, int wSize)
{

    return 0;
}

void GameUser::clear_poker() {
    m_hold.clear();
    m_just.clear();
}

size_t GameUser::poker_size() {
    return m_hold.size();
}

void GameUser::push_poker( GamePoker * poker ) {
    m_hold.push_back( poker );
}

void GameUser::pop_poker( GamePoker * poker ) {
    m_hold.remove( poker );
    m_just.push_back( poker );
}


void GameUser::clear_user(){
    m_prev = NULL;
    m_next = NULL;
}

GameUser * GameUser::set_prev( GameUser * _prev ) {
    GameUser * t = m_prev;
    m_prev = _prev;
    return t;
}

GameUser * GameUser::set_next( GameUser * _next ) {
    GameUser * t = m_next;
    m_next = _next;
    return t;
}

bool GameUser::is_null_prev() {
    return (m_prev != NULL);
}
bool GameUser::is_null_next() {
    return (m_next != NULL);
}

GameUser * GameUser::get_prev() {
    return (m_prev);
}

GameUser * GameUser::get_next() {
    return (m_next);
}
