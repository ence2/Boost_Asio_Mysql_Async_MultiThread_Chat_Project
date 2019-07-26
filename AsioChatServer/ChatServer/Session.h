#pragma once
#include "pch.h"

class Session : public std::enable_shared_from_this<Session>
{
private:
	boost::asio::ip::tcp::socket socket;
	std::string writeMessage;
	std::array<char, 64 * 1024> receiveBuffer;

	void handle_write(const boost::system::error_code&, size_t);

	void handle_receive(const boost::system::error_code& error, size_t bytes_transferred);

public:
	Session(boost::asio::io_service& ioService);

	boost::asio::ip::tcp::socket& Socket();

	void PostReceive();

	int ID;
	int roomId;
};