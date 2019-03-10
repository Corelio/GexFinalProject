#pragma once

#include <SFML\Graphics\Transformable.hpp>
#include <SFML\Graphics\Drawable.hpp>
#include <SFML\System\Time.hpp>
#include "Category.h"
#include <set>

#include <vector>
#include <memory>
#include <algorithm>

namespace GEX
{
	class CommandQueue;
	struct Command;

	class SceneNode : public sf::Transformable, public sf::Drawable
	{
	public:
		//typedef std::unique_ptr<SceneNode> Ptr;
		using Ptr = std::unique_ptr<SceneNode>;
		using Pair = std::pair<SceneNode*, SceneNode*>;

	public:
		SceneNode(Category::Type category = Category::Type::None);
		virtual	~SceneNode() = default;
		SceneNode(const SceneNode&) = delete;
		SceneNode&				operator=(SceneNode&) = delete;

		void					attachChild(Ptr child);
		SceneNode::Ptr			detachChild(const SceneNode& ptr);
								
		void					update(sf::Time dt, CommandQueue& commands);
		void					onCommand(const Command& command, sf::Time dt);
		virtual unsigned int	getCategory() const;

		sf::Vector2f			getWorldPosition() const;
		sf::Transform			getWorldTransform() const;

		virtual sf::FloatRect	getBoundingBox() const;
		void					drawBoundingBox(sf::RenderTarget& target, sf::RenderStates states) const;

		void					checkSceneCollision(SceneNode& rootNode, std::set<Pair>& collisionPair);
		void					checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPair);

		virtual bool			isDestroyed() const;
		virtual bool			isMarkedForRemoval() const;
		void					removeWrecks();

	private:
		SceneNode*				parent_;
		std::vector<Ptr>		children_;

		Category::Type			category_;

	protected:
		// Update the tree
		virtual void			updateCurrent(sf::Time dt, CommandQueue& commands);
		void					updateChildren(sf::Time dt, CommandQueue& commands);

		//draw the tree
		void					draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		void					drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
	};

	float distance(const SceneNode& lhs, const SceneNode& rhs);
	bool  collision(const SceneNode& lhs, const SceneNode& rhs);
}


