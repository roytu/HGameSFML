#pragma once

#include "Room.h"

class HRoom
{
private:
	static HRoom* instance;

public:
	HRoom(void);
	~HRoom(void);

	Room* currentRoom;

	static void buildRoom();
	static void setRoom(Room* room);
	static void gotoRoom(Room* room);
	static void clearRoom();

	static HRoom* getInstance();
	static Room* getCurrentRoom();
};