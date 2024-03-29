/**
* @file
* PauseState.cpp
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
#include "PauseState.h"
#include "Utility.h"
#include "FontManager.h"

PauseState::PauseState(GEX::StateStack& stack, Context context)
	: GEX::State(stack, context)
	, backgroundSprite_()
	, pauseText_()
	, instructionText_()
{
	pauseText_.setFont(GEX::FontManager::getInstance().get(GEX::FontID::Main));
	pauseText_.setString("Game Paused");
	pauseText_.setCharacterSize(70);
	centerOrigin(pauseText_);

	instructionText_.setFont(GEX::FontManager::getInstance().get(GEX::FontID::Main));
	instructionText_.setString("          Press backspace \nto return to the main menu");
	centerOrigin(instructionText_);

	sf::Vector2f viewsize = context.window_->getView().getSize();
	pauseText_.setPosition(0.5f * viewsize.x, 0.4f * viewsize.y);
	instructionText_.setPosition(0.5f * viewsize.x, 0.6f * viewsize.y);

	context.music_->setPaused(true);
}

PauseState::~PauseState()
{
	getContext().music_->setPaused(false);
}

//Draw pause state - Background and texts
void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window_;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(pauseText_);
	window.draw(instructionText_);
}

/*
Pause stats does not allow other states to update
*/
bool PauseState::update(sf::Time dt)
{
	return false;
}

// Events that will be handled in the pause state
bool PauseState::handleEvent(const sf::Event & event)
{
	if (event.type != sf::Event::KeyPressed)
	{
		return false;
	}

	//Escape return to previous state
	if (event.key.code == sf::Keyboard::Escape)
	{
		requestStackPop();
	}

	//Backspace - remove all states and initialize menu state
	if (event.key.code == sf::Keyboard::BackSpace)
	{
		requestStackClear();
		requestStackPush(GEX::StateID::Menu);
	}

	return false;
}
