#include "World.h"
#include <set>
#include <memory>
#include <SFML/Graphics/RenderTarget.hpp>
#include "Utility.h"
#include "Actor.h"
#include "FontManager.h"
#include <sstream>
#include <iomanip>
#include <string>
#include "DataTables.h"
#include <algorithm>
#include <utility>


namespace GEX
{
	namespace
	{
		const std::map<int, PickupData> TABLE = initializePickupData();
		const std::map<std::string, int> PARAMETERS = initializeParametersData();
	}

	World::World(sf::RenderTarget& outputTarget, SoundPlayer& sounds)
		: target_(outputTarget)
		, sounds_(sounds)
		, worldView_(outputTarget.getDefaultView())
		, textures_()
		, sceneGraph_()
		, sceneLayers_()
		, worldBounds_(0.f, 0.f, worldView_.getSize().x, worldView_.getSize().y)
		, spawnPosition_(worldView_.getSize().x / 2.f, worldBounds_.height - (worldView_.getSize().y / 2.f))
		, scrollSpeed_(0.f)
		, counter_(1)
		, orientation_(1)
		, commandQueue_()
		, lastCheckedScore_(0)
		, scoreText_()
		, livesText_()
		, map_()
		, tileMap_()
		, mapOverlay_("Media/Textures/tileMapOverlay.csv")
		, playerOrdersText_()
		, ordersTitle_()
		, ordersText_()
		, playerOrdersTitle_()
		, bakeryOrders_()
		, playerOrders_()
		, pickupTiles_(TABLE.at(0).pickupTiles)
		, pickupTime_(sf::seconds(0))
		, blinkTime_(sf::seconds(0))
		, blink_(0)
		, deliveredOrders_(0)

	{
		sceneTexture_.create(target_.getSize().x, target_.getSize().y);

		// Load all textures
		loadTextures();

		// Prepare the view
		worldView_.setCenter(spawnPosition_);

		// Build the world
		buildScene();
	}

	void World::update(sf::Time dt, CommandQueue& commands)
	{
		// run all commands in the command queue
		while (!commandQueue_.isEmpty())
		{
			sceneGraph_.onCommand(commandQueue_.pop(), dt);
		}

		// All scene nodes should be updated
		sceneGraph_.update(dt, commands);

		// Check if there are any enemy inside of the battlefield and spawn it
		//updateSound();

		//Update orders
		updateOrders(dt);

		//Pickup orders
		pickup(dt);

		//Check for Delivery orders
		delivery();

		//Level up
		levelUp();

		// Update Texts
		updateTexts();

		//Control the blink tiles
		updateBlink(dt);
	}

	//Update the score and live text
	void World::updateTexts()
	{
		//Update texts
		scoreText_.setString("Level: " + std::to_string(player_->getLevel()));
		livesText_.setString("Wallet: $" + player_->getFormatedWallet());

		//change color for the last $50 ;)
		livesText_.setFillColor(sf::Color::White);
		if (player_->getWallet() <= 50)
		{
			livesText_.setFillColor(sf::Color::Red);
		}
	}

	//Get the view bounds
	sf::FloatRect World::getViewBounds() const
	{
		return sf::FloatRect(worldView_.getCenter() - worldView_.getSize() / 2.f, worldView_.getSize());
	}

	//Get the active game area - Battle Field
	sf::FloatRect World::getBattlefieldBounds() const
	{
		sf::FloatRect bounds = getViewBounds();
		bounds.top -= 100.f;
		bounds.height += 100.f;
		return bounds;
	}

	//Update sounds - remove those that are stopped
	void World::updateSound()
	{
		sounds_.setListenerPosition(player_->getWorldPosition());
		sounds_.removeStoppedSounds();
	}

