#ifndef _GAMEPOKER_H_INCLUDED_
#define _GAMEPOKER_H_INCLUDED_

#include <Common.h>

class GamePoker
{
public:

	GamePoker();
	virtual ~GamePoker(void);

public:
    void clear();

    GamePoker * set_prev( GamePoker * _prev );
    GamePoker * set_next( GamePoker * _next );

    bool is_null_prev();
    bool is_null_next();

    GamePoker * get_prev();
    GamePoker * get_next();

    BYTE m_pkid;
    UINT m_usid;

private:

    GamePoker * m_prev;
    GamePoker * m_next;

};


#endif // _POKER_H_INCLUDED_
