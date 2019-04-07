/**
* @file
* DataTables.h
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
#include "TextureManager.h"
#include <map>
#include "Actor.h"
#include <SFML/System/Vector2.hpp>

namespace GEX
{

	struct ActorData 
	{
		TextureID								texture;
		std::map<Actor::State, Animation2>		animations;
		std::vector<int>						validTiles;
	};

	struct DeliveryData
	{
		std::vector<sf::Vector2i>				deliveryTiles;
	};

	struct PickupData
	{
		std::vector<sf::Vector2i>				pickupTiles;
	};

	struct BlockData
	{
		std::vector<sf::Vector2i>				blockTiles;
	};

	std::map<ActorType, ActorData>				initializeActorData();
	std::map<int, DeliveryData>					initializeDeliveryData();
	std::map<int, PickupData>					initializePickupData();
	std::map<int, BlockData>					initializeBlockData();
	std::map<std::string, int>					initializeParametersData();
	std::map<int, sf::Color>					initializeColorData();

}
