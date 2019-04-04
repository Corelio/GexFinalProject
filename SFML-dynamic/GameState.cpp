#include "GameState.h"

GameState::GameState(GEX::StateStack& stack, Context context)
	: GEX::State(stack, context)
	, world_(*context.window_, *context.sound_)
	, player_(*context.player_)
{
	context.music_->stop();
}

//Draw the world
void GameState::draw()
{
	world_.draw();
}

/*
Update the game state
*/
bool GameState::update(sf::Time dt)
{
	auto& commands = world_.getCommandQueue();
	world_.update(dt, commands);

	//check if there is a live player otherwise push the game over state to the stack
	if (!world_.hasAlivePlayer())
	{
		player_.setMissionStatus(GEX::MissionStatus::MissionFailure);
		requestStackPush(GEX::StateID::GameOver);
	}
	
	player_.handleRealTimeInput(commands);
	
	return true;
}

//handle key press events -> show menu and gex state
bool GameState::handleEvent(const sf::Event & event)
{
	auto& commands = world_.getCommandQueue();
	player_.handleEvent(event, commands);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		requestStackPush(GEX::StateID::Pause);
	}
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G) //Assignment - G calls Gex State
	{
		requestStackPush(GEX::StateID::Gex);
	}
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q) //Assignment - Q quits and calls Menu
	{
		requestStackClear();
		requestStackPush(GEX::StateID::Menu);
	}

	return true;
}


