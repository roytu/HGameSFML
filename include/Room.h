#pragma once

#include "Obj.h"
#include <vector>

struct RoomObj
{
	int obj;
	double x;
	double y;
};

class Room
{
private:
	Obj* makeObj(int o, double x, double y);

public:
	Room(void);
	~Room(void);

	sf::Image backgroundImage;
	bool useBackgroundImage;

	void addObject(int obj, double x, double y);
	std::vector<RoomObj> roomObjList;
	void buildRoom();
};

