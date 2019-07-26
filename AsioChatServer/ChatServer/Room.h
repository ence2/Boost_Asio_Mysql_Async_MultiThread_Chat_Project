#pragma once
#include "pch.h"

class Room : public JobQueueThreading
{
	int roomId_;
	Protocol::Dispatcher<std::shared_ptr<Session>> dispatcher_;
	std::list<std::shared_ptr<Session>> sessions;

public:
	Room(int);
	~Room();

	void OnMessage_Login(std::shared_ptr<Session> session, Protocol::MessagePtr msg);
	void OnMessage_Chat(std::shared_ptr<Session> session, Protocol::MessagePtr msg);

	void DispatchMessage(std::shared_ptr<Session> session, Msg::MessageId msgId, Protocol::MessagePtr msg);

	void InsertSession(std::shared_ptr<Session>);
	void DeleteSession(std::shared_ptr<Session>);

	void BroadCastToRoom(std::string str)
	{
		for (auto s : sessions)
		{
			boost::asio::write(s->Socket(), boost::asio::buffer(str));
		}
	}
};

///////////////////////////////////////////////////// RoomManager /////////////////////////////////////////////////////////////

class RoomManager
{
private:

public:
	RoomManager();
	~RoomManager();

	std::map<int, Room*> rooms;

	void OnMessageToRoom(std::shared_ptr<Session> session, Msg::MessageId msgId, Protocol::MessagePtr msg);

	Room* GetRoom(int roomId);
};

