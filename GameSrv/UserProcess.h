#ifndef _USERPROCESS_H_INCLUDED_
#define _USERPROCESS_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include "GamePokerList.h"

enum
{
    eGU_EMPTY   = 0x0000,
    eGU_LEAVE   = 0x0001,
    eGU_WATCH   = 0x0002,   // 观察
    eGU_SIT     = 0x0004,   // 坐下
    eGU_READY   = 0x0008,   // 准备
    eGU_PLAYING = 0x0010,   // 正完
    eGU_SHOW    = 0x0020,   // 明牌
    eGU_CALL    = 0x0040,   // 叫牌
    eGU_BANK    = 0x1000,   // 庄
    eGU_PLAYER  = 0x2000,   // 贤
};

/*
 *  用户消息
 *
 */
class UserProcess
{
public:
	UserProcess();
	virtual ~UserProcess();

public:
	int Parser_Login( const char * pInput, WORD wSize );
	int Parser_Login( MSG_LOGIN_ANC * pMsg );
	int Makeup_Login( MSG_LOGIN_REQ * pMsg );
	int Makeup_Login( char * pInput, WORD wSize );
	int Parser_Logout( const char * pInput, WORD wSize );
	int Makeup_Logout( char * pInput, WORD wSize );
	int Parser_TableChat ( const char * pInput, WORD wSize );
	int Makeup_TableChat ( char * pInput, WORD wSize );

	int Parser_JoinWatch( const char * pInput, WORD wSize );
	int Makeup_JoinWatch( char * pInput, WORD wSize );
	int Parser_QuitWatch( const char * pInput, WORD wSize );
	int Makeup_QuitWatch( char * pInput, WORD wSize );
	int Parser_JoinTable( const char * pInput, WORD wSize );
	int Makeup_JoinTable( char * pInput, WORD wSize );
	int Parser_QuitTable( const char * pInput, WORD wSize );
	int Makeup_QuitTable( char * pInput, WORD wSize );
    int Parser_StartGame( const char * pInput, WORD wSize );
    int Makeup_StartGame( char * pInput, WORD wSize );
    int Parser_Showcard ( const char * pInput, WORD wSize );
    int Makeup_Showcard ( char * pInput, WORD wSize );
    int Parser_Called   ( const char * pInput, WORD wSize );
    int Makeup_Called   ( char * pInput, WORD wSize );
    int Makeup_Alloccards( char * pInput, WORD wSize );
    int Parser_Discards ( const char * pInput, WORD wSize );
    int Makeup_Discards ( char * pInput, WORD wSize );
    int Makeup_Settlement( char * pInput, WORD wSize );
    int Makeup_Error( int errorno, char * pInput, WORD wSize );

public:
    virtual int SetPoker(const char * value, int wSize) {
        return 0;
    };

public:
    BYTE m_byRemove;    // 已经退出
    UINT m_uiUserid;    // 用户ID

    WORD m_wUserKey;    // 用记Key
    BYTE m_bySSHKey[CODE_KEY_LEN+1];

    UINT m_uiStatus;    // 状态
    BYTE m_byShow;      // 是显示牌
    BYTE m_byBank;      // 是否地主

    DWORD m_dwChip;     // 赢钱
    DWORD m_dwFreeze;   // 冻结

	GamePokerList   m_hold;  // 持有
    GamePokerList   m_just;  // 打出

    WORD m_wTable;      // 桌位号
    BYTE m_bySeat;      // 坐位号

    UINT m_uiPoints; 	// 分数
	UINT m_uiWons; 		// 失败次数
	UINT m_uiFaileds; 	// 赢的次数
	UINT m_uiAways; 	// 逃跑次数
};


#endif // _JSON_LOGINREQ_H_INCLUDED_
