#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include "PlayerControl.h"
#include "TextureManager.h"
#include "StateStack.h"
#include "MusicPlayer.h"
#include "SoundPlayer.h"

class Aplication
{
public:
	Aplication();
		
	void					run();

private:
	void					processInputs();
	void					update(sf::Time dt);
	void					render();
	void					updateStatistics(sf::Time dt);
	void					registerStates();

private:
	static const sf::Time	TimePerFrame;

	sf::RenderWindow		window_;
	GEX::PlayerControl		player_;
	GEX::TextureManager		textures_;
	GEX::StateStack			stateStack_;
	GEX::MusicPlayer		music_;
	GEX::SoundPlayer		sound_;

	sf::Text				statisticsText_;
	sf::Time				statisticsUpdateTime_;
	unsigned int			statisticsNumFrames_;
};

