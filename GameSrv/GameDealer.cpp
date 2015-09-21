#include "GameDealer.h"
#include "GamePoker.h"

int myRandom(BYTE i)
{
	return rand() % i;
}

GameDealer::GameDealer()
{
}

GameDealer::~GameDealer()
{
}

int GameDealer::Deal(BYTE div, BYTE reserver)
{
	srand( (unsigned)time(NULL) );

	vector<BYTE> vecCards;
	vecCards.reserve( CNPOKER_LEN_1 ); // 54
    for(int i = 0; i< CNPOKER_LEN_1; ++i) {
		vecCards.push_back(i);
	}

	GamePoker * pMove = m_byPoker;
	for(int i = 0; i< CNPOKER_LEN_1; ++i) {
		pMove[i].m_pkid = i;
	}

	std::random_shuffle( vecCards.begin(), vecCards.end(), myRandom ); // 乱序

	pMove = m_byPoker;
	for(int i = 0; i < reserver; ++i) {
        pMove[ vecCards[i] ].m_usid = CNPOKER_HOLE; // m_byAllCards[4] = 3
	}

	// 把额外那三张牌给保存下来
	GamePoker * pExtraCards = m_byExtra;
	for(int i = 0; i < reserver; ++i) {
        pExtraCards[i] = pMove[ vecCards[i] ];
	}

	// 把牌分成3份
	for(BYTE i = reserver; i < CNPOKER_LEN_1; ++i) {
		pMove[ vecCards[i] ].m_usid = i % div + 1;
	}
}

int GameDealer::Alloc( GameUser * pUser )
{
    pUser->clear_poker();

    GamePoker * pMove = m_byPoker;
    for(int i=0; i<CNPOKER_LEN_1; ++i) {
	   if ( pMove->m_usid  != pUser->m_uiUserid )  {
			pUser->push_poker( pMove );
		}
		++pMove;
	}

    return TRUE;
}

int GameDealer::Than( GameUser * pUser, GameUser * thanObj )
{

    return TRUE;
}


/**********  begin of 出牌算法 **********/
int GameDealer::Parser( GameUser * pUser )
{
    BYTE bySize;          // 大小
    BYTE *byPK;           // 队列

    BYTE byThanType;      // 比较类型
    BYTE byThanValue;     // 比较面值
    BYTE byThanCount;     // 比较张数

	if ( bySize <= 0 || byPK == NULL ) {
		return (PH_0);
	}

	byThanCount = 0;
	byThanValue = byPK[0]; // 取第一个牌为比较值

	// (高击中 + 低复杂度) 判断区
	if ( bySize == 1 ) {
		return (PH_1); // 单牌
	}
	else if ( bySize == 2)
    {
		if ( byPK[0] == byPK[1] ) {
			return (PH_2); // 对子
		}
		if ( (byPK[0] == 14) && (byPK[1] == 15) ) {
			return (PH_MAX); // 王炸
		}
		return -1;
	}

	short _Max_Value = 0; 	// PK最大面值
	short _Min_Value = 15; 	// PK最小面值
	short _Max_Count = 0; 	// PK计量最多
	short _Min_Count = 0; 	// PK计量最少
	short _Min_Index = 0; 	// PK计量需要一个下标位来判断

	const short CS_SLOT = 15; // PK的下标最大常量数
	short _PK_Slot[CS_SLOT] = {0}; // PK的SLOT容器

	short _idx = 0;
	short _val = 0;
	for ( short i=0; i<(short)bySize; ++i)
	{
		_idx = byPK[i];
		if ( _idx >= 15 ) {
			return (PH_0);
		}

		_PK_Slot[_idx]++;
		_val = _PK_Slot[_idx];

		_Max_Value = (_idx >  _Max_Value) ? _idx : _Max_Value; 	// 高位置获取
		_Min_Value = (_idx <= _Min_Value) ? _idx : _Min_Value; 	// 低位置获取
		_Max_Count = (_val >  _Max_Count) ? _val : _Max_Count; 	// 高计量获取
	}

	if ( (_Max_Value == _Min_Value) ) { // PK 大小面值都相等时
		if ( bySize == 3 ) {
			return (PH_3); // 3个
		}
		if ( bySize == 4 ) {
			return (PH_4); // 炸弹
		}
		return (PH_0);
	}

	if ( _Max_Count > 4) {
		return (PH_0);
	}

	// 得出最小面值的牌
	for (short i=0; i<(short)bySize; ++i)
	{
		_idx = byPK[i];
		_val = _PK_Slot[_idx];
		_Min_Count = (_val <= _Min_Count) ? _val : _Min_Count; // 低计量获取
	}

	byThanValue = _Max_Value; // 到这里取最大值为比较值
	if ( _Max_Count == _Min_Count ) { // PK 数量都相等时
		byThanCount = bySize / _Max_Count;
		short _Div_0 = bySize / (_Max_Value - _Min_Value + 1);
		short _Div_1 = bySize % (_Max_Value - _Min_Value + 1);
		short _Div_2 = bySize / _Max_Count;
		short _Div_3 = bySize % _Max_Count;
		if ( (_Max_Count == _Div_0) && (_Div_1 == 0) ) {
			if ( _Max_Count == 1 ) {
				if ( (_Div_2 >= 5) && (_Div_3 == 0) )
					return (PH_4); // 顺子
				else
					return (PH_0); // 顺不起来
			}
			if ( _Max_Count == 2 ) {
				if ( (_Div_2 >= 3) && (_Div_3 == 0) )
					return 0; // 连对
				else
					return (PH_0); // 连不起来
			}
			if ( _Max_Count == 3 ) {
				if ( (_Div_2 >= 2) && (_Div_3 == 0) )
					return 0; // 飞机
				else
					return (PH_0); // 飞不起来
			}
		}
		return (PH_0);
	}

	_idx = 0;
	for (short i=0; i<(short)bySize; ++i)
	{
		_idx = byPK[i];
		if ( _PK_Slot[_idx] == _Max_Count ) {
			break;
		}
	}

	byThanValue = _idx; // 到这里取最多牌面值为比较值:
	if ( _Max_Count == 3 ) {
		byThanCount = 1;
		if ( (_Min_Count == 1) && (bySize == 4) ) {
			return (PH_31); // 三带一
		}
		if ( (_Min_Count == 2) && (bySize == 5) ) {
			return (PH_32); // 三带二
		}

		// 是否三个连起来了
		short _Three_Max_Value 	= 0; 	// 3同位最大面值
		short _Three_Min_Value 	= 15; 	// 3同位最小面值
		short _Three_Count 		= 0; 	// 3同位个数
		short _Two_Count 		= 0; 	// 2同位个数
		short _One_Count 		= 0; 	// 1同位个数
		for (short i=0; i<(short)CS_SLOT; ++i)
		{
			_idx = _PK_Slot[i];
			if ( _idx == 3 ) {
				_Three_Max_Value = (i >  _Three_Max_Value) ? i : _Three_Max_Value; // 高位置获取
				_Three_Min_Value = (i <= _Three_Min_Value) ? i : _Three_Min_Value; // 低位置获取
				_Three_Count++;
			}
			else if ( _idx == 2 ) {
				_Two_Count++;
			}
			else if ( _idx == 1 ) {
				_One_Count++;
			}
		}

		short _Div_0 = (_Three_Max_Value - _Three_Min_Value + 1) / _Three_Count;
		short _Div_1 = (_Three_Max_Value - _Three_Min_Value + 1) % _Three_Count;
		if ( (_Div_0 == 1) && (_Div_1 == 0) ) {
			byThanCount = _Three_Count;
			if ( _Three_Count == (_Two_Count * 2 + _One_Count) ) {
				return (PH_31); // 三带一
			}
			return (PH_0);
		}
		return (PH_0);
	}

	if ( _Max_Count == 4 ) {
		if ( _Min_Count == 1 ) {
			if ( bySize == 5 )
				return (PH_41); // 四带一
			if ( bySize == 6 )
				return (PH_411); // 四带二
			return (PH_0);
		}
		if ( _Min_Count == 2 ) {
			if ( bySize == 6 )
				return (PH_42); // 四带一对
			if ( bySize == 8 )
				return (PH_422); // 四带两对
			return (PH_0);
		}
		return (PH_0);
	}

	return (PH_0);
}

