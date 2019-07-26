#include "pch.h"

RoomManager::RoomManager()
{
	//rooms.insert(std::make_pair(1, new Room()));
}

RoomManager::~RoomManager()
{

}

void RoomManager::OnMessageToRoom(std::shared_ptr<Session> session, Msg::MessageId msgId, Protocol::MessagePtr msg)
{
	GetRoom(session->roomId)->DispatchMessage(session, msgId, msg);
}

Room* RoomManager::GetRoom(int roomId)
{
	auto result = rooms.find(roomId);

	//없을 경우 생성
	if (result == rooms.end())
	{
		auto it = rooms.insert(std::make_pair(roomId, new Room(roomId)));

		return rooms[roomId];
	}
	else
	{
		return result->second;
	}
}

///////////////////////////////////////////////////// Room /////////////////////////////////////////////////////////////
Room::Room(int roomId) : JobQueueThreading("Room")
{
	roomId_ = roomId;
	dispatcher_.AddHandler(Msg::Login, std::bind(&Room::OnMessage_Login, this, std::placeholders::_1, std::placeholders::_2));
	dispatcher_.AddHandler(Msg::Chat, std::bind(&Room::OnMessage_Chat, this, std::placeholders::_1, std::placeholders::_2));

	std::cout << "New Room Created, RoomId -> " << roomId_ << std::endl;
}

Room::~Room()
{
}

void Room::OnMessage_Login(std::shared_ptr<Session> session, Protocol::MessagePtr msg)
{
	std::shared_ptr<Msg::LoginReq> req = std::static_pointer_cast<Msg::LoginReq, Protocol::MessageBase>(msg);

	std::shared_ptr<ThreadHandlerLoginReq> cmd(new ThreadHandlerLoginReq(session, req, this));
	cmd->Start();
}

void Room::OnMessage_Chat(std::shared_ptr<Session> session, Protocol::MessagePtr msg)
{
	std::shared_ptr<Msg::ChatReq> req = std::static_pointer_cast<Msg::ChatReq, Protocol::MessageBase>(msg);

	//std::cout << "[" << session->accountId << "] : " << req->msg() << std::endl;

	std::shared_ptr<ThreadHandlerChatReq> cmd(new ThreadHandlerChatReq(session, req, this));
	cmd->Start();
}

void Room::DispatchMessage(std::shared_ptr<Session> session, Msg::MessageId msgId, Protocol::MessagePtr msg)
{
	Protocol::Dispatcher<std::shared_ptr<Session>>::HandlerFunction handler;
	dispatcher_.GetHandler(msgId, handler);

	handler(session, msg);
}

void Room::InsertSession(std::shared_ptr<Session> s)
{
	sessions.push_back(s);
	std::cout << "Enter room -> " << roomId_ << ", sessionID -> " << s->ID << ", Total user -> " << sessions.size() << std::endl;
}

void Room::DeleteSession(std::shared_ptr<Session> s)
{
	auto it = find(sessions.begin(), sessions.end(), s);
	if (it == sessions.end())
		return;

	sessions.erase(it);

	std::cout << "Leave room -> " << roomId_ << ", sessionID -> " << s->ID << ", Total user -> " << sessions.size() << std::endl;
}
