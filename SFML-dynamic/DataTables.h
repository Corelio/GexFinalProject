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
