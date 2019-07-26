#pragma once
#include "pch.h"
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <string>
#include <thread>
#include <stdio.h>
#include <windows.h>

const unsigned short PORT_NUMBER = 31400;
using namespace boost::asio;

class TCP_Client
{
	enum State
	{
		EnterRoom,
		Auth,
		Wait,
		Chat
	};

public:
	TCP_Client(io_service& io_service)
		:m_io_service(io_service), m_socket(io_service), m_nSeqNumber(0)
	{
	}

	~TCP_Client()
	{
		worker->join();
	}

	void Connect(boost::asio::ip::tcp::endpoint& endpoint)
	{
		m_socket.async_connect(endpoint,
			boost::bind(&TCP_Client::handle_connect,
			this,
			boost::asio::placeholders::error)
		);
	}

public: // internal methods.
	void postWrite()
	{
		while (true)
		{
			if (!m_socket.is_open())
			{
				std::cout << "Socket closed";
				break;
			}
			
			switch (state)
			{
				case TCP_Client::EnterRoom:
				{
					std::cout << "Enter Room -> ";
					int roomId = 0;
					std::cin >> roomId;

					auto req = std::make_shared<Msg::EnterRoomReq>();
					req->set_roomid(roomId);
					SerializePacket(Msg::EnterRoom, req);

					state = Auth;
				}
				break;
				case TCP_Client::Auth:
				{
					std::cout << "Login 아이디를 입력 -> ";
					std::string id;
					std::cin >> id;

					auto req = std::make_shared<Msg::LoginReq>();
					req->set_id(id);

					SerializePacket(Msg::Login, req);
					
					state = Wait;
				}
				break;
				case State::Wait:
				{
					state = Chat;
					std::cin.ignore();
					continue;;
				}
				break;
				case TCP_Client::Chat:
				{
					state = Chat;
					std::cout << "Input Chat -> ";
					//std::string msg;
					//std::cin >> msg;
					char msg[120];
					gets_s(msg);

					auto req = std::make_shared<Msg::ChatReq>();
					req->set_msg(msg);

					SerializePacket(Msg::Chat, req);
				}
					break;
				default:
					break;
			}

			boost::asio::async_write(m_socket, boost::asio::buffer(m_writeMessageBuffer, m_writeMessageSize),
				boost::bind(&TCP_Client::handle_write, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred)
			);
		}
		//postReceive();
	}

	void SerializePacket(Msg::MessageId pktId, MessagePtr pkt)
	{
		int encodedSize = pkt->ByteSize();

		int id = (int)pktId;

		/*		char bufferLength[4];
				char bufferPktId[4];

				std::memcpy(bufferPktId, &pktId, 4);
				std::memcpy(bufferLength, &encodedSize, 4);*/

		char* resultBuffer = new char[encodedSize + 8];
		std::memcpy(resultBuffer, &id, 4);
		std::memcpy(resultBuffer + 4, &encodedSize, 4);
		pkt->SerializeToArray(resultBuffer + 8, encodedSize);

		m_writeMessageBuffer = resultBuffer;
		m_writeMessageSize = encodedSize + 8; //헤더 4 + 4 크기 추가
	}

	void postReceive()
	{
		memset(&m_receiveBuffer, 0, sizeof(m_receiveBuffer));

		//boost::asio::async_read(m_socket, boost::asio::buffer(m_receiveBuffer), boost::bind(&TCP_Client::handle_receive, this,
		//	boost::asio::placeholders::error,
		//	boost::asio::placeholders::bytes_transferred));

		m_socket.async_read_some(boost::asio::buffer(m_receiveBuffer),
			boost::bind(&TCP_Client::handle_receive, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred)
		);
	}

	void handle_connect(const boost::system::error_code& error)
	{
		if (error)
			std::cout << "connect failed" << std::endl;
		else
		{
			std::cout << "connected" << std::endl;

			worker = new std::thread(std::bind(&TCP_Client::postWrite, this));
			postReceive();
		}
	}

	void handle_write(const  boost::system::error_code &error, size_t sentBytes)
	{
		//postReceive();
	}

	void handle_receive(const boost::system::error_code &error, size_t sentBytes)
	{
		if (error)
			if (error == error::eof)
				std::cout << "Disconnected" << std::endl;
			else
				std::cout << "ErrNo :" << error.value() << " " << "Error message :" << error.message() << std::endl;
		else
		{
			std::cout << std::endl;
			const std::string strRecvMessage = m_receiveBuffer.data();
			std::cout << strRecvMessage << std::endl;
			std::cout << "Input Chat -> ";

			postReceive();
		}

	}
private: // internal variables
	io_service& m_io_service;
	ip::tcp::socket m_socket;

	int m_nSeqNumber;
	std::array<char, 128> m_receiveBuffer;
	//std::string m_writeMessage;
	//std::array<char, 1024*32> m_writeMessage;
	char* m_writeMessageBuffer;
	int m_writeMessageSize;

	State state = EnterRoom;

	std::thread *worker = nullptr;
};

int main()
{
	io_service io_service;
	std::string ip_addr = "10.25.20.10";
	//std::cin >> ip_addr;
	ip::tcp::endpoint endpoint(ip::address::from_string(ip_addr.c_str()), PORT_NUMBER);

	TCP_Client client(io_service);

	client.Connect(endpoint);
	io_service.run();

	getchar();
	return 0;
}
