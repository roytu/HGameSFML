#include "Obj.h"
#include "HGame.h"
#include <vector>
#include <cmath>

#include "LDraw.h"

Obj::Obj(void)
{
	init();
}

Obj::Obj(double x, double y)
{
    init();
	this->x = x;
	this->y = y;
	xstart = x;
	ystart = y;
	//creepy
}

void Obj::init()
{
	visible = true;

	imageIndex = 0;
	imageSpeed = 0;

	x = 0;
	y = 0;

	xstart = 0;
	ystart = 0;

	xprev = 0;
	yprev = 0;

	hspeed = 0;
	vspeed = 0;

	gravity = 0;
	gravityDirection = 0;

	friction = 0;

	sprite = NULL;

	HGame::addObject(this);
}


Obj::~Obj(void)
{
	if(sprite != NULL)
	{
		delete sprite;
	}
}

void Obj::destroy()
{
	HGame::removeObject(this);
}

void Obj::onEvent(sf::Event event){}

void Obj::onStep()
{
    if(sprite != NULL)
    {
        imageIndex += imageSpeed;
        if(imageIndex >= sprite->imageCount)
        {
            while(imageIndex >= sprite->imageCount)
            {
                imageIndex -= sprite->imageCount;
            }
            onAnimationEnd();
        }
        if(!doesExist){return;}
    }

	xprev = x;
	yprev = y;

	x += hspeed;
	y += vspeed;
	hspeed += cos(3.14159265358979323 / 180 * gravityDirection) * gravity;
	vspeed -= sin(3.14159265358979323 / 180 * gravityDirection) * gravity;
	if(abs(hspeed) <= friction){hspeed = 0;}
	else{hspeed -= hspeed/abs(hspeed) * friction;}
	if(abs(vspeed) <= friction){vspeed = 0;}
	else{vspeed -= vspeed/abs(vspeed) * friction;}
}

void Obj::onDraw()
{
	if(sprite != NULL)
	{
		LDraw::DrawSprite(sprite, imageIndex, x, y);
	}
}

void Obj::onAnimationEnd(){}

bool Obj::isColliding(ObjectType type)
{
    return getCollisionAt(x, y, type) != NULL;
}

bool Obj::isCollidingAt(double x, double y, ObjectType type)
{
	return getCollisionAt(x, y, type) != NULL;
}

bool Obj::isOutsideRoom()
{
	if(isOutsideRoom(RIGHT) || isOutsideRoom(UP) || isOutsideRoom(LEFT) || isOutsideRoom(DOWN))
	{
		return true;
	}
	return false;
}

bool Obj::isOutsideRoom(Sides side)
{
	switch(side)
	{
	case RIGHT:
		if(x - sprite->origX >= HScreen::SCREEN_WIDTH)
		{
			return true;
		}
		return false;
		break;
	case UP:
		if(y - sprite->origY + sprite->image->GetHeight() <= 0)
		{
			return true;
		}
		return false;
		break;
	case LEFT:
		if(x - sprite->origX + sprite->image->GetWidth() <= 0)
		{
			return true;
		}
		return false;
		break;
	case DOWN:
		if(y - sprite->origY >= HScreen::SCREEN_HEIGHT)
		{
			return true;
		}
		return false;
		break;
	}
	return false;
}

