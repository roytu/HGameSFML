#include "Spr.h"


Spr::Spr(void)
{
	imageCount = 1;
}


Spr::~Spr(void)
{
}

void Spr::setOriginCenter()
{
	if(image!=NULL)
	{
		origX = image->GetWidth() / 2;
		origY = image->GetHeight() / 2;
	}
}

void Spr::setHitboxFull(HitboxType hitbox)
{
	this->hitbox = hitbox;

	if(image != NULL)
	{
		hitboxX1 = 0;
		hitboxY1 = 0;
		hitboxX2 = imageWidth;
		hitboxY2 = imageHeight;
	}
}

void Spr::setOriginTopLeft()
{
	origX = 0;
	origY = 0;
}

void Spr::setup()
{
	imageWidth = image->GetWidth() / imageCount;
	imageHeight = image->GetHeight();
}

void Spr::setHitbox(int x1, int y1, int x2, int y2, HitboxType type)
{
	hitbox = type;

	hitboxX1 = x1;
	hitboxY1 = y1;
	hitboxX2 = x2;
	hitboxY2 = y2;
}
