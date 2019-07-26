#include "pch.h"

ThreadHandlerLoginReq::ThreadHandlerLoginReq(std::shared_ptr<Session> _session, std::shared_ptr<Msg::LoginReq> _req, Room* _room)
	: session(_session), req(_req), room(_room)
{

}

ThreadHandlerLoginReq::~ThreadHandlerLoginReq()
{

}

void ThreadHandlerLoginReq::Start()
{
	std::cout << "Login Start called" << std::endl;
	Job job = [sharedThis = shared_from_this()]() { sharedThis->Execute(); };
	DBJobQ::Instance().Queue(job);
}

void ThreadHandlerLoginReq::Execute()
{
	std::cout << "Login Execute called" << std::endl;

	//DB 쓰기 작업
	DBManager::Instance().ExecuteSql((boost::format("INSERT INTO `ztest`.`account` (`accountId`) VALUES ('%1%');") % req->id()).str().c_str());

	Job job = std::bind(&ThreadHandlerLoginReq::PostExecute, shared_from_this());
	room->Queue(job);
}

void ThreadHandlerLoginReq::PostExecute()
{
	std::cout << "Login PostExecute called" << std::endl;
	TCP_Server::instance().CreatePlayer(session->ID, req->id());
}

ThreadHandlerChatReq::ThreadHandlerChatReq(std::shared_ptr<Session> _session, std::shared_ptr<Msg::ChatReq> _req, Room * _room)
	: session(_session), req(_req), room(_room)
{
}

ThreadHandlerChatReq::~ThreadHandlerChatReq()
{
}

void ThreadHandlerChatReq::Start()
{
	std::cout << "Chat Start called" << std::endl;
	Job job = [sharedThis = shared_from_this()]() { sharedThis->Execute(); };
	DBJobQ::Instance().Queue(job);
}

void ThreadHandlerChatReq::Execute()
{
	std::cout << "Chat Execute called" << std::endl;

	auto player = TCP_Server::instance().GetPlayer(session->ID);
	if (player == nullptr)
	{
		std::cout << "GetPlayer is nullptr" << std::endl;
		return;
	}
	//DB 쓰기 작업
	DBManager::Instance().ExecuteSql((boost::format("INSERT INTO `ztest`.`chatting` (`accountId`, `message`) VALUES ('%1%', '%2%');") % player->nickname_ % req->msg()).str().c_str());

	Job job = std::bind(&ThreadHandlerChatReq::PostExecute, shared_from_this());
	room->Queue(job);
}

void ThreadHandlerChatReq::PostExecute()
{
	std::cout << "Chat PostExecute called" << std::endl;

	auto player = TCP_Server::instance().GetPlayer(session->ID);
	auto room = TCP_Server::instance().roomManager.GetRoom(session->roomId);

	//챗 푸쉬
	std::stringstream stream;
	stream << "[" << player->nickname_ << "] : " << req->msg() << std::endl;

	std::cout << stream.str();
	room->BroadCastToRoom(stream.str());
}
