#pragma once
#include "State.h"

class GexState : public GEX::State
{
public:
	GexState(GEX::StateStack& stack, Context context);

	void					draw() override;
	bool					update(sf::Time dt) override;
	bool					handleEvent(const sf::Event& event) override;

private:
	sf::Sprite				backgroundSprite_;
	sf::Sprite				faceSprite_;
	sf::Text				pauseText_;
	sf::Text				gexText_;
	sf::Text				instructionText1_;
	sf::Text				instructionText2_;
};

