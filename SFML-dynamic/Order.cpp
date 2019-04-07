/**
* @file
* Order.cpp
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
#include "Order.h"
#include <algorithm>
#include "DataTables.h"
#include "Utility.h"

namespace GEX
{
	namespace
	{
		const std::map<int, DeliveryData> TABLE = initializeDeliveryData();
		const std::map<std::string, int> PARAMETERS = initializeParametersData();
	}

	Order::Order(sf::Color color) :
		color_(color),
		time_(sf::seconds(PARAMETERS.at("EXPIRETIME"))),
		delivery_(sf::seconds(0))
	{
		//Create a new order
		generateOrder();
	}

	Order::~Order()
	{
	}

	//Update order - increase order time and check for delivery
	void Order::update(sf::Time dt, sf::Vector2i tilePosition)
	{
		if (!isExpired()) {
			//update time
			time_ -= dt;
			if (tilePosition != sf::Vector2i(-1, -1))
			{
				if (std::find(deliveryTiles_.begin(), deliveryTiles_.end(), tilePosition) != deliveryTiles_.end())
				{
					delivery_ += dt;
				}
				else {
					delivery_ = sf::seconds(0);
				}
			}
			else {
				delivery_ = sf::seconds(0);
			}
		}
		else if (color_ != sf::Color::Red) {
			color_ = sf::Color::Red;
		}
	}

	//Check if order is expired
	bool Order::isExpired() const
	{
		if (time_.asSeconds() <= sf::seconds(0).asSeconds())
		{
			return true;
		}
		return false;
	}

	//Check if order is delivered
	bool Order::isDelivered() const
	{
		if (delivery_.asSeconds() >= sf::seconds(PARAMETERS.at("PICKUPTIME")).asSeconds()) {
			return true;
		}
		return false;
	}

	bool Order::isDelivering() const
	{
		if (delivery_.asSeconds() > sf::seconds(0).asSeconds()) {
			return true;
		}
		return false;
	}

	//Get elapsed time for the order
	sf::Time Order::getTime() const
	{
		return time_;
	}

	//Get the order value
	float Order::getValue() const
	{
		return value_;
	}

	//Calculate order tip
	float Order::getTip() const
	{
		//Only calculate tip not expired deliveries
		if (!isExpired()) {
 			float percentage = 0.05;

			if (time_.asSeconds() > sf::seconds(PARAMETERS.at("EXPIRETIME")*.9).asSeconds())
			{
				percentage = 0.25;
			}
			else if (time_.asSeconds() > sf::seconds(PARAMETERS.at("EXPIRETIME")*.8).asSeconds())
			{
				percentage = 0.20;
			}
			else if (time_.asSeconds() > sf::seconds(PARAMETERS.at("EXPIRETIME")*.7).asSeconds())
			{
				percentage = 0.15;
			}
			else if (time_.asSeconds() > sf::seconds(PARAMETERS.at("EXPIRETIME")*.6).asSeconds())
			{
				percentage = 0.10;
			}
			else if (time_.asSeconds() >= sf::seconds(PARAMETERS.at("EXPIRETIME")*.5).asSeconds())
			{
				percentage = 0.0;
			}
			else if (time_.asSeconds() < sf::seconds(PARAMETERS.at("EXPIRETIME")*.5).asSeconds())
			{
				//If the delivery time is over 1/2 of the delivery time, charge the player the value
				return -1.0 * value_;
			}

			return value_ * (percentage);
		}
		return 0.0f;
	}

	//Get the color of the order
	sf::Color Order::getColor() const
	{
		return color_;
	}

	std::vector<sf::Vector2i> Order::getDeliveryTiles() const
	{
		return deliveryTiles_;
	}

	//Helper method to generate the order - value and delivery address
	void Order::generateOrder()
	{
		//find a delivery address
		deliveryTiles_ = TABLE.at(randomInt(TABLE.size() - 1)).deliveryTiles;
		//Generate a random float in a form of a string - max value is 199.99
		std::string value = std::to_string(randomInt(2))+std::to_string(randomInt(8) + 1 )+ std::to_string(randomInt(9))+"."+ std::to_string(randomInt(9))+ std::to_string(randomInt(9));
		value_ = stof(value);
	}
}