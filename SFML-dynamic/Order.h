#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <vector>
#include "Utility.h"

namespace GEX
{
	class Order
	{
	public:
		Order(sf::Color color = sf::Color(155 + randomInt(100), 155 + randomInt(100), 155 + randomInt(100)));
		~Order();
		void						update(sf::Time dt, sf::Vector2i tilePosition = sf::Vector2i(-1, -1));
		bool						isExpired() const;
		bool						isDelivered() const;
		sf::Time					getTime() const;
		float						getValue() const;
		float						getTip() const;
		sf::Color					getColor() const;
		std::vector<sf::Vector2i>	getDeliveryTiles() const;

	private:
		void						generateOrder();

	private:
		std::vector<sf::Vector2i>	deliveryTiles_;
		float						value_;
		sf::Time					time_;
		sf::Time					delivery_;
		sf::Color					color_;
	};
}