Obj* Obj::getCollisionAt(double x, double y, ObjectType type)
{
    //TODO ellipse
	for(unsigned int i=0; i<HGame::getObjectList().size(); i++)
	{
	    Obj* o = HGame::getObjectList().at(i);
		if(o->objectType == type)
		{
			Spr* spr1 = sprite;
			Spr* spr2 = o->sprite;
			switch(sprite->hitbox)
			{
                case Spr::HITBOX_PRECISE:
                {
                    double r1x1 = x + spr1->hitboxX1 - spr1->origX;
                    double r1y1 = y + spr1->hitboxY1 - spr1->origY;
                    double r1x2 = x + spr1->hitboxX2 - spr1->origX;
                    double r1y2 = y + spr1->hitboxY2 - spr1->origY;
                    sf::Rect<double> rect1(r1x1, r1y1, r1x2, r1y2);

                    double r2x1 = o->x + spr2->hitboxX1 - spr2->origX;
                    double r2y1 = o->y + spr2->hitboxY1 - spr2->origY;
                    double r2x2 = o->x + spr2->hitboxX2 - spr2->origX;
                    double r2y2 = o->y + spr2->hitboxY2 - spr2->origY;
                    sf::Rect<double> rect2(r2x1, r2y1, r2x2, r2y2);

                    sf::Rect<double> overlap;
                    if(rect1.Intersects(rect2, &overlap))
                    {
                        for(int x=overlap.Left;x<overlap.Right;x++)
                        {
                            for(int y=overlap.Top;y<overlap.Bottom;y++)
                            {
                                if(spr1->image->GetPixel(x, y).a == 255 && spr2->image->GetPixel(x, y).a == 255)
                                {
                                    return o;
                                }
                            }
                        }
                    }
                }
                break;
                case Spr::HITBOX_RECTANGLE:
                {
                    double r1x1 = x + spr1->hitboxX1 - spr1->origX;
                    double r1y1 = y + spr1->hitboxY1 - spr1->origY;
                    double r1x2 = x + spr1->hitboxX2 - spr1->origX;
                    double r1y2 = y + spr1->hitboxY2 - spr1->origY;
                    sf::Rect<double> rect1(r1x1, r1y1, r1x2, r1y2);

                    double r2x1 = o->x + spr2->hitboxX1 - spr2->origX;
                    double r2y1 = o->y + spr2->hitboxY1 - spr2->origY;
                    double r2x2 = o->x + spr2->hitboxX2 - spr2->origX;
                    double r2y2 = o->y + spr2->hitboxY2 - spr2->origY;
                    sf::Rect<double> rect2(r2x1, r2y1, r2x2, r2y2);

                    if(rect1.Intersects(rect2))
                    {
                        return o;
                    }
                }
				break;
			}
		}
	}
	return NULL;
}

bool Obj::isObjectAtPoint(double x, double y)
{
    Spr* spr = sprite;
    switch(spr->hitbox)
    {
        //TODO support others
        case Spr::HITBOX_RECTANGLE:
            if(spr->hitboxX1 + this->x <= x && x <= spr->hitboxX2 + this->x && spr->hitboxY1 + this->y <= y && y <= spr->hitboxY2 + this->y)
            {
                return true;
            }
        break;
    }
}

Obj* Obj::getCollisionPoint(double x, double y, ObjectType type)
{
    if(type == NULL)
    {
        for(int i = 0; i<HGame::getObjectList().size(); i++)
        {
            Obj* o = HGame::getObjectList().at(i);
            if(o->sprite != NULL)
            {
                if(o->isObjectAtPoint(x, y))
                {
                    return o;
                }
            }
        }
        return false;
    }
    else
    {
        for(int i = 0; i<HGame::getObjectList().size(); i++)
        {
            Obj* o = HGame::getObjectList().at(i);
            if(o->objectType != type)
                continue;
            if(o->sprite != NULL)
            {
                Spr* spr = o->sprite;
                switch(spr->hitbox)
                {
                    //TODO support others
                    case Spr::HITBOX_RECTANGLE:
                        if(spr->hitboxX1 + o->x <= x && x <= spr->hitboxX2 + o->x && spr->hitboxY1 + o->y <= y && y <= spr->hitboxY2 + o->y)
                        {
                            return o;
                        }
                    break;
                }
            }
        }
        return false;
    }
}

Obj* Obj::getCollisionLine(double x1, double y1, double x2, double y2, ObjectType type, int steps)
{
    double cx, cy;
    cx = x1;
    cy = y1;

    double dx, dy;
    dx = (x2 - x1) / steps;
    dy = (y2 - y1) / steps;
    for(int i = 0; i<steps; i++)
    {
        cx += dx;
        cy += dy;

        Obj* o = getCollisionPoint(cx, cy, type);
        if(o != NULL)
        {
            return NULL;
        }
    }
}
