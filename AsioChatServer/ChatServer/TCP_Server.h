#pragma once
#include "pch.h"

class TCP_Server
{
private:
	void StartAccept();
	void handle_accept(std::shared_ptr<Session> session, const boost::system::error_code& error);
	void initMessageHandlers();

	int seqNumber = 0;
	boost::asio::ip::tcp::acceptor *acceptor;
	//std::map<int, Session*> sessions;
	std::map<int, std::shared_ptr<Session>> sessions;
	std::map<int, std::shared_ptr<PlayerInfo>> players;
	boost::asio::io_service *ioService;

public:
	TCP_Server();
	~TCP_Server();

	static TCP_Server &instance();

	Protocol::Prototype msgPrototype_;
	
	Protocol::Dispatcher<std::shared_ptr<Session>> dispatcher_;

	RoomManager roomManager;

	void RemoveSession(int ID);

	std::shared_ptr<PlayerInfo> GetPlayer(int sessionID);

	void CreatePlayer(int sessionID, std::string nickname);

	void Run();

	void OnMessage_EnterRoom(std::shared_ptr<Session> session, Protocol::MessagePtr msg);

	ThreadPool threadPoolJob;
	ThreadPool threadPoolDB;
};

