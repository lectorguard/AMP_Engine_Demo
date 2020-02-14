// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once

#include "event.h"
#include "Memory/AMP_HashMap.h"
#include "list"
#include "memory"
#include "Text.h"
#include "functional"
#include "typeinfo"
#include "Static/TimeManager.h"



namespace amp
{
	struct TimeEvent {
		
		TimeEvent() {
			timeId = TIME::currentTimeInNanos();
		};
		TimeEvent(const TimeEvent& t) = default;
		TimeEvent(TimeEvent&&) = default;

		
		void calculatePublishTime() {
			publishTime = (int64_t)(TimeInSeconds * NANOS_IN_SECOND) + TIME::currentTimeInNanos();
		}

		template<typename Class, typename ... Args>
		void init(float TimeInSeconds, bool IsLooped, void(Class::* f)(Args ...), Class* ref, Args ... args) {
			this->CalledFunction = std::bind(f, ref, std::forward<Args>(args) ...);
			this->TimeInSeconds = TimeInSeconds;
			this->IsLooped = IsLooped;
			calculatePublishTime();
		}

		bool operator==(TimeEvent Rhs) {
			return this->timeId == Rhs.timeId;
		}

		float TimeInSeconds = 0.0f;
		bool IsLooped = false;
		std::function<void()> CalledFunction;
		int64_t timeId;
	private:
		friend class amp::AMP_Engine;
		friend class EventSystem;
		int64_t publishTime = 0;

	};



	class EventSystem {
	
	public:
		EventSystem(const EventSystem&) = delete;
		EventSystem(EventSystem&&) = delete;
	
		EventSystem() {};
		using  callback_t = typename std::function<void()>;
		using  callback_container_t = typename std::list<callback_t>;
		using  handle_t = typename callback_container_t::iterator;
	
		template<typename T>
		size_t getTypeID() {
			return typeid(T).hash_code();
		}
		
		//0 Parameters
		template<typename Class>
		inline auto subscribeEvent(TEXT eventName, void(Class::* f)(), Class* ref) {
			if (auto result = eventMap.tryFind_unique(eventName.getHash()))
			{
				if ((*result)->types.size() != 0)throw "Added Function has wrong Number of Parameters";
				std::function<void()> fptr = std::bind(f, ref);
				return (*result)->subscribe(fptr);
			}
			else
			{
				std::unique_ptr<event> MyEvent = std::make_unique<event>();
				std::function<void()> fptr = std::bind(f, ref);
				auto itr = MyEvent.get()->subscribe(fptr);
				eventMap.add_unique(eventName.getHash(), std::move(MyEvent));
				return itr;
			}
		}
	
		//1 Parameters
		template<typename Class,typename OneParam>
		auto subscribeEvent(TEXT eventName,void(Class::*f)(OneParam),Class* ref) {
			if (auto result = eventMap.tryFind_unique(eventName.getHash()))
			{
	 			if ((*result)->types.size() != 1)throw "Added Function has wrong Number of Parameters";
	 			if ((*result)->types[0] != getTypeID<OneParam>())throw "Function Parameter has wrong type";
				auto* helper = (eventOneParam<OneParam>*)(*result);
				std::function<void()> fptr = std::bind(f, ref, std::cref(helper->param1));
				return (*result)->subscribe(fptr);
			}
			else
			{
				std::unique_ptr<event> MyEvent = std::make_unique<eventOneParam<OneParam>>();
				//Check Type of Param
				MyEvent.get()->types.push_back(getTypeID<OneParam>());
				auto& param1 = ((eventOneParam<OneParam>*)(MyEvent.get()))->param1;
				std::function<void()> fptr = std::bind(f, ref, std::cref(param1));
				auto itr = MyEvent.get()->subscribe(fptr);
				eventMap.add_unique(eventName.getHash(), std::move(MyEvent));
				return itr;
			}
		}
	
