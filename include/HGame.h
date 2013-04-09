#pragma once

#include <vector>
#include <queue>
#include "Obj.h"

class HGame
{
private:
	static const int FPS = 60;
	static HGame* instance;

	bool isRunning;
	void hEvent();
	void hStep();
	void hDraw();

public:
	std::vector<Obj*> objectList;
	std::queue<Obj*> destroyQueue;

	bool didRoomChange;

	HGame(void);
	~HGame(void);

	static HGame* getInstance();
	static void addObject(Obj* o);
	static void removeObject(Obj* o);

	static std::vector<Obj*> getObjectList();
};