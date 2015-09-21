#ifndef _GameUserList_H_INCLUDED_
#define _GameUserList_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include <Network.h>
#include "GameUser.h"

class GameUserList
{
public:
	GameUserList();
	~GameUserList();

public:

    void clear();
    void push_back(GameUser * pUser);
    void remove(GameUser * pUser);
    WORD size() { return m_size; }

    GameUser * get_frist();

private:
    WORD m_size;
    GameUser * m_head;
    GameUser * m_last;
};

#endif // _GameUserList_H_INCLUDED_

