/**
* @file
* StateStack.h
* @author
* Marco Corsini Baccaro 2019
* @version 1.0
*
* @section DESCRIPTION
* Game Experience Development Course
* Class of 2018-2019 
* Final Project
*
* @section LICENSE
*
* Copyright 2019
* Permission to use, copy, modify, and/or distribute this software for
* any purpose with or without fee is hereby granted, provided that the
* above copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*
* @section Academic Integrity
* I certify that this work is solely my own and complies with
* NBCC Academic Integrity Policy (policy 1111)
*/
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
