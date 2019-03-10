#include "DataTables.h"
#include "JsonFrameParser.h"

namespace GEX
{
	std::map<GEX::ActorType, GEX::ActorData> GEX::initializeActorData()
	{
		std::map<ActorType, ActorData> data;

		JsonFrameParser frames = JsonFrameParser("Media/Textures/pacManAtlas.json");

		// All actors must have a dead state otherwise the application will break when the actor is destroyed

		data[ActorType::Car].texture = TextureID::PacmanAtlas;
						
		data[ActorType::Car].animations[Actor::State::HorizontalRight].addFrameSet(frames.getFramesFor("red right"));
		data[ActorType::Car].animations[Actor::State::HorizontalRight].setDuration(sf::Time(sf::seconds(1.f)));
		data[ActorType::Car].animations[Actor::State::HorizontalRight].setRepeating(true);

		data[ActorType::Car].animations[Actor::State::HorizontalLeft].addFrameSet(frames.getFramesFor("red left"));
		data[ActorType::Car].animations[Actor::State::HorizontalLeft].setDuration(sf::Time(sf::seconds(1.f)));
		data[ActorType::Car].animations[Actor::State::HorizontalLeft].setRepeating(true);
					
		data[ActorType::Car].animations[Actor::State::VerticalUp].addFrameSet(frames.getFramesFor("red up"));
		data[ActorType::Car].animations[Actor::State::VerticalUp].setDuration(sf::Time(sf::seconds(1.f)));
		data[ActorType::Car].animations[Actor::State::VerticalUp].setRepeating(true);
													  
		data[ActorType::Car].animations[Actor::State::VerticalDown].addFrameSet(frames.getFramesFor("red down"));
		data[ActorType::Car].animations[Actor::State::VerticalDown].setDuration(sf::Time(sf::seconds(1.f)));
		data[ActorType::Car].animations[Actor::State::VerticalDown].setRepeating(true);

		data[ActorType::Car].animations[Actor::State::Dead].addFrameSet(frames.getFramesFor("die"));
		data[ActorType::Car].animations[Actor::State::Dead].setDuration(sf::Time(sf::seconds(1.f)));
		data[ActorType::Car].animations[Actor::State::Dead].setRepeating(false);

		data[ActorType::Car].validTiles.push_back(1092);
		data[ActorType::Car].validTiles.push_back(1093);
		data[ActorType::Car].validTiles.push_back(1094);
		data[ActorType::Car].validTiles.push_back(1095);

		return data;
	}


	std::map<int, DeliveryData > initializeDeliveryData()
	{
		std::map<int, DeliveryData> data;

		int position = 0;

		data[position].deliveryTiles.push_back(sf::Vector2i(8, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(9, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(10, 5));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(13, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(14, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(15, 5));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(23, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(24, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(25, 5));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(33, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(34, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(35, 5));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(43, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(44, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(45, 5));

		return data;
	}

	std::map<int, PickupData> initializePickupData()
	{
		std::map<int, PickupData> data;

		data[0].pickupTiles.push_back(sf::Vector2i(73, 44));
		data[0].pickupTiles.push_back(sf::Vector2i(74, 44));
		data[0].pickupTiles.push_back(sf::Vector2i(75, 44));
		data[0].pickupTiles.push_back(sf::Vector2i(76, 44));
		data[0].pickupTiles.push_back(sf::Vector2i(77, 44));
		data[0].pickupTiles.push_back(sf::Vector2i(78, 44));

		return data;
	}
	std::map<std::string, int> initializeParametersData()
	{
		std::map<std::string, int> data;

		data["EXPIRETIME"] = 240;
		data["PICKUPTIME"] = 3;
		data["NUMBERORDERSLEVELUP"] = 20;
		data["WALLET"] = 1000;

		return data;
	}
}
