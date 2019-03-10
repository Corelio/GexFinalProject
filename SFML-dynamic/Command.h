#pragma once
#include <SFML/System/Time.hpp>
#include <functional>
#include <cassert>
#include "Category.h"

namespace GEX
{
	//Forward Declaration
	class SceneNode;

	struct Command
	{
	public:
		Command();
		
		std::function<void(SceneNode&, sf::Time)>	action;
		unsigned int								category;
	};

	template <typename GameObject, typename Function>
	std::function<void(SceneNode&, sf::Time)>	derivedAction(Function fn)
	{
		return [=](SceneNode& node, sf::Time dt) {
			assert(dynamic_cast<GameObject*>(&node) != nullptr);
			fn(static_cast<GameObject&>(node), dt);


		};
	}
}