		//2 Parameters
		template<typename Class, typename OneParam,typename TwoParam>
		inline auto subscribeEvent(TEXT eventName, void(Class::* f)(OneParam,TwoParam), Class* ref) {
			if (auto result = eventMap.tryFind_unique(eventName.getHash()))
			{
				if ((*result)->types.size() != 2)throw "Added Function has wrong Number of Parameters";
				if ((*result)->types[0] != getTypeID<OneParam>() ||
					(*result)->types[1] != getTypeID<TwoParam>())throw "Function Parameter has wrong type";
				auto* helper = (eventTwoParam<OneParam,TwoParam>*)(*result);
				std::function<void()> fptr = std::bind(f, ref, std::cref(helper->param1),std::cref(helper->param2));
				return (*result)->subscribe(fptr);
			}
			else
			{
				std::unique_ptr<event> MyEvent = std::make_unique<eventTwoParam<OneParam,TwoParam>>();
				//Set Param Types
				MyEvent.get()->types.push_back(getTypeID<OneParam>());
				MyEvent.get()->types.push_back(getTypeID<TwoParam>());
				auto* eventPtr = (eventTwoParam<OneParam,TwoParam>*)(MyEvent.get());
				auto& param1 = eventPtr->param1;
				auto& param2 = eventPtr->param2;
				std::function<void()> fptr = std::bind(f, ref, std::cref(param1),std::cref(param2));
				auto itr = MyEvent.get()->subscribe(fptr);
				eventMap.add_unique(eventName.getHash(), std::move(MyEvent));
				return itr;
			}
		}
	
		//3 Parameters
		template<typename Class, typename OneParam, typename TwoParam,typename ThreeParam>
		inline auto subscribeEvent(TEXT eventName, void(Class::* f)(OneParam,TwoParam,ThreeParam), Class* ref) {
			if (auto result = eventMap.tryFind_unique(eventName.getHash()))
			{
				if ((*result)->types.size() != 3)throw "Added Function has wrong Number of Parameters";
				if ((*result)->types[0] != getTypeID<OneParam>() ||
					(*result)->types[1] != getTypeID<TwoParam>() ||
					(*result)->types[2] != getTypeID<ThreeParam>())throw "Function Parameter has wrong type";
				auto* helper = (eventThreeParam<OneParam,TwoParam,ThreeParam>*)(*result);
				std::function<void()> fptr = std::bind(f, ref, std::cref(helper->param1), std::cref(helper->param2),std::cref(helper->param3));
				return (*result)->subscribe(fptr);
			}
			else
			{
				std::unique_ptr<event> MyEvent = std::make_unique<eventThreeParam<OneParam,TwoParam,ThreeParam>>();
				//Set Param Types
				MyEvent.get()->types.push_back(getTypeID<OneParam>());
				MyEvent.get()->types.push_back(getTypeID<TwoParam>());
				MyEvent.get()->types.push_back(getTypeID<ThreeParam>());
				auto* eventPtr = (eventThreeParam<OneParam,TwoParam,ThreeParam>*)(MyEvent.get());
				auto& param1 = eventPtr->param1;
				auto& param2 = eventPtr->param2;
				auto& param3 = eventPtr->param3;
				std::function<void()> fptr = std::bind(f, ref, std::cref(param1), std::cref(param2),std::cref(param3));
				auto itr = MyEvent.get()->subscribe(fptr);
				eventMap.add_unique(eventName.getHash(), std::move(MyEvent));
				return itr;
			}
		}
	
		void unsubscribeEvent(TEXT eventName,handle_t retValueFromSubscribe) {
			if (auto result = eventMap.tryFind_unique(eventName.getHash()))
			{
				(*result)->unsubscribe(retValueFromSubscribe);
			}
		}
	
		//0 parameter
		void publishEvent(TEXT eventName) {
			if (auto result = eventMap.tryFind_unique(eventName.getHash()))
			{
				if ((*result)->types.size() != 0)throw "Publish Function has wrong Number of Parameters";
				(*result)->fire();
			}
		}
	
