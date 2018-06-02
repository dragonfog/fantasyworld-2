#pragma once
#include "Header.hpp"

class Player
{
private:
	const int START_HP = 10;
	const int HP_RANGE = 10;
	const int START_ATK = 2;
	const int ATK_RANGE = 5;
	const int TYPE = 2;

	int p_posx = 0;
	int p_posy = 0;
	int p_atk = 0;
	int p_hp;
	bool is_death = true;

public:
	Player();
	~Player();
	void summon();
	void summon(const int& x, const int& y);
	int getRandAtk();
	void setPos(const int& x, const int& y);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	int getPosX();
	int getPosY();
	void setHP();
	int getHP();
	void reduceHP(const int& atk);
	bool getFlag();
	void setFlag();
	int getType();
	void attacked(const int& dmg);
};