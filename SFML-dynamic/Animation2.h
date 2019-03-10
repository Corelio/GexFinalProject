#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <vector>

using Frame = sf::IntRect;

namespace GEX
{
	class Animation2
	{
	public:
		//Constructors
		explicit			Animation2(bool repeat = true);

		//Getters and setters
		void				addFrame(Frame frame);
		void				addFrameSet(std::vector<Frame> frames); //Updated
		void				setDuration(sf::Time time);
		sf::Time			getDuration() const;
		void				setRepeating(bool repeat);
		bool				isRepeating() const;

		//Methods
		void				restart();
		bool				isFinished() const;

		Frame				getCurrentFrame() const;

		Frame				update(sf::Time dt);

	private:
		std::vector<Frame>	frames_;
		std::size_t			currentFrame_;
		sf::Time			duration_;
		sf::Time			elapsedTime_;
		bool				repeat_;
	};
}

