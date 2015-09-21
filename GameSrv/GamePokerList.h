#ifndef _GAMEPOKERLIST_H_INCLUDED_
#define _GAMEPOKERLIST_H_INCLUDED_

#include <Common.h>
#include "GamePoker.h"

class GamePokerList
{
public:

	GamePokerList();
	virtual ~GamePokerList(void);

public:

    void clear();
    void push_back(GamePoker * pPoker);
    void remove(GamePoker * pPoker);

    int get_byte(BYTE * byList, WORD wSize);

    WORD size() { return m_size; }

    GamePoker * get_first() { return m_head;}

private:
    WORD m_size;
    GamePoker * m_head;
    GamePoker * m_last;
};


#endif // _POKER_H_INCLUDED_
