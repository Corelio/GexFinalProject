#pragma once

#include "json.hpp"
#include <vector>
#include <SFML/Graphics/Rect.hpp>

using nlohmann::json;

struct IntRect {

	IntRect(int l, int t, int w, int h) : left(l), top(t), width(w), height(h) {}
	int left;
	int top;
	int width;
	int height;
};

class JsonFrameParser
{
public:
									/**
									* Construct a jason frame parser object
									*
									* @param[in] path path to texture atlas
									*/
									JsonFrameParser(std::string path);

									/**
									* Return set of texture Rectangles for the named
									* animation. 
									* 
									* @param animationName the name of the animation, must match 
									*		 the begining of the name string for the animation in the 
									*		 json file.
									*
									* @return vector of Frames that make up the animation 
									*/
	std::vector<sf::IntRect>        getFramesFor(std::string animationName) const;

private:
	json              json_;
};



