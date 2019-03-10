#pragma once
#include "State.h"


class GameOverState : public GEX::State
{
public:
	GameOverState(GEX::StateStack& stack, Context context);

	void					draw() override;
	bool					update(sf::Time dt) override;
	bool					handleEvent(const sf::Event& event) override;

private:
	sf::Text				gameOverText_;
	sf::Time				elapsedTime_; //Hold the time counter on this state
	int						waitingTime_; //time to wait until reset the game and return to main screen
};

