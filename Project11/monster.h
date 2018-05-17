#pragma once
#include "Header.h"
class Monster
{
private:
	int monhp;
	int x_cor;
	int y_cor;
public:
	Monster();
	~Monster();
	int getx();
	int gety();
	void respawn(int x ,int y);
	void setHP();
	int getHP();
	void reduceHP();
};

