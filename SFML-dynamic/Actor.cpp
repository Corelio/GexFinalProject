#include "Actor.h"
#include "TextureManager.h"
#include "JsonFrameParser.h"
#include "TextureManager.h"
#include "Utility.h"
#include "DataTables.h"
#include "TextNode.h"
#include <memory>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include "CommandQueue.h"

namespace GEX
{
	namespace
	{
		const std::map<ActorType, ActorData> TABLE = initializeActorData();
		const std::map<std::string, int> PARAMETERS = initializeParametersData();
	}

	Actor::Actor(ActorType type, const GEX::TextureManager& textures, Map* map, Map* mapOverlay)
		: Entity(100)
		, type_(type)
		, textures_(textures)
		, state_(State::HorizontalRight)
		, sprite_(textures.get(TABLE.at(type).texture))
		, direction_(Direction::Right)
		, travelDistance_(0.f)
		, directionIndex_(0)
		, power_(false)
		, elapsedPowerTime_(sf::seconds(4.f))
		, shouldBeAffraid_(false)
		, powerCherryBlinkTime_(sf::Time::Zero)
		, blinkState_(true)
		, totalPowerTime_(6.f)
		, tilePosition_(0, 5)
		, newDirection_(Direction::None)
		, wallet_(PARAMETERS.at("WALLET"))
		, level_(1)
		, delivering_(false)
		, validTiles_(TABLE.at(type).validTiles)
		, map_(map)
		, mapOverlay_(mapOverlay)

	{	  
		//Load animations map
		for (auto a : TABLE.at(type).animations)
		{
			animations_[a.first] = a.second;
		}

		//Start with an empty sprite to prevent the flash of the whole texture
		sprite_.setTextureRect(sf::IntRect());

		//center the sprite
		centerOrigin(sprite_);
	}

	//Returns the Actor category
	unsigned int Actor::getCategory() const
	{
		return Category::Car;
	}

	//Get the bounding box for collisions
	sf::FloatRect Actor::getBoundingBox() const
	{
		auto box = getWorldTransform().transformRect(sprite_.getGlobalBounds());
		box.width -= 30; // tighten up bounding box for more realistic collisions
		box.left += 15;
		return box;
	}

	//Set the actor state
	void Actor::setState(State state)
	{
		state_ = state;
		animations_[state_].restart();
	}

	//Get the actor state
	Actor::State Actor::getState() const
	{
		return state_;
	}

	//Get the actor direction - used to rotate the player
	Actor::Direction Actor::getDirection() const
	{
		return direction_;
	}

	Actor::Direction Actor::getNewDirection() const
	{
		return newDirection_;
	}

	void Actor::setDirection(Direction direction)
	{
		direction_ = direction;
	}

	void Actor::setNewDirection(Direction direction)
	{
		newDirection_ = direction;
	}

	//Set the actor position on the tile system
	void Actor::setTilePosition(sf::Vector2i position)
	{
		tilePosition_ = position;
	}

	sf::Vector2i Actor::getTilePosition() const
	{
		return tilePosition_;
	}

	//Update Actor state
	void Actor::updateStates(sf::Time dt)
	{
		//If actor hitppoints is zero -> start death animation
		if (isDestroyed()) {
			state_ = State::Dead;
		}
		if (direction_ == Direction::Right) {
			state_ = State::HorizontalRight;
		}
		else if (direction_ == Direction::Left) {
			state_ = State::HorizontalLeft;
		}
		else if (direction_ == Direction::Up) {
			state_ = State::VerticalUp;
		}
		else if (direction_ == Direction::Down) {
			state_ = State::VerticalDown;
		}
	}

	//Update Actor
	void Actor::updateCurrent(sf::Time dt, GEX::CommandQueue & commands)
	{
		std::cout << tilePosition_.x << " || " << tilePosition_.y << std::endl;
		//Update player position
		updatePosition();

		//Update States
		updateStates(dt);

		//Get the animation
		auto rec = animations_.at(state_).update(dt);

		//Set the sprite position over the texture
		sprite_.setTextureRect(rec);

		//Center the sprite
		centerOrigin(sprite_);

		//Update the entity, only if the Actor is not dead
		if (state_ != State::Dead) {// dont move it while dying
			Entity::updateCurrent(dt, commands);
		}
		std::cout << tilePosition_.x << " || " << tilePosition_.y << std::endl;
	}

	//Draw the Actor
	void Actor::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
	{
		if (tilePosition_.y < MAPY) {
			target.draw(sprite_, states);
		}
		
	}

