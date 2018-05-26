#pragma once
#include "monster.h"
#include "player.h"
class Stage
{
private:
	const int INIT_HP = 0;
	const float DIFF = 2.0;
	const int MAX_TURN = 5;
	int x_num = 100;
	int row = 30;
	int col = 30;
	int turn = 1;
	int **stageinf = nullptr;

	Player *hero = new Player;
	Monster *monsters = new Monster;
	


public:
	Stage();
	Stage(const int& x, const int& y, const int& number);
	Stage(const int& number);
	~Stage();
	void initStage();
	void setNumber(int x, int y, int percent);
	void setNumber(const int& number);
	void setspawnData(const int& x, const int& y, const int& hp);
	void setPlayerData(const int& x, const int& y, const int& hp);
	void drawmap();
	int randPositionX();
	int randPositionY();
	void setRow(const int& x);
	void setCol(const int& y);
	void getTurn();
	int getRow();
	int getCol();
	void playerSpawner();
	void spawner();
	void single(const int& value);
	void nexTurn();
	void autoNextTurn();
	
};

