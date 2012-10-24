#include "HScreen.h"

HScreen* HScreen::instance;
sf::Color HScreen::BACKGROUND_COLOR = sf::Color(255, 255, 255);

HScreen::HScreen()
{
	instance = this;
	screen = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML window");
}


HScreen::~HScreen()
{
}

HScreen* HScreen::getInstance()
{
	return instance;
}

sf::RenderWindow* HScreen::getScreen()
{
	return getInstance()->screen;
}
