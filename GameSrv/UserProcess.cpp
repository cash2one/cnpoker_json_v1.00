#include <iostream>
#include <Yond_json.h>
#include "UserProcess.h"

using std::cout;
using std::endl;

UserProcess::UserProcess()
{

}

UserProcess::~UserProcess()
{

}

/*
 *  登陆, 主要是用户ID, 认证码;
 */
int UserProcess::Parser_Login( const char * pInput, WORD wSize )
{
	cJSON * root = NULL;
	root = cJSON_Parse( pInput );
	if ( root == NULL ) {
		return -1;
	}

	// user id
	cJSON * uid = cJSON_GetObjectItem( root, "uid" );
	if ( uid ) {
		this->m_uiUserid = uid->valueint;
	}

	int nLen = 0;

	// User SshKey
	cJSON * sshkey = cJSON_GetObjectItem( root, "sshkey" );
	if ( sshkey ) {
		nLen = strlen( sshkey->valuestring );
		if ( nLen < sizeof( this->m_bySSHKey ) )
		{
			memcpy( this->m_bySSHKey, sshkey->valuestring, nLen + 1 );
			this->m_bySSHKey[ nLen ] = '\0';
		}
	}

	if ( root ) {
        cJSON_Delete( root );
    }

	return 0;
}

int UserProcess::Parser_Login( MSG_LOGIN_ANC * pMsg )
{
    this->m_wUserKey    = pMsg->m_wUserPort ;
    this->m_uiUserid    = pMsg->m_dwUserID  ;
    this->m_uiPoints    = pMsg->m_uiPoints  ;
    this->m_uiWons      = pMsg->m_uiWons    ;
    this->m_uiFaileds   = pMsg->m_uiFaileds ;
    this->m_uiAways     = pMsg->m_uiAways   ;
    return 0;
}

int UserProcess::Makeup_Login( MSG_LOGIN_REQ * pMsg )
{
    pMsg->m_wUserPort  = this->m_wUserKey ;
    pMsg->m_dwUserID   = this->m_uiUserid ;
    memcpy( pMsg->m_bySshKey, this->m_bySSHKey,sizeof(this->m_bySSHKey) );
    return 0;
}

int UserProcess::Makeup_Login( char * pInput, WORD wSize )
{
    MSG_LOGIN_ANC msg;

	char buff[1024]  = {0};
	char format[256] = 	"{\"potocol\":\"%d\","
                        "\"data\":{"
                        "\"userid\":\"%d\","
						"\"point\":\"%d\","
						"\"wons\":\"%d\","
						"\"faileds\":\"%d\","
						"\"aways\":\"%d\"}}";

	sprintf( buff, format,
         msg.m_dwProtocol,
         this->m_uiUserid,
         this->m_uiPoints,
         this->m_uiWons,
         this->m_uiFaileds,
         this->m_uiAways);

	int len = strlen(buff);
	if ( len < wSize ) {
		memcpy(pInput, buff, len);
	}
	return len;
}

int UserProcess::Parser_Logout( const char * pInput, WORD wSize )
{
	cJSON * root = NULL;
	root = cJSON_Parse( pInput );
	if ( root == NULL ) {
		return -1;
	}

	UINT id = 0;

	// user id
	cJSON * uid = cJSON_GetObjectItem( root, "uid" );
	if ( uid ) {
        id = uid->valueint;
	}

	if ( root ) {
        cJSON_Delete( root );
    }

    if ( this->m_uiUserid != id) {
        return -1;
	}

	return 0;
}

/* 某用户已经退出通知 */
int UserProcess::Makeup_Logout( char * pInput, WORD wSize )
{
    MSG_LOGOUT_ANC msg;

	char buff[1024]  = {0};
	char format[256] = 	"{\"potocol\":\"%d\","
                        "\"data\":{"
                        "\"userid\":\"%d\"}}";

	sprintf( buff, format,
         msg.m_dwProtocol,
         this->m_uiUserid);

	int len = strlen(buff);
	if ( len < wSize ) {
		memcpy(pInput, buff, len);
	}
	return len;
}

int UserProcess::Parser_TableChat ( const char * pInput, WORD wSize )
{

    return 0;
}

int UserProcess::Makeup_TableChat ( char * pInput, WORD wSize )
{

    return 0;
}

