#include "SoundPlayer.h"
#include <SFML/Audio/Listener.hpp>
#include <cassert>

namespace
{
	// Sound coordinate system, point of view of a player in front of the screen:
	// X = left; Y = up; Z = back (out of the screen)
	const float ListenerZ = 300.f;
	const float Attenuation = 8.f;
	const float MinDistance2D = 200.f;
	const float MinDistance3D = std::sqrt(MinDistance2D*MinDistance2D + ListenerZ * ListenerZ);
}

namespace GEX
{

	SoundPlayer::SoundPlayer()
		: soundBuffers_()
		, sounds_()
		, volume_(100)
	{
		loadBuffer(SoundEffectID::AlliedGunfire, "Media/Sound/AlliedGunfire.wav");
		loadBuffer(SoundEffectID::EnemyGunfire, "Media/Sound/EnemyGunfire.wav");
		loadBuffer(SoundEffectID::Explosion1, "Media/Sound/Explosion1.wav");
		loadBuffer(SoundEffectID::Explosion2, "Media/Sound/Explosion2.wav");
		loadBuffer(SoundEffectID::LaunchMissile, "Media/Sound/LaunchMissile.wav");
		loadBuffer(SoundEffectID::CollectPickup, "Media/Sound/CollectPickup.wav");
		loadBuffer(SoundEffectID::Button, "Media/Sound/Button.wav");

		// Listener points towards the screen (default in SFML)
		sf::Listener::setDirection(0.f, 0.f, -1.f);
	}

	void SoundPlayer::play(SoundEffectID effect)
	{
		play(effect, getListenerPosition());
	}

	void SoundPlayer::play(SoundEffectID effect, sf::Vector2f position)
	{
		sounds_.push_back(sf::Sound());
		sf::Sound& sound = sounds_.back();

		sound.setBuffer(*soundBuffers_.at(effect));
		sound.setPosition(position.x, -position.y, 0);
		sound.setAttenuation(Attenuation);
		sound.setMinDistance(MinDistance3D);

		sound.setVolume(volume_);
		sound.play();
	}

	void SoundPlayer::removeStoppedSounds()
	{
		sounds_.remove_if([](const sf::Sound& s) {return s.getStatus() == sf::Sound::Stopped; });
	}

	void SoundPlayer::setListenerPosition(sf::Vector2f position)
	{
		sf::Listener::setPosition(position.x, -position.y, ListenerZ);
	}

	sf::Vector2f SoundPlayer::getListenerPosition() const
	{
		auto position = sf::Listener::getPosition();
		return sf::Vector2f(position.x, -position.y);
	}

	void SoundPlayer::loadBuffer(SoundEffectID id, const std::string path)
	{
		std::unique_ptr<sf::SoundBuffer> buffer(new sf::SoundBuffer);
		if (!buffer->loadFromFile(path))
		{
			throw std::runtime_error("Sound effect load failed");
		}

		auto inserted = soundBuffers_.insert(std::make_pair(id, std::move(buffer)));
		assert(inserted.second);
	}

}