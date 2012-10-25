#pragma once

#include <SFML/Graphics.hpp>

class Spr
{
public:
	enum HitboxType
	{
		HITBOX_PRECISE,
		HITBOX_RECTANGLE,
		HITBOX_ELLIPSE
	};

	HitboxType hitboxType;

	sf::Image* image;

	double origX;
	double origY;

	sf::Rect<int> hitbox;

	unsigned int imageCount;
	int imageWidth;
	int imageHeight;

	Spr(void);
	~Spr(void);

	void setOriginCenter();
	void setOriginTopLeft();

	sf::Rect<double> getTransformedHitbox(double x, double y);

protected:
	void setHitbox(int x1, int y1, int x2, int y2, HitboxType hitboxType);
	void setHitboxFull(HitboxType hitboxType);
	void setup();
};