/* 加入观看 */
int UserProcess::Parser_JoinWatch( const char * pInput, WORD wSize )
{
	cJSON * root = NULL;
	root = cJSON_Parse( pInput );
	if ( root == NULL ) {
		return -1;
	}

	// User SshKey
	cJSON * table = cJSON_GetObjectItem( root, "table" );
	if ( !table ) {
		this->m_wTable = table->valueint;
	}

	if ( root ) {
		cJSON_Delete( root );
	}

	return 0;
}

/* 某用户已经正在观看 */
int UserProcess::Makeup_JoinWatch( char * pInput, WORD wSize )
{
    MSG_JOINWATCH_BRD msg;

	char buff[1024]  = {0};
	char format[256] = 	"{\"potocol\":\"%d\","
                        "\"data\":{\"userid\":\"%d\","
                                  "\"table\":\"%d\"}}";

	sprintf( buff, format,
         msg.m_dwProtocol,
         this->m_uiUserid,
         this->m_wTable);

	int len = strlen(buff);
	if ( len < wSize ) {
		memcpy(pInput, buff, len);
	}
	return len;
}

/* 申请退出观看 */
int UserProcess::Parser_QuitWatch( const char * pInput, WORD wSize )
{
	cJSON * root = NULL;
	root = cJSON_Parse( pInput );
	if ( root == NULL ) {
		return -1;
	}

	// User SshKey
	cJSON * table = cJSON_GetObjectItem( root, "table" );
	if ( !table ) {
		int uiTable = table->valueint;
		if ( this->m_wTable != uiTable) {
            return -1;
		}
		this->m_wTable = uiTable;
	}

	if ( root ) {
		cJSON_Delete( root );
	}

	return 0;
}

/* 某用户已经退出观看 */
int UserProcess::Makeup_QuitWatch( char * pInput, WORD wSize )
{
    MSG_QUITTABLE_BRD msg;

	char buff[1024]  = {0};
	char format[256] = 	"{\"potocol\":\"%d\","
                        "\"data\":{\"userid\":\"%d\","
                                  "\"table\":\"%d\"}}";

	sprintf( buff, format,
         msg.m_dwProtocol,
         this->m_uiUserid,
         this->m_wTable);

	int len = strlen(buff);
	if ( len < wSize ) {
		memcpy(pInput, buff, len);
	}
	return len;
}

/* 申请加入桌子 */
int UserProcess::Parser_JoinTable( const char * pInput, WORD wSize )
{
	cJSON * root = NULL;
	root = cJSON_Parse( pInput );
	if ( root == NULL ) {
		return -1;
	}

	// user id
	cJSON * uid = cJSON_GetObjectItem( root, "uid" );
	if ( !uid ) {
        this->m_uiUserid = uid->valueint;
	}

	// User table
	cJSON * table = cJSON_GetObjectItem( root, "table" );
	if ( !table ) {
		this->m_wTable = table->valueint;
	}

	cJSON * seat = cJSON_GetObjectItem( root, "seat" );
	if ( !seat ) {
        this->m_uiStatus = eGU_SIT;
		this->m_bySeat   = seat->valueint;
	}

	if ( root ) {
		cJSON_Delete( root );
	}

	return 0;
}

/* 某用户已经加入桌子 */
int UserProcess::Makeup_JoinTable( char * pInput, WORD wSize )
{
    MSG_JOINTABLE_BRD msg;

	char buff[1024]  = {0};
	char format[256] = 	"{\"potocol\":\"%d\","
                        "\"data\":{"
                        "\"userid\":\"%d\","
						"\"table\":\"%d\","
						"\"seat\":\"%d\"}}";

	sprintf( buff, format,
         msg.m_dwProtocol,
         this->m_uiUserid,
         this->m_wTable,
         this->m_bySeat);

	int len = strlen(buff);
	if ( len < wSize ) {
		memcpy(pInput, buff, len);
	}
	return len;
}

/* 退出桌子 */
int UserProcess::Parser_QuitTable( const char * pInput, WORD wSize )
{
	cJSON * root = NULL;
	root = cJSON_Parse( pInput );
	if ( root == NULL ) {
		return -1;
	}

	// User SshKey
	cJSON * table = cJSON_GetObjectItem( root, "table" );
	if ( !table ) {
		int uiTable = table->valueint;
		if ( this->m_wTable != uiTable) {
            return -1;
		}
		this->m_uiStatus    = eGU_LEAVE;
		this->m_wTable      = uiTable;
	}

	if ( root ) {
		cJSON_Delete( root );
	}

	return 0;
}

