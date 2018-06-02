#include "monster.hpp"



Monster::Monster()
{
}


Monster::~Monster()
{
}
void Monster::respawn(const int& x, const int& y, const int& number)
{
	monnumber = number;
	monposx = x;
	monposy = y;
	monHP = rand() % START_HP + HP_RANGE;
}



void Monster::setHP()
{
	monHP = rand() % START_HP + HP_RANGE;
}


int Monster::getHP()
{
	return monHP;
}

int Monster::getx()
{
	return monposx;
}

int Monster::gety()
{
	return monposy;
}

void Monster::reduceHP()
{
	monHP--;
}

int Monster::getRandAtk()
{
	monatk = rand() % START_ATK + ATK_RANGE;
	return monatk;
}


int Monster::getNumber()
{
	return monnumber;
}

int Monster::getType()
{
	return TYPE;
}

void Monster::attacked(const int& dmg)
{
	monHP -= dmg;
	if (monHP < ABSOLUTE_ZERO)
		monHP = ABSOLUTE_ZERO;
}