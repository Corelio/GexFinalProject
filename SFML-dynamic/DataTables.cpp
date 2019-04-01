#include "DataTables.h"
#include "JsonFrameParser.h"

namespace GEX
{
	std::map<GEX::ActorType, GEX::ActorData> GEX::initializeActorData()
	{
		std::map<ActorType, ActorData> data;

		JsonFrameParser frames = JsonFrameParser("Media/Textures/carAtlas.json");

		// All actors must have a dead state otherwise the application will break when the actor is destroyed

		data[ActorType::Car].texture = TextureID::PacmanAtlas;
						
		data[ActorType::Car].animations[Actor::State::HorizontalRight].addFrameSet(frames.getFramesFor("hf"));
		data[ActorType::Car].animations[Actor::State::HorizontalRight].setDuration(sf::Time(sf::seconds(1.f)));
		data[ActorType::Car].animations[Actor::State::HorizontalRight].setRepeating(true);

		data[ActorType::Car].animations[Actor::State::HorizontalLeft].addFrameSet(frames.getFramesFor("hr"));
		data[ActorType::Car].animations[Actor::State::HorizontalLeft].setDuration(sf::Time(sf::seconds(1.f)));
		data[ActorType::Car].animations[Actor::State::HorizontalLeft].setRepeating(true);
					
		data[ActorType::Car].animations[Actor::State::VerticalUp].addFrameSet(frames.getFramesFor("up"));
		data[ActorType::Car].animations[Actor::State::VerticalUp].setDuration(sf::Time(sf::seconds(1.f)));
		data[ActorType::Car].animations[Actor::State::VerticalUp].setRepeating(true);
													  
		data[ActorType::Car].animations[Actor::State::VerticalDown].addFrameSet(frames.getFramesFor("dw"));
		data[ActorType::Car].animations[Actor::State::VerticalDown].setDuration(sf::Time(sf::seconds(1.f)));
		data[ActorType::Car].animations[Actor::State::VerticalDown].setRepeating(true);

		data[ActorType::Car].animations[Actor::State::Dead].addFrameSet(frames.getFramesFor("hf"));
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

		//first line
		int position = 0;

		data[position].deliveryTiles.push_back(sf::Vector2i(8, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(9, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(10, 5));
		
		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(13, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(14, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(15, 5));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(24, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(25, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(26, 5));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(36, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(37, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(38, 5));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(40, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(41, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(42, 5));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(63, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(64, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(65, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(66, 5));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(73, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(74, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(75, 5));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(77, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(78, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(79, 5));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(87, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(88, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(89, 5));
		data[position].deliveryTiles.push_back(sf::Vector2i(90, 5));

		//Second line
		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(0, 18));
		data[position].deliveryTiles.push_back(sf::Vector2i(1, 18));
		data[position].deliveryTiles.push_back(sf::Vector2i(2, 18));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(8, 18));
		data[position].deliveryTiles.push_back(sf::Vector2i(9, 18));
		data[position].deliveryTiles.push_back(sf::Vector2i(10, 18));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(13, 18));
		data[position].deliveryTiles.push_back(sf::Vector2i(14, 18));
		data[position].deliveryTiles.push_back(sf::Vector2i(15, 18));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(25, 18));
		data[position].deliveryTiles.push_back(sf::Vector2i(26, 18));
		data[position].deliveryTiles.push_back(sf::Vector2i(27, 18));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(36, 18));
		data[position].deliveryTiles.push_back(sf::Vector2i(37, 18));
		data[position].deliveryTiles.push_back(sf::Vector2i(38, 18));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(40, 18));
		data[position].deliveryTiles.push_back(sf::Vector2i(41, 18));
		data[position].deliveryTiles.push_back(sf::Vector2i(42, 18));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(49, 18));
		data[position].deliveryTiles.push_back(sf::Vector2i(50, 18));
		data[position].deliveryTiles.push_back(sf::Vector2i(51, 18));
		data[position].deliveryTiles.push_back(sf::Vector2i(52, 18));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(60, 18));
		data[position].deliveryTiles.push_back(sf::Vector2i(61, 18));
		data[position].deliveryTiles.push_back(sf::Vector2i(62, 18));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(72, 18));
		data[position].deliveryTiles.push_back(sf::Vector2i(73, 18));
		data[position].deliveryTiles.push_back(sf::Vector2i(74, 18));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(86, 18));
		data[position].deliveryTiles.push_back(sf::Vector2i(87, 18));
		data[position].deliveryTiles.push_back(sf::Vector2i(88, 18));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(97, 18));
		data[position].deliveryTiles.push_back(sf::Vector2i(98, 18));
		data[position].deliveryTiles.push_back(sf::Vector2i(99, 18));

		//Third line
		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(0, 31));
		data[position].deliveryTiles.push_back(sf::Vector2i(1, 31));
		data[position].deliveryTiles.push_back(sf::Vector2i(2, 31));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(12, 31));
		data[position].deliveryTiles.push_back(sf::Vector2i(13, 31));
		data[position].deliveryTiles.push_back(sf::Vector2i(14, 31));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(25, 31));
		data[position].deliveryTiles.push_back(sf::Vector2i(26, 31));
		data[position].deliveryTiles.push_back(sf::Vector2i(27, 31));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(38, 31));
		data[position].deliveryTiles.push_back(sf::Vector2i(39, 31));
		data[position].deliveryTiles.push_back(sf::Vector2i(40, 31));
		data[position].deliveryTiles.push_back(sf::Vector2i(41, 31));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(63, 31));
		data[position].deliveryTiles.push_back(sf::Vector2i(64, 31));
		data[position].deliveryTiles.push_back(sf::Vector2i(65, 31));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(75, 31));
		data[position].deliveryTiles.push_back(sf::Vector2i(76, 31));
		data[position].deliveryTiles.push_back(sf::Vector2i(77, 31));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(87, 31));
		data[position].deliveryTiles.push_back(sf::Vector2i(88, 31));
		data[position].deliveryTiles.push_back(sf::Vector2i(89, 31));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(97, 31));
		data[position].deliveryTiles.push_back(sf::Vector2i(98, 31));
		data[position].deliveryTiles.push_back(sf::Vector2i(99, 31));

		//Forth line
		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(0, 44));
		data[position].deliveryTiles.push_back(sf::Vector2i(1, 44));
		data[position].deliveryTiles.push_back(sf::Vector2i(2, 44));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(10, 44));
		data[position].deliveryTiles.push_back(sf::Vector2i(11, 44));
		data[position].deliveryTiles.push_back(sf::Vector2i(12, 44));
		data[position].deliveryTiles.push_back(sf::Vector2i(13, 44));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(21, 44));
		data[position].deliveryTiles.push_back(sf::Vector2i(22, 44));
		data[position].deliveryTiles.push_back(sf::Vector2i(23, 44));
		data[position].deliveryTiles.push_back(sf::Vector2i(24, 44));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(35, 44));
		data[position].deliveryTiles.push_back(sf::Vector2i(36, 44));
		data[position].deliveryTiles.push_back(sf::Vector2i(37, 44));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(49, 44));
		data[position].deliveryTiles.push_back(sf::Vector2i(50, 44));
		data[position].deliveryTiles.push_back(sf::Vector2i(51, 44));
		data[position].deliveryTiles.push_back(sf::Vector2i(52, 44));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(60, 44));
		data[position].deliveryTiles.push_back(sf::Vector2i(61, 44));
		data[position].deliveryTiles.push_back(sf::Vector2i(62, 44));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(85, 44));
		data[position].deliveryTiles.push_back(sf::Vector2i(86, 44));
		data[position].deliveryTiles.push_back(sf::Vector2i(87, 44));

		position++;

		data[position].deliveryTiles.push_back(sf::Vector2i(97, 44));
		data[position].deliveryTiles.push_back(sf::Vector2i(98, 44));
		data[position].deliveryTiles.push_back(sf::Vector2i(99, 44));


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

	std::map<int, BlockData> initializeBlockData()
	{
		std::map<int, BlockData> data;

		int i = 0;

		data[i].blockTiles.push_back(sf::Vector2i(4, 7));
		data[i].blockTiles.push_back(sf::Vector2i(5, 7));
		data[i].blockTiles.push_back(sf::Vector2i(6, 7));
		data[i].blockTiles.push_back(sf::Vector2i(4, 16));
		data[i].blockTiles.push_back(sf::Vector2i(5, 16));
		data[i].blockTiles.push_back(sf::Vector2i(6, 16));

		i++;

		data[i].blockTiles.push_back(sf::Vector2i(4, 20));
		data[i].blockTiles.push_back(sf::Vector2i(5, 20));
		data[i].blockTiles.push_back(sf::Vector2i(6, 20));
		data[i].blockTiles.push_back(sf::Vector2i(4, 29));
		data[i].blockTiles.push_back(sf::Vector2i(5, 29));
		data[i].blockTiles.push_back(sf::Vector2i(6, 29));

		i++;

		data[i].blockTiles.push_back(sf::Vector2i(4, 33));
		data[i].blockTiles.push_back(sf::Vector2i(5, 33));
		data[i].blockTiles.push_back(sf::Vector2i(6, 33));
		data[i].blockTiles.push_back(sf::Vector2i(4, 42));
		data[i].blockTiles.push_back(sf::Vector2i(5, 42));
		data[i].blockTiles.push_back(sf::Vector2i(6, 42));

		i++;
		data[i].blockTiles.push_back(sf::Vector2i(17, 7));
		data[i].blockTiles.push_back(sf::Vector2i(18, 7));
		data[i].blockTiles.push_back(sf::Vector2i(19, 7));
		data[i].blockTiles.push_back(sf::Vector2i(17, 16));
		data[i].blockTiles.push_back(sf::Vector2i(18, 16));
		data[i].blockTiles.push_back(sf::Vector2i(19, 16));

		i++;

		data[i].blockTiles.push_back(sf::Vector2i(17, 20));
		data[i].blockTiles.push_back(sf::Vector2i(18, 20));
		data[i].blockTiles.push_back(sf::Vector2i(19, 20));
		data[i].blockTiles.push_back(sf::Vector2i(17, 29));
		data[i].blockTiles.push_back(sf::Vector2i(18, 29));
		data[i].blockTiles.push_back(sf::Vector2i(19, 29));

		i++;

		data[i].blockTiles.push_back(sf::Vector2i(17, 33));
		data[i].blockTiles.push_back(sf::Vector2i(18, 33));
		data[i].blockTiles.push_back(sf::Vector2i(19, 33));
		data[i].blockTiles.push_back(sf::Vector2i(17, 42));
		data[i].blockTiles.push_back(sf::Vector2i(18, 42));
		data[i].blockTiles.push_back(sf::Vector2i(19, 42));

		i++;
		data[i].blockTiles.push_back(sf::Vector2i(31, 7));
		data[i].blockTiles.push_back(sf::Vector2i(32, 7));
		data[i].blockTiles.push_back(sf::Vector2i(33, 7));
		data[i].blockTiles.push_back(sf::Vector2i(31, 16));
		data[i].blockTiles.push_back(sf::Vector2i(32, 16));
		data[i].blockTiles.push_back(sf::Vector2i(33, 16));

		i++;

		data[i].blockTiles.push_back(sf::Vector2i(31, 20));
		data[i].blockTiles.push_back(sf::Vector2i(32, 20));
		data[i].blockTiles.push_back(sf::Vector2i(33, 20));
		data[i].blockTiles.push_back(sf::Vector2i(31, 29));
		data[i].blockTiles.push_back(sf::Vector2i(32, 29));
		data[i].blockTiles.push_back(sf::Vector2i(33, 29));

		i++;

		data[i].blockTiles.push_back(sf::Vector2i(31, 33));
		data[i].blockTiles.push_back(sf::Vector2i(32, 33));
		data[i].blockTiles.push_back(sf::Vector2i(33, 33));
		data[i].blockTiles.push_back(sf::Vector2i(31, 42));
		data[i].blockTiles.push_back(sf::Vector2i(32, 42));
		data[i].blockTiles.push_back(sf::Vector2i(33, 42));

		i++;
		data[i].blockTiles.push_back(sf::Vector2i(44, 7));
		data[i].blockTiles.push_back(sf::Vector2i(45, 7));
		data[i].blockTiles.push_back(sf::Vector2i(46, 7));
		data[i].blockTiles.push_back(sf::Vector2i(44, 16));
		data[i].blockTiles.push_back(sf::Vector2i(45, 16));
		data[i].blockTiles.push_back(sf::Vector2i(46, 16));

		i++;

		data[i].blockTiles.push_back(sf::Vector2i(44, 20));
		data[i].blockTiles.push_back(sf::Vector2i(45, 20));
		data[i].blockTiles.push_back(sf::Vector2i(46, 20));
		data[i].blockTiles.push_back(sf::Vector2i(44, 29));
		data[i].blockTiles.push_back(sf::Vector2i(45, 29));
		data[i].blockTiles.push_back(sf::Vector2i(46, 29));

		i++;

		data[i].blockTiles.push_back(sf::Vector2i(44, 33));
		data[i].blockTiles.push_back(sf::Vector2i(45, 33));
		data[i].blockTiles.push_back(sf::Vector2i(46, 33));
		data[i].blockTiles.push_back(sf::Vector2i(44, 42));
		data[i].blockTiles.push_back(sf::Vector2i(45, 42));
		data[i].blockTiles.push_back(sf::Vector2i(46, 42));

		i++;
		data[i].blockTiles.push_back(sf::Vector2i(55, 7));
		data[i].blockTiles.push_back(sf::Vector2i(56, 7));
		data[i].blockTiles.push_back(sf::Vector2i(57, 7));
		data[i].blockTiles.push_back(sf::Vector2i(55, 16));
		data[i].blockTiles.push_back(sf::Vector2i(56, 16));
		data[i].blockTiles.push_back(sf::Vector2i(57, 16));

		i++;

		data[i].blockTiles.push_back(sf::Vector2i(55, 20));
		data[i].blockTiles.push_back(sf::Vector2i(56, 20));
		data[i].blockTiles.push_back(sf::Vector2i(57, 20));
		data[i].blockTiles.push_back(sf::Vector2i(55, 29));
		data[i].blockTiles.push_back(sf::Vector2i(56, 29));
		data[i].blockTiles.push_back(sf::Vector2i(57, 29));

		i++;

		data[i].blockTiles.push_back(sf::Vector2i(55, 33));
		data[i].blockTiles.push_back(sf::Vector2i(56, 33));
		data[i].blockTiles.push_back(sf::Vector2i(57, 33));
		data[i].blockTiles.push_back(sf::Vector2i(55, 42));
		data[i].blockTiles.push_back(sf::Vector2i(56, 42));
		data[i].blockTiles.push_back(sf::Vector2i(57, 42));

		i++;
		data[i].blockTiles.push_back(sf::Vector2i(68, 7));
		data[i].blockTiles.push_back(sf::Vector2i(69, 7));
		data[i].blockTiles.push_back(sf::Vector2i(70, 7));
		data[i].blockTiles.push_back(sf::Vector2i(68, 16));
		data[i].blockTiles.push_back(sf::Vector2i(69, 16));
		data[i].blockTiles.push_back(sf::Vector2i(70, 16));

		i++;

		data[i].blockTiles.push_back(sf::Vector2i(68, 20));
		data[i].blockTiles.push_back(sf::Vector2i(69, 20));
		data[i].blockTiles.push_back(sf::Vector2i(70, 20));
		data[i].blockTiles.push_back(sf::Vector2i(68, 29));
		data[i].blockTiles.push_back(sf::Vector2i(69, 29));
		data[i].blockTiles.push_back(sf::Vector2i(70, 29));

		i++;

		data[i].blockTiles.push_back(sf::Vector2i(68, 33));
		data[i].blockTiles.push_back(sf::Vector2i(69, 33));
		data[i].blockTiles.push_back(sf::Vector2i(70, 33));
		data[i].blockTiles.push_back(sf::Vector2i(68, 42));
		data[i].blockTiles.push_back(sf::Vector2i(69, 42));
		data[i].blockTiles.push_back(sf::Vector2i(70, 42));

		i++;
		data[i].blockTiles.push_back(sf::Vector2i(81, 7));
		data[i].blockTiles.push_back(sf::Vector2i(82, 7));
		data[i].blockTiles.push_back(sf::Vector2i(83, 7));
		data[i].blockTiles.push_back(sf::Vector2i(81, 16));
		data[i].blockTiles.push_back(sf::Vector2i(82, 16));
		data[i].blockTiles.push_back(sf::Vector2i(83, 16));

		i++;

		data[i].blockTiles.push_back(sf::Vector2i(81, 20));
		data[i].blockTiles.push_back(sf::Vector2i(82, 20));
		data[i].blockTiles.push_back(sf::Vector2i(83, 20));
		data[i].blockTiles.push_back(sf::Vector2i(81, 29));
		data[i].blockTiles.push_back(sf::Vector2i(82, 29));
		data[i].blockTiles.push_back(sf::Vector2i(83, 29));

		i++;

		data[i].blockTiles.push_back(sf::Vector2i(81, 33));
		data[i].blockTiles.push_back(sf::Vector2i(82, 33));
		data[i].blockTiles.push_back(sf::Vector2i(83, 33));
		data[i].blockTiles.push_back(sf::Vector2i(81, 42));
		data[i].blockTiles.push_back(sf::Vector2i(82, 42));
		data[i].blockTiles.push_back(sf::Vector2i(83, 42));

		i++;
		data[i].blockTiles.push_back(sf::Vector2i(93, 7));
		data[i].blockTiles.push_back(sf::Vector2i(94, 7));
		data[i].blockTiles.push_back(sf::Vector2i(95, 7));
		data[i].blockTiles.push_back(sf::Vector2i(93, 16));
		data[i].blockTiles.push_back(sf::Vector2i(94, 16));
		data[i].blockTiles.push_back(sf::Vector2i(95, 16));

		i++;

		data[i].blockTiles.push_back(sf::Vector2i(93, 20));
		data[i].blockTiles.push_back(sf::Vector2i(94, 20));
		data[i].blockTiles.push_back(sf::Vector2i(95, 20));
		data[i].blockTiles.push_back(sf::Vector2i(93, 29));
		data[i].blockTiles.push_back(sf::Vector2i(94, 29));
		data[i].blockTiles.push_back(sf::Vector2i(95, 29));

		i++;

		data[i].blockTiles.push_back(sf::Vector2i(93, 33));
		data[i].blockTiles.push_back(sf::Vector2i(94, 33));
		data[i].blockTiles.push_back(sf::Vector2i(95, 33));
		data[i].blockTiles.push_back(sf::Vector2i(93, 42));
		data[i].blockTiles.push_back(sf::Vector2i(94, 42));
		data[i].blockTiles.push_back(sf::Vector2i(95, 42));

		return data;
	}

	std::map<std::string, int> initializeParametersData()
	{
		std::map<std::string, int> data;

		data["EXPIRETIME"] = 240;
		data["PICKUPTIME"] = 3;
		data["NUMBERORDERSLEVELUP"] = 2;
		data["WALLET"] = 1000;

		return data;
	}

	std::map<int, sf::Color> initializeColorData()
	{
		std::map<int, sf::Color> data;

		data[0] = sf::Color::Blue;
		data[1] = sf::Color::Cyan;
		data[2] = sf::Color::Green;
		data[3] = sf::Color::Magenta;
		data[4] = sf::Color::Yellow;

		return data;
	}
}
