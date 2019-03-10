#pragma once
#include "SceneNode.h"
#include "ResourceIdentifier.h"
#include "SoundPlayer.h"

namespace GEX
{
	class SoundPlayer;

	class SoundNode : public SceneNode
	{
	public:
		explicit		SoundNode(SoundPlayer& player);
		void			playSound(SoundEffectID sound, sf::Vector2f position);

		unsigned int	getCategory() const override;

	private:
		SoundPlayer&	sounds_;
	};
}
