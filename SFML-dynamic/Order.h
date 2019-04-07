/**
* @file
* Order.h
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
		Order(sf::Color color = sf::Color::White);
		~Order();
		void						update(sf::Time dt, sf::Vector2i tilePosition = sf::Vector2i(-1, -1));
		bool						isExpired() const;
		bool						isDelivered() const;
		bool						isDelivering() const;
		sf::Time					getTime() const;
		float						getValue() const;
		float						getTip() const;
		sf::Color					getColor() const;
		void						setColor(sf::Color c) {
			color_ = c;
		}
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