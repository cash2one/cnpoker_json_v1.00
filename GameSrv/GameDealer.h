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
#define DE_TABLE_EMPTY  0xF0   // ����Ϊ��
#define DE_SEAT_EMPTY   0xF1   // ��λ����
#define DE_SEAT_FULL    0xF1   // ��λ����
#define DE_PLAYING      0xF2   // ������Ϸ
*/

enum ePK_TYPE   // ���Ƶ�����
{
    PH_0 	= 0    , 		// ��Ч
    PH_1 	= 100  , 		// ����
    PH_2 	       , 		// ����
    PH_3 	       ,		// ����
    PH_31 	       ,		// ����һ
    PH_32 	       ,		// ������
    PH_41 	       ,		// �Ĵ�һ
    PH_411 	       ,		// �Ĵ�����
    PH_42 	       ,		// �Ĵ�һ��
    PH_422 	       ,		// �Ĵ�����
    PH_C1 	= 200  , 		// ˳��
    PH_C2 	       ,		// ����
    PH_C3 	       ,		// �ɻ�
    PH_4 	= 500  ,		// ը��
    PH_MAX 	       ,		// ��ը
    PH_End 	= 1000 ,		// ��Ч
};

enum ePK_POWER
{
    PH_INVALID = 0 , 		// ��Ч�Ƽ�
    PH_PASS    = 10, 		// ת����Ȩ
    PH_AGAIN       , 		// �ٳ���Ȩ
    PH_THAN        , 		// �ȴ��Ƚ�
};

class GameDealer
{
public:

	GameDealer();
	virtual ~GameDealer(void);

	// ����
    int Deal( BYTE div = 3, BYTE reserver = 3 );

    // ������
    int Alloc(  GameUser * pUser  );

    // �Ƚ���ֵ
    int Than( GameUser * pUser, GameUser * thanObj );

    // ������ֵ
	int Parser( GameUser * pUser );

private:
    GameUser * m_tokenUser;                 // ���������û�
    GamePoker  m_byPoker[CNPOKER_LEN_1];    // ���е���
    GamePoker  m_byExtra[CNPOKER_HOLE];     // �������
};


#endif // _POKER_H_INCLUDED_
