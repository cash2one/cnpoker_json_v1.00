#include "GameServer.h"

int main(int argc, char ** argv) 
{
	g_GameServer = new GameServer;
	g_GameServer->Init();
	
	while(true) {
		Sleep(100);
		g_GameServer->Update(0);
	}
	
	return 0;
}




