/**
* @file
* GexState.h
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

