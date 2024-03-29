/**
* @file
* SceneNode.h
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


