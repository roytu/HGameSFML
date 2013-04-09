#pragma once

#include "Spr.h"

#include <map>

class ParentMap;

class Obj
{
protected:
	void init();

	enum Sides
	{
		RIGHT,
		UP,
		LEFT,
		DOWN
	};

public:
    enum ObjectType
	{
	    TEST
	};

    static std::map<ObjectType, ObjectType> parentMap;

	bool doesExist;

	bool visible;

	ObjectType objectType;

	double imageIndex;
	double imageSpeed;

	double x;
	double y;

	double xstart;
	double ystart;

	double xprev;
	double yprev;

	double hspeed;
	double vspeed;

	double gravity;
	double gravityDirection;

	double friction;

	Spr* sprite;

	Obj(void);
	Obj(double x, double y);
	~Obj(void);

	virtual void destroy();

	virtual void onEvent(sf::Event event);
	virtual void onStep();
	virtual void onDraw();

	bool isColliding(ObjectType type);
	bool isCollidingAt(double x, double y, ObjectType type);

	bool isOutsideRoom();
	bool isOutsideRoom(Sides side);

	virtual void onAnimationEnd();

    bool isObjectAtPoint(double x, double y);
    Obj* getCollisionAt(double x, double y, ObjectType type);
    static Obj* getCollisionPoint(double x, double y, ObjectType type);
	static Obj* getCollisionLine(double x1, double y1, double x2, double y2, ObjectType type, int steps);

	ObjectType getParent();
	ObjectType getParent(ObjectType objectType);

	void moveContact(double direction, int maxDist, ObjectType objectType);

	bool isParent(ObjectType parent, ObjectType child);
};
