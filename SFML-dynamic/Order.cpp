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
		time_(sf::seconds(0)),
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
			time_ += dt;
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
		if (time_.asSeconds() > sf::seconds(PARAMETERS.at("EXPIRETIME")).asSeconds())
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
		//Only calculate tip for delivered and not expired deliveries
		if (isDelivered() && !isExpired()) {
			float percentage = 0.05;

			if (time_.asSeconds() < sf::seconds(PARAMETERS.at("EXPIRETIME")*.065).asSeconds())
			{
				percentage = 0.25;
			}
			else if (time_.asSeconds() < sf::seconds(PARAMETERS.at("EXPIRETIME")*.125).asSeconds())
			{
				percentage = 0.20;
			}
			else if (time_.asSeconds() < sf::seconds(PARAMETERS.at("EXPIRETIME")*.25).asSeconds())
			{
				percentage = 0.15;
			}
			else if (time_.asSeconds() < sf::seconds(PARAMETERS.at("EXPIRETIME")*.313).asSeconds())
			{
				percentage = 0.10;
			}
			else if (time_.asSeconds() > sf::seconds(PARAMETERS.at("EXPIRETIME")*.375).asSeconds() && time_.asSeconds() < sf::seconds(PARAMETERS.at("EXPIRETIME")/2).asSeconds())
			{
				percentage = 0.0;
			}
			else if (time_.asSeconds() > sf::seconds(PARAMETERS.at("EXPIRETIME")/2).asSeconds())
			{
				//If the delivery time is over 2 min, charge the player the value
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