#include "SoundNode.h"


namespace GEX
{

	SoundNode::SoundNode(SoundPlayer& player)
		: SceneNode()
		, sounds_(player)
	{
	}

	void SoundNode::playSound(SoundEffectID sound, sf::Vector2f position)
	{
		sounds_.play(sound, position);
	}

	unsigned int SoundNode::getCategory() const
	{
		return Category::SoundEffect;
	}
}
