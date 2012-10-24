#include "HRoom.h"
#include "HGame.h"

HRoom* HRoom::instance;

HRoom::HRoom(void)
{
	instance = this;
}


HRoom::~HRoom(void)
{
}

HRoom* HRoom::getInstance()
{
	return instance;
}

void HRoom::buildRoom()
{
	HRoom::getInstance()->currentRoom->buildRoom();
}
void HRoom::setRoom(Room* room)
{
	HGame::getInstance()->didRoomChange = true;
	HRoom::getInstance()->currentRoom = room;
}
void HRoom::gotoRoom(Room* room)
{
	clearRoom();
	setRoom(room);
	buildRoom();
}
void HRoom::clearRoom()
{
	for(unsigned int i=0; i<HGame::getObjectList().size(); i++)
	{
	    Obj* o = HGame::getObjectList().at(i);
		o->destroy();
	}
}

Room* HRoom::getCurrentRoom()
{
	return HRoom::getInstance()->currentRoom;
}
