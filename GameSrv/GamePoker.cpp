#include "GamePoker.h"


GamePoker::GamePoker()
{
    m_pkid = 0;
    m_prev = NULL;
    m_next = NULL;
}

GamePoker::~GamePoker()
{
}

void GamePoker::clear() {
    m_prev = NULL;
    m_next = NULL;
}

GamePoker * GamePoker::set_prev( GamePoker * _prev ) {
    GamePoker * t = m_prev;
    m_prev = _prev;
    return t;
}

GamePoker * GamePoker::set_next( GamePoker * _next ) {
    GamePoker * t = m_next;
    m_next = _next;
    return t;
}

bool GamePoker::is_null_prev() {
    return (m_prev != NULL);
}
bool GamePoker::is_null_next() {
    return (m_next != NULL);
}

GamePoker * GamePoker::get_prev() {
    return (m_prev);
}

GamePoker * GamePoker::get_next() {
    return (m_next);
}
