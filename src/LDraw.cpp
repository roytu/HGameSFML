#include "LDraw.h"

void LDraw::DrawRect(double x, double y, double w, double h, sf::Color color)
{
	HScreen::getScreen()->Draw(sf::Shape::Rectangle(x, y, x + w, y + h, color));
}
void LDraw::DrawCircle(double x, double y, double r, sf::Color color)
{
    HScreen::getScreen()->Draw(sf::Shape::Circle(x, y, r, color));
}

void LDraw::DrawImage(sf::Image* img, double x, double y)
{
    sf::Sprite s(*img);
    s.SetX(x);
    s.SetY(y);
    HScreen::getScreen()->Draw(s);
}

void LDraw::DrawSprite(Spr* spr, double imageIndex, double x, double y)
{
    sf::Sprite s(*spr->image);
    s.SetX(x - spr->origX);
    s.SetY(y - spr->origY);
    s.SetSubRect(sf::IntRect(imageIndex * spr->imageWidth, 0, (imageIndex + 1) * spr->imageWidth, spr->imageHeight));
    HScreen::getScreen()->Draw(s);
}
