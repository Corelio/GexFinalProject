#include "MenuState.h"
#include "Utility.h"
#include "FontManager.h"
#include "ResourceIdentifier.h"

MenuState::MenuState(GEX::StateStack& stack, Context context)
	: GEX::State(stack, context)
	, options_()
	, optionsIndex_(0)
{
	sf::Font& font = GEX::FontManager::getInstance().get(GEX::FontID::Main);
	backgroundSprite_.setTexture(context.textures_->get(GEX::TextureID::TitleScreen));

	//set up menu
	//Play Option
	sf::Text playOption;
	playOption.setFont(font);
	playOption.setString("Play");
	centerOrigin(playOption);
	playOption.setPosition(context.window_->getView().getSize() / 2.f);
	
	//Exit Option
	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setString("Exit");
	centerOrigin(exitOption);
	exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
	
	options_.push_back(playOption);
	options_.push_back(exitOption);

	updateOptionText();

	context.music_->play(GEX::MusicID::Game);
}

void MenuState::draw()
{
	auto& window = *getContext().window_;

	window.setView(window.getDefaultView());
	window.draw(backgroundSprite_);

	for (const sf::Text& text : options_)
	{
		window.draw(text);
	}
	
}

//All other states bellow this could be updated
bool MenuState::update(sf::Time dt)
{
	return true;
}

//handle key press event -> start game or exit
bool MenuState::handleEvent(const sf::Event & event)
{
	if (event.type != sf::Event::KeyPressed)
	{
		return true;
	}
	if (event.key.code == sf::Keyboard::Return)
	{
		if (optionsIndex_ == Play)
		{
			requestStackPop();
			requestStackPush(GEX::StateID::Game);
		}
		else if (optionsIndex_ == Exit)
		{
			requestStackPop();
		}
	}
	else if (event.key.code == sf::Keyboard::Up)
	{
		if (optionsIndex_ > 0)
		{
			optionsIndex_--;
		}
		else
		{
			optionsIndex_ = options_.size() - 1;
		}
		updateOptionText();
	}
	else if (event.key.code == sf::Keyboard::Down)
	{
		if (optionsIndex_ < options_.size() - 1)
		{
			optionsIndex_++;
		}
		else
		{
			optionsIndex_ = 0;
		}
		updateOptionText();
	}

	return true;
}

//Change color of the menu options
void MenuState::updateOptionText()
{
	if (options_.empty())
	{
		return;
	}

	for (sf::Text& text : options_)
	{
		text.setFillColor(sf::Color::White);
		text.setOutlineColor(sf::Color::Black);
	}

	options_.at(optionsIndex_).setFillColor(sf::Color::Magenta);
}
