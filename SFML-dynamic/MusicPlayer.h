/**
* @file
* MusicPlayer.h
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
