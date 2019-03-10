#pragma once

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include "ResourceIdentifier.h"
#include <SFML/System/Vector2.hpp>

#include <map>
#include <memory>
#include <list>
#include <string>

namespace GEX
{
	class SoundPlayer
	{
	public:
																	SoundPlayer();
																	~SoundPlayer() = default;
																	SoundPlayer(const SoundPlayer&) = delete;
		SoundPlayer&												operator=(const SoundPlayer&) = delete;
		void														play(SoundEffectID effect);
		void														play(SoundEffectID effect, sf::Vector2f position);
		void														removeStoppedSounds();
		void														setListenerPosition(sf::Vector2f position);
		sf::Vector2f												getListenerPosition() const;

	private:
		void														loadBuffer(SoundEffectID id, const std::string path);

	private:
		std::map<SoundEffectID, std::unique_ptr<sf::SoundBuffer>>	soundBuffers_;
		std::list<sf::Sound>										sounds_;
		float														volume_;
	};
}

