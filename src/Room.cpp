#include "Room.h"

Room::Room(void)
{
	//backgroundImage = NULL;
	useBackgroundImage = false;
}


Room::~Room(void)
{
}

void Room::addObject(int obj, double x, double y)
{
	RoomObj ro = RoomObj();
	ro.obj = obj;
	ro.x = x;
	ro.y = y;
	roomObjList.push_back(ro);
}

void Room::buildRoom()
{
	for(int i=0; i<roomObjList.size(); i++)
	{
	    RoomObj o = roomObjList.at(i);
		makeObj(o.obj, o.x, o.y);
	}
}

Obj* Room::makeObj(int o, double x, double y)
{
	switch(o)
	{
		//TODO
	}
	return NULL;
}
