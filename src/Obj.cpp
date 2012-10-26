#include "Obj.h"
#include "HGame.h"
#include <vector>
#include <cmath>

#include "LDraw.h"

std::map<Obj::ObjectType, Obj::ObjectType> Obj::parentMap;

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
}

void Obj::init()
{
    //TODO setup parent hierarchy here
    parentMap = std::map<ObjectType, ObjectType>({
                                                 /* TODO parent hierarchy here */
                                                 });

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
			switch(sprite->hitboxType)
			{
                case Spr::HITBOX_PRECISE:
                {
                    sf::Rect<double> rect1 = spr1->getTransformedHitbox(x, y);
                    sf::Rect<double> rect2 = spr2->getTransformedHitbox(x, y);

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
                    sf::Rect<double> rect1 = spr1->getTransformedHitbox(x, y);
                    sf::Rect<double> rect2 = spr2->getTransformedHitbox(x, y);

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
    switch(spr->hitboxType)
    {
        //TODO support others
        case Spr::HITBOX_RECTANGLE:
            if(spr->getTransformedHitbox(this->x, this->y).Contains(x, y))
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
                switch(spr->hitboxType)
                {
                    //TODO support others
                    case Spr::HITBOX_RECTANGLE:
                        if(spr->getTransformedHitbox(o->x, o->y).Contains(x, y))
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

Obj::ObjectType Obj::getParent()
{
    return parentMap.at(objectType);
}

Obj::ObjectType Obj::getParent(ObjectType objectType)
{
    return parentMap.at(objectType);
}

bool Obj::isParent(ObjectType parent, ObjectType child)
{
    while(child != NULL)
    {
        if(child == parent)
        {
            return true;
        }
        child = getParent(child);
    }
    return false;
}
