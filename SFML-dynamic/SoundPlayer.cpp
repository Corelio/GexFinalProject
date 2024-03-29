/**
* @file
* SoundPlayer.cpp
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
		loadBuffer(SoundEffectID::New, "Media/Sound/Call-bell-ding.wav");
		loadBuffer(SoundEffectID::Delivery, "Media/Sound/delivery.wav");
		loadBuffer(SoundEffectID::Money, "Media/Sound/money.wav");
		loadBuffer(SoundEffectID::Error, "Media/Sound/error.wav");
		loadBuffer(SoundEffectID::Levelup, "Media/Sound/cheering.wav");
		loadBuffer(SoundEffectID::Go, "Media/Sound/go.wav");
		loadBuffer(SoundEffectID::No, "Media/Sound/no.wav");


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