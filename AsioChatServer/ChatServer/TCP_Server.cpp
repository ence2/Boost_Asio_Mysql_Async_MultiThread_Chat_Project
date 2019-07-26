#include "pch.h"
#include "msg.pb.h"

void TCP_Server::StartAccept()
{
	std::cout << "waiting client..." << std::endl;
	std::shared_ptr<Session> session = std::make_shared<Session>(*ioService);
	//auto session=new Session(*ioService);
	session->ID = seqNumber;
	sessions.insert(std::make_pair(seqNumber++, session));
	acceptor->async_accept(session->Socket(),
		boost::bind(&TCP_Server::handle_accept, this, session, boost::asio::placeholders::error));
}

void TCP_Server::handle_accept(std::shared_ptr<Session> session, const boost::system::error_code& error)
{
	if (!error)
	{
		std::cout << "client connection, count -> " << sessions.size() << std::endl;

		session->PostReceive();

		std::cout << "waiting client..." << std::endl;
		std::shared_ptr<Session> session = std::make_shared<Session>(*ioService);
		//auto session=new Session(*ioService);
		session->ID=seqNumber;
		sessions.insert(std::make_pair(seqNumber++, session));
		acceptor->async_accept(session->Socket(),
			boost::bind(&TCP_Server::handle_accept, this, session, boost::asio::placeholders::error));
	}
}

void TCP_Server::initMessageHandlers()
{
	msgPrototype_.Add(Msg::EnterRoom, std::shared_ptr<Msg::EnterRoomReq>(new Msg::EnterRoomReq()));
	msgPrototype_.Add(Msg::Login, std::shared_ptr<Msg::LoginReq>(new Msg::LoginReq()));
	msgPrototype_.Add(Msg::Chat, std::shared_ptr<Msg::ChatReq>(new Msg::ChatReq()));

	dispatcher_.AddHandler(Msg::EnterRoom, [this](auto s, auto m) { this->OnMessage_EnterRoom(s, m); });
}

TCP_Server::TCP_Server() : threadPoolJob(10), threadPoolDB(10)
{
	initMessageHandlers();
	//sessions = new std::map<int, Session *>();
	//sessions = new std::map<int, std::shared_ptr<Session>>();
	ioService = new boost::asio::io_service();
	acceptor = new boost::asio::ip::tcp::acceptor(*ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT_NUMBER));
	//session = nullptr;
	StartAccept();
}

TCP_Server::~TCP_Server()
{
	sessions.clear();
}

TCP_Server& TCP_Server::instance()
{
	static TCP_Server _instance;

	return _instance;
}

void TCP_Server::RemoveSession(int ID)
{
	//auto s = (sessions)[ID];
	auto it = sessions.find(ID);
	auto room = roomManager.GetRoom(it->second->roomId);
	room->DeleteSession(it->second);

	sessions.erase(ID);
	players.erase(ID);
	//delete s;
}

std::shared_ptr<PlayerInfo> TCP_Server::GetPlayer(int sessionID)
{
	return players[sessionID];
}

void TCP_Server::CreatePlayer(int sessionID, std::string nickname)
{
	players.insert(std::make_pair(sessionID, std::make_shared<PlayerInfo>(nickname)));
}

void TCP_Server::Run()
{
	ioService->run();
}

void TCP_Server::OnMessage_EnterRoom(std::shared_ptr<Session> session, Protocol::MessagePtr msg)
{
	std::shared_ptr<Msg::EnterRoomReq> req = std::static_pointer_cast<Msg::EnterRoomReq, Protocol::MessageBase>(msg);

	auto room = roomManager.GetRoom(req->roomid());
	room->InsertSession(session);

	session->roomId = req->roomid();

	//std::cout << "Enter room -> " << req->roomid() << ", sessionID -> " << session->ID << std::endl;
}