	//Spaw a new player
	void World::spawnPlayer()
	{
		std::unique_ptr<Actor> Car(new Actor(ActorType::Car, textures_, &map_, &mapOverlay_));
		Car->setState(Actor::State::HorizontalRight); //Set start state
		Car->setTileSize(tileMap_.getTileSize());
		Car->setTilePosition(sf::Vector2i(0, 5));
		Car->setMapSize(sf::Vector2i(MAPX, MAPY));
		player_ = Car.get();
		sceneLayers_[UpperAir]->attachChild(std::move(Car));
	}

	//Draw the order texts
	void World::drawOrderText()
	{
		for (auto it = playerOrdersText_.begin(); it != playerOrdersText_.end(); it++) {
			target_.draw(*it);
		}
		for (auto it = ordersText_.begin(); it != ordersText_.end(); it++) {
			target_.draw(*it);
		}
	}

	//Clear Order Text
	void World::clearOrderText()
	{
		for (int i = 0; i < 5; i++) {
			playerOrdersText_[i].setFillColor(sf::Color::Yellow);
			playerOrdersText_[i].setString("$---.-- (-:--)");
			ordersText_[i].setFillColor(sf::Color::Yellow);
			ordersText_[i].setString("$---.-- (-:--)");
		}
	}

	void World::updateOrders(sf::Time dt)
	{
		//clear orders
		clearOrderText();

		//Should I create a new order?
		if (randomInt(player_->getLevel() + 60) < player_->getLevel()) {
			//generate a new order and save at the bakery list
			bakeryOrders_.push_back(new Order());
		}

		//Update bakery orders
		for (auto it = bakeryOrders_.begin(); it != bakeryOrders_.end(); it++) {
			(*it)->update(dt, player_->getTilePosition());
		}
		//Update player orders
		for (auto it = playerOrders_.begin(); it != playerOrders_.end(); it++) {
			(*it)->update(dt, player_->getTilePosition());
		}

		updateOrdersText();
	}

	void World::updateOrdersText()
	{
		int counter = 0;

		//Update bakery orders text
		for (auto it = bakeryOrders_.begin(); it != bakeryOrders_.end(); it++) {
			if ((*it)->isExpired()) {
				ordersText_.at(counter).setString("-CANCELED-");
			}
			else
			{
				ordersText_.at(counter).setString("$" + formatValue((*it)->getValue()) + " - " + formatTime((*it)->getTime()));
			}
			ordersText_.at(counter).setFillColor((*it)->getColor());
			if (++counter == 5) {
				break;
			}
		}

		//Re-initialize counter variable
		counter = 0;
		//Update player orders text
		for (auto it = playerOrders_.begin(); it != playerOrders_.end(); it++) {
			if ((*it)->isExpired()) {
				playerOrdersText_.at(counter).setString("-CANCELED-");
			}
			else
			{
				playerOrdersText_.at(counter).setString("$" + formatValue((*it)->getValue()) + " - " + formatTime((*it)->getTime()));
			}
			playerOrdersText_.at(counter).setFillColor((*it)->getColor());
			if (++counter == 5) {
				break;
			}
		}
	}

	//Format time for display
	std::string World::formatTime(sf::Time time)
	{
		float ftime = time.asSeconds();
		int minutes = ftime / 60;
		int seconds = ftime - minutes * 60;
		std::stringstream ss;
		ss << minutes << ":";
		seconds < 10 ? ss << "0" << seconds : ss << seconds;
		return ss.str();
	}

	//Format float value to display 
	std::string World::formatValue(float value)
	{
		std::stringstream ss;
		ss << std::fixed << std::setprecision(2) << value;
		return ss.str();
	}

