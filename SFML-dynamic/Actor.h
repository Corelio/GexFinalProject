/**
* @file
* Actor.h
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
#include "Entity.h"
#include <SFML/Graphics/Sprite.hpp>
#include "TextureManager.h"
#include "Command.h"
#include "Animation2.h"
#include "Map.h"
#include "SoundNode.h"

namespace GEX
{
	class CommandQueue;
	class TextNode;

	//Possible actors
	enum class ActorType { Car };

	class Actor : public Entity
	{
	public:
		//Possible state for the actors
		enum class State { HorizontalLeft, HorizontalRight, VerticalUp, VerticalDown, Dead, count};

		//Actor possible direction
		enum class Direction { Left, Right, Up, Down, Stop, None };

		Actor(ActorType type, const GEX::TextureManager& textures, Map* map, Map* mapOverlay);
		~Actor() = default;

		unsigned int							getCategory() const override;
		sf::FloatRect							getBoundingBox() const override;

		void									setState(State state);
		Actor::State							getState() const;
		Actor::Direction						getDirection() const;
		Actor::Direction						getNewDirection() const;
		void									setDirection(Direction direction);
		void									setNewDirection(Direction direction);
		void									setTilePosition(sf::Vector2i position);
		sf::Vector2i							getTilePosition() const;
		bool									isMarkedForRemoval() const override;
		
		void									setTileSize(sf::Vector2u tileSize);
		void									setMapSize(sf::Vector2i mapSize);
		float									getWallet() const;
		std::string								getFormatedWallet() const;
		void									addWallet(float money);
		int										getLevel() const;
		void									levelUp();
		void									playLocalSound(CommandQueue& commands, SoundEffectID effect);

	private:
		void									updateStates(sf::Time dt);
		void									updateCurrent(sf::Time dt, CommandQueue& commands) override;
		void									drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
		void									updatePosition();
		bool									checkMovement();
		bool									isOppositeDirection();
		bool									isNextAnObstacle();

	private:
		ActorType								type_;
		State									state_;
		mutable sf::Sprite						sprite_;
		mutable std::map<State, Animation2>		animations_;
		Direction								direction_;
		Direction								newDirection_;
		const TextureManager&					textures_;

		sf::Vector2i							tilePosition_;
		sf::Vector2u							tileSize_;
		sf::Vector2i							mapSize_;
		float									wallet_;
		int										level_;
		bool									delivering_;
		std::vector<int>						validTiles_;

		Map*			                        map_;
		Map*									mapOverlay_;

	};
}

