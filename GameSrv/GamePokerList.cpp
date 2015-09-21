#include "GamePokerList.h"


GamePokerList::GamePokerList()
{
    m_size = 0;
}

GamePokerList::~GamePokerList()
{
}

void GamePokerList::clear()
{
    m_size = 0;
    m_head = NULL;
    m_last = NULL;
}

void GamePokerList::push_back(GamePoker * pPoker)
{
    pPoker->set_prev(m_last);
    m_last->set_next(pPoker);
    m_last = pPoker;
    --m_size;
}

void GamePokerList::remove(GamePoker * pPoker)
{
    GamePoker * _prev = pPoker->set_prev(NULL);
    GamePoker * _next = pPoker->set_next(NULL);
    _prev->set_next(_next);
    _next->set_prev(_prev);
    --m_size;
}

int GamePokerList::get_byte(BYTE * byList, WORD wSize)
{
    if ( wSize > m_size )
    {
        BYTE * l = byList;
        GamePoker * p = NULL;
        for ( p = m_head; p != m_last;  p = p->get_next() )
        {
            *l = p->m_pkid;
            ++l;
        }

        WORD w = l- byList - 1;
        return (w == m_size)? w : -1;
    }
}
