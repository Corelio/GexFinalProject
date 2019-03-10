#include "GameOverState.h"
#include "Utility.h"
#include "FontManager.h"
#include "PlayerControl.h"


GameOverState::GameOverState(GEX::StateStack& stack, Context context)
	: State(stack, context)
	, gameOverText_()
	, elapsedTime_(sf::Time::Zero)
	, waitingTime_(2)
{
	sf::Vector2f windowSize(context.window_->getSize());

	gameOverText_.setFont(GEX::FontManager::getInstance().get(GEX::FontID::Main));
	if (context.player_->getMissionStatus() == GEX::MissionStatus::MissionFailure)
	{
		gameOverText_.setString("You are FIRED!!");
	}
	else
	{
		gameOverText_.setString("Mission Success");
	}
	gameOverText_.setCharacterSize(70);
	centerOrigin(gameOverText_);
	gameOverText_.setPosition(windowSize.x * .5f, windowSize.y * .4f);

}

void GameOverState::draw()
{
	sf::RenderWindow& window = *getContext().window_;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 50));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(gameOverText_);
}

bool GameOverState::update(sf::Time dt)
{
	elapsedTime_ += dt;
	if (elapsedTime_ > sf::seconds(waitingTime_))
	{
		requestStackClear();
		requestStackPush(GEX::StateID::Menu);
	}
	return false;
}

bool GameOverState::handleEvent(const sf::Event & event)
{
	return false;
}

