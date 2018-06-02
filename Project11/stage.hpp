#pragma once
#include "Monster.hpp"
#include "Player.hpp"
class Stage
{
private:
	const std::string HERO = "H";
	const std::string MONSTER = "M";
	const std::string EMPTY = "-";
	const float DIFF = 2.0;
	const int MAX_TURN = 5;
	const enum TYPE { INIT = 0, T_MONSTER = 1, T_HERO = 2, T_BOTH = 3 };

	int m_number = 100;
	int row = 30;
	int col = 30;
	int turn = 1;

	std::vector<std::vector<int>> mapdata;
	std::vector<std::vector<int>> monsterdata;
	std::vector<std::shared_ptr<Monster>> monsters;
	std::shared_ptr<Player> hero = std::make_shared<Player>();

public:
	Stage();
	Stage(const int& x, const int& y, const int& number);
	Stage(const int& number);
	~Stage();
	void stageinf();
	void ClearScreen();
	void setNumber(const int& number);
	void setMapData(const int& x, const int& y, const int& type);
	void setMonsterData(const int& x, const int& y, const int& value);
	void displayStat();
	void drawMap();
	int randPosX();
	int randPosY();
	void setRow(const int& x);
	void setCol(const int& y);
	void getTurn();
	int getRow();
	int getCol();
	void spawner();
	void singleSpawner(const int& value);
	void playerSpawner();
	void playerController();
	void playerMoveUp();
	void playerMoveLeft();
	void playerMoveDown();
	void playerMoveRight();
	void checkPrev();
	void checkCurr();
	void atkPhase();
	void checkAfterAtk(const int& value);
	void autoNextTurn();
	void nextTurn();
};

