#pragma once
#include "SceneNode.h"

namespace GEX
{
	class commandQueue;

	class Entity : public SceneNode
	{
	public:

		explicit		Entity(int points);

		void			setVelocity(sf::Vector2f velocity);
		void			setVelocity(float vx, float vy);
		sf::Vector2f	getVelocity() const;

		virtual void	accelerate(sf::Vector2f velocity);
		virtual void	accelerate(float vx, float vy);

		//Hits
		int				getHitpoints() const;
		void			damage(int points);
		void			repair(int points);
		void			destroy(); //set hitpoints to 0
		bool			isDestroyed() const override;
		virtual void	remove();

	protected:
		virtual void	updateCurrent(sf::Time dt, CommandQueue& Commands) override;

	private:
		sf::Vector2f	velocity_;
		int				hitpoints_;

	};
}

