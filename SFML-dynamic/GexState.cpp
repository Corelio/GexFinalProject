/**
* @file
* GexState.cpp
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
#include "GexState.h"
#include "Utility.h"
#include "FontManager.h"


GexState::GexState(GEX::StateStack& stack, Context context)
	: GEX::State(stack, context)
	, backgroundSprite_()
	, faceSprite_()
	, pauseText_()
	, gexText_()
	, instructionText1_()
	, instructionText2_()
{
	//Get the font from the font manager
	sf::Font& font = GEX::FontManager::getInstance().get(GEX::FontID::Main);
	
	//Set text object 1 - game pause
	pauseText_.setFont(font);
	pauseText_.setString("Game Paused");
	pauseText_.setCharacterSize(70);
	centerOrigin(pauseText_);

	//Set text object 2 - gex State
	gexText_.setFont(font);
	gexText_.setString("Gex State");
	gexText_.setFillColor(sf::Color::Green);
	gexText_.setCharacterSize(50);
	centerOrigin(gexText_);

	//Set Face sprite
	faceSprite_.setTexture(context.textures_->get(GEX::TextureID::Face));
	faceSprite_.setColor(sf::Color(255, 255, 255, 100));
	centerOrigin(faceSprite_);

	//Set text object 3 - Instruction Text
	instructionText1_.setFont(font);
	instructionText1_.setString("(Press G to return to the game)");
	centerOrigin(instructionText1_);

	//Set text object 4 - Instruction Text
	instructionText2_.setFont(font);
	instructionText2_.setString("(Press backspace to return to the main menu)");
	centerOrigin(instructionText2_);

	//Position all elements
	sf::Vector2f viewsize = context.window_->getView().getSize();
	pauseText_.setPosition(0.5f * viewsize.x, 0.3f * viewsize.y);
	gexText_.setPosition(0.5f * viewsize.x, 0.48f * viewsize.y);
	faceSprite_.setPosition(0.5f * viewsize.x, 0.55f * viewsize.y);
	instructionText1_.setPosition(0.5f * viewsize.x, 0.78f * viewsize.y);
	instructionText2_.setPosition(0.5f * viewsize.x, 0.83f * viewsize.y);
}

void GexState::draw()
{
	//Draw the elements
	//getting window
	sf::RenderWindow& window = *getContext().window_;
	window.setView(window.getDefaultView());

	//Set the background
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(255, 0, 0, 100));
	backgroundShape.setSize(window.getView().getSize());

	//Send elements to the window draw method
	window.draw(backgroundShape);
	window.draw(pauseText_);
	window.draw(gexText_);
	window.draw(faceSprite_);
	window.draw(instructionText1_);
	window.draw(instructionText2_);
}

bool GexState::update(sf::Time dt)
{
	//The state prevents the other states to run update
	return false;
}

bool GexState::handleEvent(const sf::Event & event)
{
	//Actions based on key press
	//If the event is not a key press, dont do anything
	if (event.type != sf::Event::KeyPressed)
	{
		return false;
	}

	//if user pressed G remove the GexState from the stack
	if (event.key.code == sf::Keyboard::G)
	{
		requestStackPop();
	}

	//if user presses backspace, clear the stack and call the menu
	if (event.key.code == sf::Keyboard::BackSpace)
	{
		requestStackClear();
		requestStackPush(GEX::StateID::Menu);
	}

	return false;
}


