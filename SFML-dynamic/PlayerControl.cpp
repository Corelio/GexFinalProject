/**
* @file
* PlayerControl.cpp
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
#include "PlayerControl.h"
#include "Actor.h"
#include "Command.h"
#include <functional>

namespace GEX
{

	//Functor to move the actor
	struct ActorMover
	{
		ActorMover(Actor::Direction direction) : direction_(direction) {}

		void	operator() (Actor& actor, sf::Time dt) const
		{
			actor.setNewDirection(direction_);
		}

		Actor::Direction	direction_;
	};

	PlayerControl::PlayerControl()
		:currentMissionStatus_(MissionStatus::MissionRunning)
	{
		// Set up bindings
		keyBindings_[sf::Keyboard::Left] = Action::MoveLeft;
		keyBindings_[sf::Keyboard::Right] = Action::MoveRight;
		keyBindings_[sf::Keyboard::Up] = Action::MoveUp;
		keyBindings_[sf::Keyboard::Down] = Action::MoveDown;
		keyBindings_[sf::Keyboard::Space] = Action::Stop;

		//Set up actionbindings 
		initializeActions();

	}

	void PlayerControl::handleEvent(const sf::Event & event, CommandQueue & commands)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			auto found = keyBindings_.find(event.key.code);
			if (found != keyBindings_.end() && !isRealTimeAction(found->second))
			{
				commands.push(actionBindings_.at(found->second));
			}
		}
	}

	void PlayerControl::handleRealTimeInput(CommandQueue & commands)
		{
		//travese all assigned keys, look up the action, generate command
		for (auto pair : keyBindings_)
		{
			if (sf::Keyboard::isKeyPressed(pair.first) && isRealTimeAction(pair.second))
			{
				commands.push(actionBindings_.at(pair.second));
			}
		}
	}

	void PlayerControl::setMissionStatus(MissionStatus status)
	{
		currentMissionStatus_ = status;
	}

	MissionStatus PlayerControl::getMissionStatus() const
	{
		return currentMissionStatus_;
	}

	bool PlayerControl::isRealTimeAction(Action action)
	{
		switch (action)
		{
		case Action::MoveLeft:
		case Action::MoveRight:
		case Action::MoveUp:
		case Action::MoveDown:
		case Action::Stop:
			return true;
			break;
		default:
			return false;
		}
	}

	void PlayerControl::initializeActions()
	{

		//Creating all action bindings
		actionBindings_[Action::MoveLeft].action = derivedAction<Actor>(ActorMover(Actor::Direction::Left));
		actionBindings_[Action::MoveRight].action = derivedAction<Actor>(ActorMover(Actor::Direction::Right));
		actionBindings_[Action::MoveUp].action = derivedAction<Actor>(ActorMover(Actor::Direction::Up));
		actionBindings_[Action::MoveDown].action = derivedAction<Actor>(ActorMover(Actor::Direction::Down));
		actionBindings_[Action::Stop].action = derivedAction<Actor>(ActorMover(Actor::Direction::Stop));

		//Assigning to the pacman
		for (auto& pair : actionBindings_)
		{
			pair.second.category = Category::Car;
		}
		
		
	}
}