#include "TitleState.h"
#include "TextureManager.h"
#include "Utility.h"
#include "FontManager.h"

TitleState::TitleState(GEX::StateStack& stack, Context context)
	: GEX::State(stack, context)
	, backgroundSprite_()
	, text_()
	, showText_(true)
	, textEffectTime_(sf::Time::Zero)
{

	backgroundSprite_.setTexture(context.textures_->get(GEX::TextureID::TitleScreen));

	text_.setFont(GEX::FontManager::getInstance().get(GEX::FontID::Main));
	text_.setString("Press any key to start");
	centerOrigin(text_);

	text_.setPosition(context.window_->getView().getSize() / 2.f);

	context.music_->play(GEX::MusicID::Game);
}

//Draw the background and text
void TitleState::draw()
{
	auto& window = *getContext().window_;

	window.draw(backgroundSprite_);

	if (showText_) {
		window.draw(text_);
	}
}

//Blink the press key text
bool TitleState::update(sf::Time dt)
{
	textEffectTime_ += dt;

	if (textEffectTime_ >= sf::seconds(0.5f))
	{
		showText_ = !showText_;
		textEffectTime_ = sf::Time::Zero;
	}

	return true;
}

bool TitleState::handleEvent(const sf::Event & event)
{
	if (event.type != sf::Event::KeyPressed)
	{
		return false;
	}

	requestStackPop();
	requestStackPush(GEX::StateID::Game);

	return false;
}



