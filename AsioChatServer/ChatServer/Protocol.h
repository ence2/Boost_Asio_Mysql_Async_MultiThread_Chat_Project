#pragma once
#include "pch.h"

namespace Protocol
{
	typedef google::protobuf::MessageLite MessageBase;
	typedef std::shared_ptr<MessageBase> MessagePtr;

	class Prototype
	{
	public:
		Prototype()
		{
		}

		~Prototype()
		{
		}

		typedef std::map<unsigned short, MessagePtr> MsgMap;

		bool Add(unsigned short msgId, MessagePtr msg)
		{
			std::pair<MsgMap::iterator, bool > ib = map_.insert(MsgMap::value_type(msgId, msg));
			assert(ib.second);
			return ib.second;
		}

		MessagePtr Get(unsigned short msgId)
		{
			MsgMap::iterator i = map_.find(msgId);
			if (i == map_.end())
			{
				return MessagePtr();
			}

			return MessagePtr(i->second->New());
		}

	private:
		MsgMap map_;
	};

	template<typename _TID>
	class Dispatcher
	{
	public:
		Dispatcher()
		{

		}

		~Dispatcher()
		{
		}

		typedef std::function<void(_TID, MessagePtr)> HandlerFunction;

		void AddHandler(unsigned short msgId, HandlerFunction handler)
		{
			auto ib = handlerMap_.insert(HandlerMap::value_type(msgId, handler));
			if (false == ib.second)
			{
				assert(!"핸들러 중복 등록했음");
			}
		}

		bool RemoveHandler(unsigned short msgId)
		{
			auto i = handlerMap_.find(msgId);
			if (i != handlerMap_.end())
			{
				handlerMap_.erase(i);
				return true;
			}
			return false;
		}

		bool GetHandler(unsigned short msgId, HandlerFunction& handler)
		{
			auto i = handlerMap_.find(msgId);
			if (i != handlerMap_.end())
			{
				handler = i->second;
				return true;
			}
			return false;
		}

		void Clear()
		{
			handlerMap_.clear();
		}

		typedef std::unordered_map<unsigned short, HandlerFunction> HandlerMap;

	private:
		HandlerMap handlerMap_;
	};
}