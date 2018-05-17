#pragma once
#include "monster.h"
class Stage
{
private:
	int x_num = 100;
	int row = 30;
	int col = 30;
	int turn = 1;
	int **stageinf = nullptr;
	Monster *monsters = new Monster;
	


public:
	Stage();
	Stage(int x, int y, int percent);
	Stage(int percent);
	~Stage();
	void initStage();
	void setNumber(int x, int y, int percent);
	void setNumber(int percent);
	void setspawnData(int x, int y, int hp);
	void drawmap();
	int randPositionX();
	int randPositionY();
	void setRow(int x);
	void setcol(int y);
	void getTurn();
	int getRow();
	int getCol();
	void spawner();
	void single(int value);
	void nexTurn();
};

