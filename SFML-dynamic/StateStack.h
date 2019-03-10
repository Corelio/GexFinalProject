#pragma once
#include "State.h"
#include "StatesIdentifiers.h"
#include <vector>
#include <map>
#include <functional>

namespace sf
{
	class Event;
	class RenderWindow;
}

namespace GEX
{
	class StateStack
	{
	public:
		enum class Action
		{
			Push,
			Pop,
			Clear
		};

	public:
		explicit	StateStack(State::Context context);

					~StateStack();

		template <typename T>
		void		registerState(GEX::StateID stateID);

		void		update(sf::Time dt);
		void		draw();
		void		handleEvent(const sf::Event& event);

		void		pushState(StateID stateID);
		void		popState();
		void		clearStates();

		bool		isEmpty() const;

	private:
		State::Ptr	createState(StateID stateID);
		void		applyPendingChanges();

	private:
		struct PendingChange
		{
			explicit		PendingChange(Action action, StateID stateID = StateID::None);

			Action			action;
			StateID			stateID;

		};

	private:
		std::vector<State::Ptr>								stack_;
		std::vector<PendingChange>							pendingList_;
		State::Context										context_;
		std::map <StateID, std::function<State::Ptr()>>		factories_;
	};

	template <typename T>
	void StateStack::registerState(GEX::StateID stateID)
	{
		factories_[stateID] = [this]() 
		{
			return State::Ptr(new T(*this, context_));
		};
	}
}
