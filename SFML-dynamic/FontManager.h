#pragma once
#include <map>
#include <memory>
#include "ResourceIdentifier.h"
#include <string>
#include <SFML/Graphics/Font.hpp>


namespace GEX
{
	class FontManager
	{
	private:
		FontManager() = default;

	public:
		static FontManager&									getInstance();

		void												load(FontID id, const std::string& path);
		sf::Font&											get(FontID id) const;

	private:
		static FontManager*									instance_;
		std::map<FontID, std::unique_ptr<sf::Font>>			fonts_;
	};

}