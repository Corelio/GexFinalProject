#pragma once

#include <SFML/Audio/Music.hpp>
#include "ResourceIdentifier.h"
#include <map>
#include <string>

namespace GEX {
	class MusicPlayer
	{
	public:
											MusicPlayer();
											~MusicPlayer() = default;
											MusicPlayer(const MusicPlayer&) = delete;
		MusicPlayer&						operator=(const MusicPlayer&) = delete;

		void								play(MusicID theme);
		void								stop();
		void								setPaused(bool paused);
		void								setVolume(float volume);

	private:
		sf::Music							music_;
		std::map<MusicID, std::string>		filenames_;
		float								volume_;
	};

}
