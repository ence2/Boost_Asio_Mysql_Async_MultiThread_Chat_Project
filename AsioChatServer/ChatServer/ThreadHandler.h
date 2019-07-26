#pragma once
#include "pch.h"
#include "Room.h"

class ThreadHandlerLoginReq : public std::enable_shared_from_this<ThreadHandlerLoginReq>
{
public:
	ThreadHandlerLoginReq(std::shared_ptr<Session> _session, std::shared_ptr<Msg::LoginReq> _req, Room* _room);

	//ThreadHandler(std::shared_ptr<Session> _session, std::shared_ptr<Msg::ChatReq> _req, Room* _room);

	~ThreadHandlerLoginReq();

	void Start();

	void Execute();

	void PostExecute();

	//void StartChat();

	//void ExecuteChat();

	//void PostExecuteChat();

private:
	std::shared_ptr<Session> session;
	std::shared_ptr<Msg::LoginReq> req;
	Room* room;
};

class ThreadHandlerChatReq : public std::enable_shared_from_this<ThreadHandlerChatReq>
{
public:
	ThreadHandlerChatReq(std::shared_ptr<Session> _session, std::shared_ptr<Msg::ChatReq> _req, Room* _room);

	//ThreadHandler(std::shared_ptr<Session> _session, std::shared_ptr<Msg::ChatReq> _req, Room* _room);

	~ThreadHandlerChatReq();

	void Start();

	void Execute();

	void PostExecute();

	//void StartChat();

	//void ExecuteChat();

	//void PostExecuteChat();

private:
	std::shared_ptr<Session> session;
	std::shared_ptr<Msg::ChatReq> req;
	Room* room;
};
