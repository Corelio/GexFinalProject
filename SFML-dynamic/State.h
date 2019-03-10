#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include "TextureManager.h"
#include "StatesIdentifiers.h"
#include <memory>
#include "MusicPlayer.h"
//#include "StateStack.h"

namespace GEX
{
	//forward declarations
	class PlayerControl;
	class StateStack;
	class SoundPlayer;

	class State
	{
	public:
		typedef std::unique_ptr<State> Ptr;
		struct Context
		{
			Context(sf::RenderWindow& window, 
					TextureManager& texture, 
					PlayerControl& playercontrol, 
					MusicPlayer& music_, 
					SoundPlayer& sound_
			);

			sf::RenderWindow*	window_;
			TextureManager*		textures_;
			PlayerControl*		player_;
			MusicPlayer*		music_;
			SoundPlayer*		sound_;

		};
	public:

								State(StateStack& stack, Context context);
		virtual					~State();

		virtual void			draw() = 0;
		virtual bool			update(sf::Time) = 0;
		virtual bool			handleEvent(const sf::Event& event) = 0;

	protected:
		void					requestStackPush(StateID stateID);
		void					requestStackPop();
		void					requestStackClear();

		Context					getContext() const;

	private:
		StateStack*				stack_;
		Context					context_;
	};
}