	void World::pickup(sf::Time dt)
	{
		//Check if player is stoped at the pickup point
   		if (std::find(pickupTiles_.begin(), pickupTiles_.end(), player_->getTilePosition()) != pickupTiles_.end())
		{
			pickupTime_ += dt;
		}
		else
		{
			pickupTime_ = sf::seconds(0);
		}

		//Check if pickup time is more than 3 seconds
		if (pickupTime_.asSeconds() >= sf::seconds(PARAMETERS.at("PICKUPTIME")).asSeconds())
		{
			//Check how many orders the player may pickup
			int spotsAvailable = 5 - playerOrders_.size();
			//Check how many orders are available at the bakery
			int ordersAvailable = bakeryOrders_.size();

			//Define the amount of orders that will be picked up
			int ordersAmount = ordersAvailable > spotsAvailable ? spotsAvailable : ordersAvailable;

			for (int i = 0; i < ordersAmount; i++)
			{
				playerOrders_.push_back(std::move(bakeryOrders_.front()));
				bakeryOrders_.pop_front();
			}
		}
	}

	void World::delivery()
	{
		std::list<Order*>::iterator last = playerOrders_.end();
		//Check for any delivery
		for (std::list<Order*>::iterator it = playerOrders_.begin(); it != playerOrders_.end(); it++) {
			if (last != playerOrders_.end())
			{
				playerOrders_.erase(last);
				last = playerOrders_.end();
			}
			if (!(*it)->isExpired() && (*it)->isDelivered())
			{
				player_->addWallet((*it)->getTip());
				deliveredOrders_++;
				last = it;
			}
		}
		//exclude if the last of the list was delivered
		if (last != playerOrders_.end())
		{
			playerOrders_.erase(last);
			last = playerOrders_.end();
		}
	}

	//Check if there are spots left to add new orders
	bool World::playerHasSpotsLeft() const
	{
		int spots = 0;
		for (auto it = playerOrders_.begin(); it != playerOrders_.end(); it++) {
			if ((*it)->isExpired()) {
				spots++;
			}
		}
		if (spots >= 5) {
			return false;
		}
		return true;
	}

	void World::drawActionTiles()
	{
		if (!blink_) {
			return;
		}
		//Draw a tile
		sf::RectangleShape rectangle(sf::Vector2f(16, 16));

		//Draw pickups tile
		if (bakeryOrders_.size() > 0)
		{
			rectangle.setFillColor(sf::Color(sf::Color::White.r, sf::Color::White.g, sf::Color::White.b, 60));
			for (int i = 0; i < pickupTiles_.size(); i++)
			{
				rectangle.setPosition(sf::Vector2f(pickupTiles_.at(i).x * 16, pickupTiles_.at(i).y * 16));
				target_.draw(rectangle);
			}
		}

		//Draw delivery tiles
		if (playerOrders_.size() > 0)
		{
			std::vector<sf::Vector2i> positions;
			for (auto it = playerOrders_.begin(); it != playerOrders_.end(); it++)
			{
				std::vector<sf::Vector2i> tmppositions = (*it)->getDeliveryTiles();
				for (int i = 0; i < tmppositions.size(); i++) {
					if (!(std::find(positions.begin(), positions.end(), tmppositions.at(i)) != positions.end()))
					{
						if (!(*it)->isExpired())
						{
							rectangle.setFillColor(sf::Color(((*it)->getColor()).r, ((*it)->getColor()).g, ((*it)->getColor()).b, 40));
							rectangle.setPosition(sf::Vector2f(tmppositions.at(i).x * 16, tmppositions.at(i).y * 16));
							target_.draw(rectangle);
							positions.push_back(tmppositions.at(i));
						}
					}
				}
				
			}
		}
	}

	void World::updateBlink(sf::Time dt)
	{
		blinkTime_ += dt;

		if (blink_ && blinkTime_.asSeconds() > sf::seconds(1).asSeconds())
		{
			blink_ = 0;
			blinkTime_ = sf::seconds(0);
		}
		else if (!blink_ && blinkTime_.asSeconds() > sf::seconds(0.5).asSeconds())
		{
			blink_ = 1;
			blinkTime_ = sf::seconds(0);
		}
	}

	void World::levelUp()
	{
		if (deliveredOrders_ / PARAMETERS.at("NUMBERORDERSLEVELUP") > player_->getLevel())
		{
			player_->levelUp();
		}
	}

