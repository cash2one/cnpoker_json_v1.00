#ifndef _GAMEUSER_H_INCLUDED_
#define _GAMEUSER_H_INCLUDED_

#include <Network.h>
#include <Utility.h>
#include <Common.h>
#include "GamePoker.h"
#include "UserProcess.h"

using namespace A;

class GameUser : public UserProcess
{
public:
    GameUser();
    virtual ~GameUser();

public:
    int Init();
    int Update();

    // base function
    void SetHashKey ( WORD _userkey) { m_wUserKey = _userkey; }
    WORD GetHashKey () const { return m_wUserKey; }

    // base function
    void SetUserid ( UINT _userid) { m_uiUserid = _userid; }
    WORD GetUserid () const { return m_uiUserid; }

    // network function
    void SendToClient( BYTE * pMsg, WORD wSize );
    void SendToTable( const char * pInput, WORD wSize );

public:
    // 打出的牌设置;
	virtual int SetPoker( const char * value, int wSize );

public: // 状态
     // game function
    int JoinWatch();
    int QuitWatch();
    int JoinTable();
    int LeaveTable();


    int IsReady();      // 准备好
    void Ready();        // 准备

public: // 比较
    int Showcards();    // 明牌
    int Discards();     // 打牌

    BYTE m_byThanType;      // 比较类型
    BYTE m_byThanValue;     // 比较面值
    BYTE m_byThanCount;     // 比较张数

public: // 结算
    int Called();    // 叫地主
    int Accountant( bool woned ); // 结算

public: // 游戏
    void clear_poker();
    size_t poker_size();
    void push_poker(GamePoker * x);
    void pop_poker(GamePoker * x);

    //==========================
    friend class GameRoom;
    friend class GameTable;

public:
    // 用户群
    void clear_user();

    GameUser * set_prev( GameUser * _prev );
    GameUser * set_next( GameUser * _next );

    bool is_null_prev();
    bool is_null_next();

    GameUser * get_prev();
    GameUser * get_next();

private:
    GameUser * m_prev;
    GameUser * m_next;
};

#endif
