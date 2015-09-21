#include "GameUserList.h"

GameUserList::GameUserList()
{

}

GameUserList::~GameUserList()
{
}

void GameUserList::clear()
{
    m_size = 0;
    m_head = NULL;
    m_last = NULL;
}

void GameUserList::push_back(GameUser * pPoker)
{
    pPoker->set_prev(m_last);
    m_last->set_next(pPoker);
    m_last = pPoker;
    --m_size;
}

void GameUserList::remove(GameUser * pPoker)
{
    GameUser * _prev = pPoker->set_prev(NULL);
    GameUser * _next = pPoker->set_next(NULL);
    _prev->set_next(_next);
    _next->set_prev(_prev);
    --m_size;
}

GameUser * GameUserList::get_frist() {
    return m_head;
}