int UserProcess::Makeup_QuitTable( char * pInput, WORD wSize )
{
   MSG_QUITTABLE_BRD msg;

	char buff[1024]  = {0};
	char format[256] = 	"{\"potocol\":\"%d\","
                        "\"data\":{"
                        "\"userid\":\"%d\","
						"\"table\":\"%d\","
						"\"seat\":\"%d\"}}";

	sprintf( buff, format,
         msg.m_dwProtocol,
         this->m_uiUserid,
         this->m_wTable,
         this->m_bySeat);

	int len = strlen(buff);
	if ( len < wSize ) {
		memcpy(pInput, buff, len);
	}
	return len;
}

/* 开始游戏 */
int UserProcess::Parser_StartGame( const char * pInput, WORD wSize )
{
	cJSON * root = NULL;
	root = cJSON_Parse( pInput );
	if ( root == NULL ) {
		return -1;
	}

	// User SshKey
	cJSON * status = cJSON_GetObjectItem( root, "status" );
	if ( !status ) {
        if ( this->m_uiStatus == eGU_SIT)
		{
		    int uiStatus = status->valueint;
            if ( uiStatus | eGU_SHOW) {
                this->m_uiStatus &= eGU_READY;
                this->m_uiStatus &= eGU_SHOW;
            }
            this->m_uiStatus &= eGU_READY;
		}
		else {
            this->m_uiStatus = eGU_EMPTY;
		}
	}

	if ( root ) {
		cJSON_Delete( root );
	}

	if ( this->m_uiStatus == eGU_EMPTY ) {
        return -1;
	}

	return 0;
}

int UserProcess::Makeup_StartGame( char * pInput, WORD wSize )
{
    MSG_STARTGAME_BRD msg;

	char buff[1024]  = {0};
	char format[256] = 	"{\"potocol\":\"%d\","
                        "\"data\":{"
                        "\"userid\":\"%d\","
                        "\"status\":\"%d\","
						"\"table\":\"%d\","
						"\"seat\":\"%d\"}}";

	sprintf( buff, format,
         msg.m_dwProtocol,
         this->m_uiUserid,
         this->m_uiStatus,
         this->m_wTable,
         this->m_bySeat);

	int len = strlen(buff);
	if ( len < wSize ) {
		memcpy(pInput, buff, len);
	}

	return len;
}

/* 分配牌 */
int UserProcess::Makeup_Alloccards( char * pInput, WORD wSize )
{
   MSG_DISCARDS_BRD msg;

 	char buff[1024]  = {0};
	char cards[1024]  = {0};
	char format[256] = 	"{\"potocol\":\"%d\","
                        "\"data\":{"
                        "\"userid\":\"%d\","
                        "\"count\":\"%d\","
						"\"allocpk\":\"%s\"}}";

    GamePoker * p = m_hold.get_first();
    for ( ; p; )
    {
        char temp[8]  = {0};
        sprintf( temp, "%d", p->m_pkid);
        strcat(cards,temp);
        p = p->get_next();
        if ( p ) {
            strcat(cards,",");
        }
    }

	sprintf( buff, format,
         msg.m_dwProtocol,
         this->m_uiUserid,
         this->m_hold.size(),
         cards);

	int len = strlen(buff);
	if ( len < wSize ) {
		memcpy( pInput, buff, len );
	}
	return len;
}

/* 退出明牌 */
int UserProcess::Parser_Showcard( const char * pInput, WORD wSize )
{
	cJSON * root = NULL;
	root = cJSON_Parse( pInput );
	if ( root == NULL ) {
		return -1;
	}

	// User SshKey;
	cJSON * status = cJSON_GetObjectItem( root, "status" );
	if ( !status ) {
        if ( this->m_uiStatus == eGU_SIT)
		{
		    int uiStatus = status->valueint;
            if ( uiStatus | eGU_SHOW)
            {
                this->m_uiStatus &= eGU_READY;
                this->m_uiStatus &= eGU_SHOW;
            }
            this->m_uiStatus &= eGU_READY;
		}
		else
        {
            this->m_uiStatus = eGU_EMPTY;
		}
	}

	if ( root ) {
		cJSON_Delete( root );
	}

	if ( this->m_uiStatus == eGU_EMPTY ) {
        return -1;
	}

	return 0;
}

int UserProcess::Makeup_Showcard( char * pInput, WORD wSize )
{
    MSG_SHOWCARDS_BRD msg;

	char buff[1024]  = {0};
	char format[256] = 	"{\"potocol\":\"%d\","
                        "\"data\":{"
                        "\"userid\":\"%d\","
                        "\"status\":\"%d\","
						"\"table\":\"%d\","
						"\"seat\":\"%d\"}}";

	sprintf( buff, format,
         msg.m_dwProtocol,
         this->m_uiUserid,
         this->m_uiStatus,
         this->m_wTable,
         this->m_bySeat);

	int len = strlen(buff);
	if ( len < wSize ) {
		memcpy(pInput, buff, len);
	}
	return len;
}


