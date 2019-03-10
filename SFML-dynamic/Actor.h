#pragma once
#include "Entity.h"
#include <SFML/Graphics/Sprite.hpp>
#include "TextureManager.h"
#include "Command.h"
#include "Animation2.h"
#include "Map.h"

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
		bool									hasPower() const;
		void									addPower();
		void									removePower();
		void									shouldBeAffraid(bool beAffraid);
		void									setAffraidElapsedTime(sf::Time affraidElapsedTime);
		sf::Time								getElapsedPowerTime();
		
		void									setTileSize(sf::Vector2u tileSize);
		void									setMapSize(sf::Vector2i mapSize);
		float									getWallet() const;
		std::string								getFormatedWallet() const;
		void									addWallet(float money);
		int										getLevel() const;
		void									levelUp();

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

		float									travelDistance_;
		std::size_t								directionIndex_;
		bool									power_;
		sf::Time								elapsedPowerTime_;
		bool									shouldBeAffraid_;
		sf::Time								affraidElapsedTime_;
		sf::Time								powerCherryBlinkTime_;
		bool									blinkState_;
		float									totalPowerTime_;

	};
}

