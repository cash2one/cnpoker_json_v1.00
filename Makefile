CC = g++
CFLAGS = -g -fPIC -D_FILELINE -Wno-deprecated 
#HOME = /mnt/Shared/moche 
HOME = /mnt/Shared/cnpoker_json_v1.00

MYSQLINC = /usr/include/mysql
MYSQLLIB = -L /usr/lib64/mysql -l mysqlclient -lz -lm

INC = -I $(HOME)/Utility \
	  -I $(HOME)/Common  \
	  -I $(HOME)/Network \
	  -I $(HOME)/Public \
	  -I $(HOME)/AgentSrv \
	  -I $(HOME)/HyMysql \
	  -I $(HOME)/DBSrv \
	  -I $(MYSQLINC) 

PublicObjs 		= Public/InfoParser.o \
				  Public/JsonParser.o \
				  Public/MsgProcess.o \
				  Public/Yond_drng.o \
				  Public/Yond_json.o \
				  Public/Yond_string.o \
				  Public/Yond_md5.o 
	  
UtilityObjs 	= Utility/Yond_mutex.o \
				  Utility/Yond_ini.o \
				  Utility/Yond_thread.o \
				  Utility/Yond_thread_pool.o \
				  Utility/ObjKeyGenerator.o

NetworkObjs 	= Network/Acceptor.o \
				  Network/Connector.o \
				  Network/IOCPServer.o \
				  Network/NetworkObject.o \
				  Network/Session.o \
				  Network/SessionList.o \
				  Network/SessionPool.o \
				  Network/SocketOpt.o \
				  Network/SyncHandler.o
		  
AgentServerObjs = AgentSrv/AgentMain.o \
				  AgentSrv/AgentFactory.o \
				  AgentSrv/AgentServer.o \
				  AgentSrv/GameServerSession.o \
				  AgentSrv/ServerSession.o \
				  AgentSrv/TempServerSession.o \
				  AgentSrv/UserSession.o \
				  AgentSrv/Handler_FromGameServer.o \
				  AgentSrv/PacketHandler.o \
				  AgentSrv/GameServerSession.o \
				  AgentSrv/RootID.o \
				  AgentSrv/RootidManager.o
		  
GameServerObjs 	= GameSrv/AgentServerSession.o \
				  GameSrv/DBServerSession.o \
				  GameSrv/GameFactory.o \
				  GameSrv/GameMain.o \
				  GameSrv/GameServer.o \
				  GameSrv/GamePoker.o \
				  GameSrv/GamePokerList.o \
				  GameSrv/GameRoom.o \
				  GameSrv/GameTable.o \
				  GameSrv/GameUser.o \
				  GameSrv/GameUserList.o \
				  GameSrv/Handler_FromAgentServer.o \
				  GameSrv/Handler_FromDBServer.o \
				  GameSrv/PacketHandler.o \
				  GameSrv/ServerSession.o \
				  GameSrv/GameDealer.o \
				  GameSrv/UserProcess.o

DBServerObjs 	= HyMysql/HyDatabase.o \
				  HyMysql/IDBCInterface.o \
				  HyMysql/IMysql.o \
				  HyMysql/QueryExecuteProcessor.o \
				  HyMysql/QueryResult.o \
				  DBSrv/DBConnectDir.o \
				  DBSrv/DBFactory.o \
				  DBSrv/DBMain.o \
				  DBSrv/DBServer.o \
				  DBSrv/GameQuery.o \
				  DBSrv/GameServerSession.o \
				  DBSrv/Handler_FromGameServer.o \
				  DBSrv/LoginQuery.o \
				  DBSrv/PacketHandler.o \
				  DBSrv/ServerSession.o \
				  DBSrv/TempServerSession.o

#LoginServerObjs = LoginSrv/ServerSession.o \
#				  LoginSrv/TempServerSession.o \
#				  LoginSrv/AgentServerSession.o \
#				  LoginSrv/DBServerSession.o \
#				  LoginSrv/LoginMain.o \
#				  LoginSrv/LoginFactory.o \
#				  LoginSrv/LoginServer.o \
#				  LoginSrv/LoginUser.o \
#				  LoginSrv/LoginUserManager.o \
#				  LoginSrv/PacketHandler.o \
#				  LoginSrv/AllocServer.o \
#				  LoginSrv/Handler_FromAgentServer.o \
#				  LoginSrv/Handler_FromDBServer.o 
				  
BINDIR = bin

all: checkbin $(BINDIR)/AgentServer $(BINDIR)/GameServer $(BINDIR)/DBServer
#$(BINDIR)/DBServer 

$(BINDIR)/AgentServer: $(UtilityObjs) $(PublicObjs) $(NetworkObjs) $(AgentServerObjs)
	$(CC) -g $^ -o $@ -pthread

$(BINDIR)/GameServer: $(UtilityObjs) $(PublicObjs) $(NetworkObjs) $(GameServerObjs)
	$(CC) -g $^ -o $@ -pthread

$(BINDIR)/DBServer: $(UtilityObjs) $(PublicObjs) $(NetworkObjs) $(DBServerObjs)
	$(CC) -g $(MYSQLLIB) $^ -o $@ -pthread

.SUFFIXES: .c .o .cpp
.cpp.o:
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

.PHONY: checkbin
checkbin:
	test -d "${BINDIR}" || mkdir $(BINDIR)

.PHONY:	clean cleanGame
clean:
	rm -f Network/*.o
	rm -f Utility/*.o
	rm -f Public/*.o
	rm -f AgentSrv/*.o
	rm -f $(BINDIR)/AgentServer

cleanAll:
	rm -f Network/*.o
	rm -f Utility/*.o
	rm -f Public/*.o
	rm -f HyMysql/*.o
	rm -f AgentSrv/*.o
	rm -f GameSrv/*.o
	rm -f DBSrv/*.o
	rm -f $(BINDIR)/AgentServer
	rm -f $(BINDIR)/GameServer
	rm -f $(BINDIR)/DBServer	
#	rm -f $(BINDIR)/LoginServer
	
cleanGame:
	rm -f Network/*.o
	rm -f Utility/*.o
	rm -f GameSrv/*.o
	rm -f $(BINDIR)/GameServer
	
#cleanLogin:
#	rm -f LoginSrv/*.o
#	rm -f $(BINDIR)/LoginServer

cleanDB:
	rm -f HyMysql/*.o
	rm -f DBSrv/*.o
	rm -f $(BINDIR)/DBServer	