		//1 parameter
		template<typename OneParam>
		void publishEvent(TEXT eventName,OneParam param1) {
			if (auto result = eventMap.tryFind_unique(eventName.getHash()))
			{
	 			if ((*result)->types.size() != 1)throw "Publish Function has wrong Number of Parameters";
	 			if ((*result)->types[0] != getTypeID<OneParam>())throw "Function Parameter has wrong type";
				auto casted = (eventOneParam<OneParam>*)(*result);
				casted->param1 = param1;
				(*result)->fire();	
			}
		}
	
		//2 parameter
		template<typename OneParam,typename TwoParam>
		void publishEvent(TEXT eventName, OneParam param1,TwoParam param2) {
			if (auto result = eventMap.tryFind_unique(eventName.getHash()))
			{
				if ((*result)->types.size() != 2)throw "Publish Function has wrong Number of Parameters";
				if ((*result)->types[0] != getTypeID<OneParam>() ||
					(*result)->types[1] != getTypeID<TwoParam>())throw "Function Parameter has wrong type";
				auto casted = (eventTwoParam<OneParam,TwoParam>*)(*result);
				casted->param1 = param1;
				casted->param2 = param2;
				(*result)->fire();
			}
		}
	
		//3 parameter
		template<typename OneParam, typename TwoParam,typename ThreeParam>
		void publishEvent(TEXT eventName, OneParam param1, TwoParam param2,ThreeParam param3) {
			if (auto result = eventMap.tryFind_unique(eventName.getHash()))
			{
				if ((*result)->types.size() != 3)throw "Publish Function has wrong Number of Parameters";
				if ((*result)->types[0] != getTypeID<OneParam>() ||
					(*result)->types[1] != getTypeID<TwoParam>() ||
					(*result)->types[2] != getTypeID<ThreeParam>())throw "Function Parameter has wrong type";
				auto casted = (eventThreeParam<OneParam,TwoParam,ThreeParam>*)(*result);
				casted->param1 = param1;
				casted->param2 = param2;
				casted->param3 = param3;
				(*result)->fire();
			}
		}
	
		
	
		void addTimerFuction(TimeEvent& timeEvent) {
	 		auto Itr = timeEventList.rbegin();
	 		auto ItrEnd = timeEventList.rend();
			auto insertItr = timeEventList.end();
			for (; Itr != ItrEnd; ++Itr) {
				if (Itr->publishTime <= timeEvent.publishTime) {
					timeEventList.insert(insertItr, timeEvent);
					return;
				}
				--insertItr;
			}
			timeEventList.push_front(timeEvent);
		}
	
		void removeLoopedTimerFunction(TimeEvent& timeEvent) {
			removeVector.push_back(timeEvent);
		}

		void clear() {
			timeEventList.clear();
			removeVector.clear();
			eventMap.clear();
		}
	
	private:

		void publishTimeEvent() {
			if (timeEventList.size() == 0)return;
			if (removeVector.size() != 0)UnloopTimeEvents();
			std::vector<TimeEvent> loopElements;
			auto itr = timeEventList.begin();
			auto endItr = timeEventList.end();
			int64_t currTime = TIME::currentTimeInNanos();
			while (itr != endItr) {
				if (currTime >= itr->publishTime) {
					itr->CalledFunction();
					if (itr->IsLooped)loopTimer(*itr);
					timeEventList.erase(itr++);
				}
				else break;
			}
		}

		void UnloopTimeEvents()
		{
			for (auto& removeItem : removeVector) {
				for (auto& eventItem : timeEventList)
				{
					if (eventItem.timeId == removeItem.timeId) {
						if (!eventItem.IsLooped)throw "You are calling unloop for an already unlooped Time event";
						eventItem.IsLooped = false;
						break;
					}
				}
			}
			removeVector.clear();
		}

		void loopTimer(TimeEvent& timeEvent) {
			timeEvent.calculatePublishTime();
			addTimerFuction(timeEvent);
		}
		
		std::list<TimeEvent> timeEventList;
		std::vector<TimeEvent> removeVector;
		HashMap<size_t, std::unique_ptr<event>> eventMap;
		friend class Scene;
		friend class AMP_Engine;
	};
}