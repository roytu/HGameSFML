#pragma once

#include "HScreen.h"
#include "Spr.h"

class LDraw
{
public:
	static void DrawRect(double x, double y, double w, double h, sf::Color color);
	static void DrawCircle(double x, double y, double r, sf::Color color);
	static void DrawImage(sf::Image* img, double x, double y);
	static void DrawSprite(Spr* spr, double imageIndex, double x, double y);
};
