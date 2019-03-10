#pragma once

#include <map>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include "Command.h"
#include "CommandQueue.h"
#include "Category.h"

namespace GEX
{

	enum class Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		Stop,
	};

	enum class MissionStatus{
		MissionRunning,
		MissionFailure,
		MissionSuccess
	};

	class PlayerControl
	{
	public:
		PlayerControl();

		void			handleEvent(const sf::Event& event, CommandQueue& commands);
		void			handleRealTimeInput(CommandQueue& commands);

		void			setMissionStatus(MissionStatus status);
		MissionStatus	getMissionStatus() const;

	private:
		void			initializeActions();
		static bool		isRealTimeAction(Action action);

	private:
		std::map<sf::Keyboard::Key, Action>		keyBindings_;
		std::map<Action, Command>				actionBindings_;
		MissionStatus							currentMissionStatus_;
	};
}