	//Draw the world
	void World::draw()
	{
			target_.clear(sf::Color::Black);
			target_.setView(worldView_);
			map_.reload();
			tileMap_.load(&map_, MAPX, MAPY);
			target_.draw(tileMap_);
			mapOverlay_.reload();
			tileMap_.load(&mapOverlay_, MAPX, MAPY);
			target_.draw(tileMap_);
			target_.draw(sceneGraph_);
			target_.draw(scoreText_);
			target_.draw(livesText_);
			target_.draw(playerOrdersTitle_);
			target_.draw(ordersTitle_);
			drawOrderText();
			drawActionTiles();
	}

	//Get the comman queue
	CommandQueue & World::getCommandQueue()
	{
		return commandQueue_;
	}

	/*
	Check if the player is dead 
	if player is dead, lose one live and respawn the player
	if player does not have any lives left, end the game
	*/
	bool World::hasAlivePlayer()
	{

		if (player_->isMarkedForRemoval() || !playerHasSpotsLeft())
		{
			return false;
		}

		return true;
	}

	//Load textures
	void World::loadTextures()
	{
		textures_.load(GEX::TextureID::Jungle,		 "Media/Textures/background.png");
		textures_.load(GEX::TextureID::PacmanAtlas,  "Media/Textures/carAtlas.png");
	}

	//Build the world
	void World::buildScene()
	{
		// Initialize layers
		for (int i = 0; i < LayerCount; ++i)
		{
			auto category = (i == UpperAir) ? Category::Type::AirSceneLayer : Category::Type::None;
			SceneNode::Ptr layer(new SceneNode(category));
			sceneLayers_.push_back(layer.get());
			sceneGraph_.attachChild(std::move(layer));
		}

		// Adding Characters

		spawnPlayer();

		scoreText_.setFont(GEX::FontManager::getInstance().get(GEX::FontID::Main));
		scoreText_.setPosition(5.0f, 820.0f);
		scoreText_.setFillColor(sf::Color::White);
		scoreText_.setCharacterSize(25.0f);
		scoreText_.setString("Level: " + std::to_string(player_->getLevel()));

		livesText_.setFont(GEX::FontManager::getInstance().get(GEX::FontID::Main));
		livesText_.setPosition(5.0f, 860.0f);
		livesText_.setCharacterSize(25.0f);
		livesText_.setFillColor(sf::Color::White);
		livesText_.setString("Wallet: $" + player_->getFormatedWallet());

		//Display Player order title
		playerOrdersTitle_.setFont(GEX::FontManager::getInstance().get(GEX::FontID::Main));
		playerOrdersTitle_.setPosition(700.0f, 895.0f);
		playerOrdersTitle_.setCharacterSize(25.0f);
		playerOrdersTitle_.setFillColor(sf::Color::White);
		playerOrdersTitle_.setRotation(270);
		playerOrdersTitle_.setString("Player\nOrders");

		//Display Player order title
		ordersTitle_.setFont(GEX::FontManager::getInstance().get(GEX::FontID::Main));
		ordersTitle_.setPosition(1200.0f, 895.0f);
		ordersTitle_.setCharacterSize(24.0f);
		ordersTitle_.setFillColor(sf::Color::White);
		ordersTitle_.setRotation(270);
		ordersTitle_.setString("Delivery\nOrders");


		sf::Text tmp;
		tmp.setFont(GEX::FontManager::getInstance().get(GEX::FontID::Main));
		tmp.setCharacterSize(16.0f);
		tmp.setFillColor(sf::Color::Yellow);
		tmp.setString("$---.-- (-:--)");

		for (int i = 0; i < 5; i++) {
			float y = 804.0 + i * 18;
			tmp.setPosition(770.0, y);
			playerOrdersText_.push_back(tmp);
			tmp.setPosition(1270.0f, y);
			ordersText_.push_back(tmp);
		}
	}
}