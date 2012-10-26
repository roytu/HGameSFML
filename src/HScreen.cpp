#include "HScreen.h"

HScreen* HScreen::instance;
sf::Color HScreen::BACKGROUND_COLOR = sf::Color(255, 255, 255);
sf::View* HScreen::view;

HScreen::HScreen()
{
	instance = this;
	screen = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML window");
	view = new sf::View(sf::Vector2f(0, 0), sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));
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

void HScreen::setView(double centerX, double centerY)
{
    view->SetCenter(centerX, centerY);
}
