#include "LDraw.h"

void LDraw::DrawRect(double x, double y, double w, double h, sf::Color color)
{
	HScreen::getScreen()->Draw(sf::Shape::Rectangle(static_cast<float>(x), static_cast<float>(y), static_cast<float>(x + w), static_cast<float>(y + h), color));
}
void LDraw::DrawCircle(double x, double y, double r, sf::Color color)
{
    HScreen::getScreen()->Draw(sf::Shape::Circle(static_cast<float>(x), static_cast<float>(y), static_cast<float>(r), color));
}

void LDraw::DrawImage(sf::Image* img, double x, double y)
{
    sf::Sprite s(*img);
    s.SetX(static_cast<float>(x));
    s.SetY(static_cast<float>(y));
    HScreen::getScreen()->Draw(s);
}

void LDraw::DrawSprite(Spr* spr, double imageIndex, double x, double y)
{
    sf::Sprite s(*spr->image);
    s.SetX(static_cast<float>(x - spr->origX));
    s.SetY(static_cast<float>(y - spr->origY));
    s.SetSubRect(sf::IntRect(static_cast<int>(imageIndex * spr->imageWidth), 0, static_cast<int>((imageIndex + 1) * spr->imageWidth), spr->imageHeight));
    HScreen::getScreen()->Draw(s);
}
