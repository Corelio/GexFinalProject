#include "State.h"
#include "StateStack.h"

namespace GEX
{
	State::Context::Context(
			sf::RenderWindow & window, 
			TextureManager & texture, 
			PlayerControl & player,
			MusicPlayer& music,
			SoundPlayer& sound
	)
		: window_(&window)
		, textures_(&texture)
		, player_(&player)
		, music_(&music)
		, sound_(&sound)
	{
	}

	State::State(StateStack& stack, Context context)
		: stack_(&stack)
		, context_(context)
	{
	}

	State::~State()
	{
	}

	void State::requestStackPush(StateID stateID)
	{
		stack_->pushState(stateID);
	}

	void State::requestStackPop()
	{
		stack_->popState();
	}

	void State::requestStackClear()
	{
		stack_->clearStates();
	}

	State::Context State::getContext() const
	{
		return context_;
	}

	
}