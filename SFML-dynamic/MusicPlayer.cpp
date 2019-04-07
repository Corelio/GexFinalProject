#include "MusicPlayer.h"


namespace GEX {
	MusicPlayer::MusicPlayer()
		: music_()
		, filenames_()
		, volume_(100)
	{
		filenames_[MusicID::Game] = "Media/Music/game.wav";
	}

	void MusicPlayer::play(MusicID theme)
	{
		if (!music_.openFromFile(filenames_.at(theme)))
		{
			throw std::runtime_error("Music could not open file");
		}

		music_.setVolume(volume_);
		music_.setLoop(true);
		music_.play();
	}

	void MusicPlayer::stop()
	{
		music_.stop();
	}

	void MusicPlayer::setPaused(bool paused)
	{
		if(paused)
		{
			music_.pause();
		}
		else
		{
			music_.play();
		}
	}

	void MusicPlayer::setVolume(float volume)
	{
		volume_ = volume;
		music_.setVolume(volume_);
	}


	
}