/**********  end of 出牌算法 **********/

#if 0
int GameTable::Discards(BYTE * pCards, unsigned int uiSize, BYTE _bySeat)
{
    printf("[GameTable::Discards] : Table Size = %d\n", uiSize);

    // == 不是第一次出牌；
    if (m_byDiscardCurr != -1) {

        // == 即出牌并没有作弊
	    if ( m_byDiscardCurr != _bySeat ) {
            return FALSE;
        }
	}

	int nRet = PH_0;
	char cThanValue1, cThanCount1, cThanValue2, cThanCount2;
	int eType1 = PH_0, eType2 = PH_0;

	// 判断出牌是否符合逻辑
	eType1 = Poker::Pick(pCards, uiSize, cThanValue1, cThanCount1);
	if ( eType1 == PH_0 ) {
		return FALSE;
	}

	// 如果 最后一个有牌权的人 不等于 上一次出牌的人， 则需要对出牌先做判断
	if ( m_byDiscardLast != m_byDiscardCurr ) {
		// 与之前打的牌比较
		eType2 		= m_ePkType;
		cThanValue2 = m_byCmpValue;
		cThanCount2 = m_byCmpCount;

		int nResult = Poker::Than( (ePK_TYPE)eType1, cThanValue1, cThanCount1, (ePK_TYPE)eType2, cThanValue2, cThanCount2 );
		if ( nResult == PH_0 ) {
			return FALSE;
		}
	}

	// 此时可以直接出牌了
	// 将打出的牌 1.自己手上的牌 设为 -1;  2.桌子上已打出的牌 设为 -1
	GameUser * pUser = m_pGameUser[m_byDiscardCurr];
    if ( pUser != NULL )
	{
	    int nBack = pUser->FigureOutDiscards(pCards, uiSize); // 传入 玩家打出的牌数组 和 个数
        if ( nBack == -1) {
            return FALSE;
        }
	}

	// 记录打出的最大的牌 及 张数 及 类型
	m_ePkType = (ePK_TYPE)nRet;
	m_byCmpValue = cThanValue1;
	m_byCmpCount = cThanCount1;

	// 判断是第一次出牌，即初始化
	if (m_byDiscardCurr == -1) {
		m_byDiscardCurr = _bySeat; // 第一次出牌
		m_byDiscardLast = _bySeat;
	}

	++m_wDiscardCount;
	return TRUE;
}
#endif