/* 退出明牌 */
int UserProcess::Parser_Called ( const char * pInput, WORD wSize )
{
	cJSON * root = NULL;
	root = cJSON_Parse( pInput );
	if ( root == NULL ) {
		return -1;
	}

	// User SshKey;
	cJSON * status = cJSON_GetObjectItem( root, "status" );
	if ( !status ) {
        if ( this->m_uiStatus == eGU_SIT)
		{
		    int uiStatus = status->valueint;
            if ( uiStatus | eGU_SHOW)
            {
                this->m_uiStatus &= eGU_READY;
                this->m_uiStatus &= eGU_SHOW;
            }
            this->m_uiStatus &= eGU_READY;
		}
		else {
            this->m_uiStatus = eGU_EMPTY;
		}
	}

	if ( root ) {
		cJSON_Delete( root );
	}

	if ( this->m_uiStatus == eGU_EMPTY ) {
        return -1;
	}

	return 0;
}

int UserProcess::Makeup_Called ( char * pInput, WORD wSize )
{
    MSG_CALLBANK_BRD msg;

	char buff[1024]  = {0};
	char format[256] = 	"{\"potocol\":\"%d\","
                        "\"data\":{"
                        "\"userid\":\"%d\","
                        "\"status\":\"%d\","
						"\"table\":\"%d\","
						"\"seat\":\"%d\"}}";

	sprintf( buff, format,
         msg.m_dwProtocol,
         this->m_uiUserid,
         this->m_uiStatus,
         this->m_wTable,
         this->m_bySeat);

	int len = strlen(buff);
	if ( len < wSize ) {
		memcpy(pInput, buff, len);
	}
	return len;
}


/* 退出明牌 */
int UserProcess::Parser_Discards ( const char * pInput, WORD wSize )
{
	cJSON * root = NULL;
	root = cJSON_Parse( pInput );
	if ( root == NULL ) {
		return -1;
	}

	// User SshKey;
	int uiCount = 0;
	cJSON * pk_count = cJSON_GetObjectItem( root, "count" );
	if ( !pk_count ) {
        uiCount = pk_count->valueint;
	}

	// User SshKey;
	cJSON * pk_buff = cJSON_GetObjectItem( root, "poker" );
	if ( !pk_buff ) {
        int nLen = strlen( pk_buff->valuestring );
        this->SetPoker( pk_buff->valuestring, nLen );
	}

	if ( root ) {
		cJSON_Delete( root );
	}

	if ( this->m_uiStatus == eGU_EMPTY ) {
        return -1;
	}

	return 0;
}

int UserProcess::Makeup_Discards ( char * pInput, WORD wSize )
{
    MSG_DISCARDS_BRD msg;

 	char buff[1024]  = {0};
	char cards[1024]  = {0};
	char format[256] = 	"{\"potocol\":\"%d\","
                        "\"data\":{"
                        "\"userid\":\"%d\","
                        "\"count\":\"%d\","
						"\"discard\":\"%s\"}}";

    GamePoker * p = m_just.get_first();
    for ( ; p; )
    {
        char temp[8]  = {0};
        sprintf( temp, "%d", p->m_pkid);
        strcat(cards,temp);
        p = p->get_next();
        if ( p ) {
            strcat(cards,",");
        }
    }

	sprintf( buff, format,
         msg.m_dwProtocol,
         this->m_uiUserid,
         this->m_just.size(),
         cards);

	int len = strlen(buff);
	if ( len < wSize ) {
		memcpy(pInput, buff, len);
	}
	return len;
}

int UserProcess::Makeup_Settlement( char * pInput, WORD wSize )
{

    return 0;
}

int UserProcess::Makeup_Error( int errorno, char * pInput, WORD wSize )
{
    MSG_ERRORNO_BRD msg;

	char buff[1024]  = {0};
	char format[256] = 	"{\"potocol\":\"%d\","
                        "\"data\":{"
                        "\"userid\":\"%d\","
						"\"errno\":\"%d\"}}";

	sprintf( buff, format,
         msg.m_dwProtocol,
         this->m_uiUserid,
         errorno );

	int len = strlen(buff);
	if ( len < wSize ) {
		memcpy(pInput, buff, len);
	}
	return len;
}
