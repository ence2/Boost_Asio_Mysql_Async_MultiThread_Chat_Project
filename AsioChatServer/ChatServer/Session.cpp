#pragma once
#include "pch.h"

void Session::handle_write(const boost::system::error_code &, size_t)
{

}

void Session::handle_receive(const boost::system::error_code& error, size_t bytes_transferred)
{
	if (error)
	{
		if (error == boost::asio::error::eof)
		{
			std::cout << "클라이언트와 연결이 끈어졌습니다." << std::endl;
		}
		else
		{
			std::cout << "error No : " << error.value() << " error Message : " << error.message() << std::endl;
		}

		TCP_Server::instance().RemoveSession(ID);
	}
	else
	{
		const char* recvMessage = receiveBuffer.data();
		//std::cout << "Message by client : " << recvMessage << ", size : " << bytes_transferred << std::endl;

		Msg::MessageId pktId;
		int pktLength;
		std::memcpy(&pktId, recvMessage, 4);
		std::memcpy(&pktLength, recvMessage + 4, 4);

		//메세지 파싱
		auto req = TCP_Server::instance().msgPrototype_.Get(pktId);
		req->ParseFromArray(recvMessage + 8, pktLength);

		Protocol::Dispatcher<std::shared_ptr<Session>>::HandlerFunction handler;

		//핸들러가 없을경우 방으로
		if (false == TCP_Server::instance().dispatcher_.GetHandler(pktId, handler))
		{
			Job job = std::bind(&RoomManager::OnMessageToRoom, &TCP_Server::instance().roomManager, shared_from_this(), pktId, req);
			auto room = TCP_Server::instance().roomManager.GetRoom(this->roomId);
			room->Queue(job);
			PostReceive();
			return;
		}

		handler(shared_from_this(), req);

		PostReceive();
	}
}

Session::Session(boost::asio::io_service& ioService) : socket(ioService)
{
	
}

boost::asio::ip::tcp::socket& Session::Socket()
{
	return socket;
}

void Session::PostReceive()
{
	memset(&receiveBuffer, '\0', sizeof(receiveBuffer));

	//socket.async_read_some
	//(
	//	boost::asio::buffer(receiveBuffer),
	//	boost::bind(&Session::handle_receive,
	//	this,
	//	boost::asio::placeholders::error,
	//	boost::asio::placeholders::bytes_transferred)
	//);

	socket.async_receive
	(
		boost::asio::buffer(receiveBuffer),
		boost::bind(&Session::handle_receive,
		shared_from_this(),
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred)
	);

	//boost::asio::async_read(socket, boost::asio::buffer(receiveBuffer), boost::bind(&Session::handle_receive, this,
	//	boost::asio::placeholders::error,
	//	boost::asio::placeholders::bytes_transferred));
}