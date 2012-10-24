#pragma once

#include "Room.h"

class HResources
{
private:
	static HResources* instance;

public:
	static Room* ROOM_TEST;

	HResources(void);
	~HResources(void);

	static HResources* getInstance();

	static Room* Room_Load(const char* url);
};