	//Updates player position
	void Actor::updatePosition()
	{
		if (newDirection_ != Direction::None) {
			if (newDirection_ == Direction::Stop) {
				newDirection_ = Direction::None;
				delivering_ = true;
				return; //do not move
			}
			else {
				if (!delivering_)
				{
					if (checkMovement())
					{
						if (!isOppositeDirection())
						{
							direction_ = newDirection_;
						}
					}
					newDirection_ = Direction::None;
				}
				else {
					newDirection_ = Direction::None;
					return; //do not try to move - player is in stop mode
				}
			}
		}
		else {
			delivering_ = false;
		}

		//Check direction - set new tile position - fix position if out of map

		//Check if next is an obstacle - that will prevent any movement up and down over the obstacle
		if(isNextAnObstacle()) {
			int orientation = randomInt(2);
			if (orientation) {
				direction_ = Direction::Right;
			}
			else {
				direction_ = Direction::Left;
			}
		}

		//Move up or down
		if (direction_ == Direction::Up) {
			tilePosition_.y--;
			if (tilePosition_.y < -5) {
				direction_ = Direction::Down;
			}
		}
		else if (direction_ == Direction::Down) {
			tilePosition_.y++;
			if (tilePosition_.y > mapSize_.y+5) {
				direction_ = Direction::Up;
			}
		}
		
		if (direction_ == Direction::Left) {
			tilePosition_.x--;
			if (tilePosition_.x < -5) {
				direction_ = Direction::Right;
			}
		}
		else if (direction_ == Direction::Right) {
			tilePosition_.x++;
			if (tilePosition_.x > mapSize_.x+5) {
				direction_ = Direction::Left;
			}
		}
		float x = tileSize_.x * tilePosition_.x + 0.5*tileSize_.x;
		float y = tileSize_.y * tilePosition_.y + 0.5*tileSize_.y;
		setPosition(x, y);
	}

	bool Actor::checkMovement()
	{
		sf::Vector2i tmpPosition(tilePosition_);
		if (newDirection_ == Direction::Left) {
			tmpPosition.x--;
		}
		else if (newDirection_ == Direction::Right) {
			tmpPosition.x++;
		}
		else if (newDirection_ == Direction::Up) {
			tmpPosition.y--;
		}
		else if (newDirection_ == Direction::Down) {
			tmpPosition.y++;
		}
		int maptile = map_->getTile(tmpPosition.x, tmpPosition.y);
		int overlayMaptile = mapOverlay_->getTile(tmpPosition.x, tmpPosition.y);

		if (
			std::find(validTiles_.begin(), validTiles_.end(), maptile) != validTiles_.end()
			&& (
				overlayMaptile == -1
				|| std::find(validTiles_.begin(), validTiles_.end(), overlayMaptile) != validTiles_.end()
				)
			)
		{
			return true;
		}

		return false;
	}

	//prevent the user to switch to the opposite direction 
	bool Actor::isOppositeDirection()
	{
		if (newDirection_ == Direction::Left && direction_ == Direction::Right) {
			return true;
		}
		else if (newDirection_ == Direction::Right && direction_ == Direction::Left) {
			return true;
		}
		else if (newDirection_ == Direction::Up && direction_ == Direction::Down) {
			return true;
		}
		else if (newDirection_ == Direction::Down && direction_ == Direction::Up) {
			return true;
		}
		else {
			return false;
		}
	}

	//Check if next position
	bool Actor::isNextAnObstacle()
	{
		//check if movement is vertical - onlyvertical streets will have obstacles
		if (!(direction_ == Direction::Up || direction_ == Direction::Down)) {
			return false;
		}

		//Fake movement
		sf::Vector2i tmpPosition(tilePosition_);
		if (direction_ == Direction::Up) {
			tmpPosition.y-=2;
		}
		else if (direction_ == Direction::Down) {
			tmpPosition.y+=2;
		}
		//Check the overlay tile Id
		int overlayMaptile = mapOverlay_->getTile(tmpPosition.x, tmpPosition.y);
		//If is not -1 is an obstacle
		if (overlayMaptile != -1)
		{
			return true;
		}

		return false;
	}

	//Check if the actor is read to be removed 
	bool Actor::isMarkedForRemoval() const
	{
		return wallet_ < 0; 
	}

	// Return the power state of the actor
	bool Actor::hasPower() const
	{
		return power_;
	}

	// Adds power to the actor also starts the elapsed countdown to remove the power
	void Actor::addPower()
	{
		power_ = true;
		elapsedPowerTime_ = sf::seconds(totalPowerTime_);
	}

	// Removes the power of the Actor and sets the elapsed power time to Zero
	void Actor::removePower()
	{
		power_ = false;
		elapsedPowerTime_ = sf::Time::Zero;
	}

	// Return if the actor should be affraid of the other actors
	void Actor::shouldBeAffraid(bool beAffraid)
	{
		shouldBeAffraid_ = beAffraid;
	}

	// Set the amount of time remaining for the affraid mode
	void Actor::setAffraidElapsedTime(sf::Time affraidElapsedTime)
	{
		affraidElapsedTime_ = affraidElapsedTime;
	}

	// Return the time remaining for the Power
	sf::Time Actor::getElapsedPowerTime()
	{
		return elapsedPowerTime_;
	}

	void Actor::setTileSize(sf::Vector2u tileSize)
	{
		tileSize_ = tileSize;
	}

	void Actor::setMapSize(sf::Vector2i mapSize)
	{
		mapSize_ = mapSize;
	}

	float Actor::getWallet() const
	{
		return wallet_;
	}

	std::string Actor::getFormatedWallet() const
	{
		std::stringstream ss;
		ss << std::fixed << std::setprecision(2) << wallet_;
		return ss.str();
	}

	void Actor::addWallet(float money)
	{
		wallet_ += money;
	}

	int Actor::getLevel() const
	{
		return level_;
	}

	void Actor::levelUp()
	{
		level_++;
	}

	void Actor::playLocalSound(CommandQueue & commands, SoundEffectID effect)
	{
		Command playSoundCommand;
		playSoundCommand.category = Category::SoundEffect;
		playSoundCommand.action = derivedAction<SoundNode>(
			std::bind(&SoundNode::playSound, std::placeholders::_1, effect, getWorldPosition())
			);

		commands.push(playSoundCommand);
	}


}
