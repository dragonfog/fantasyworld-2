#include "monster.h"



Monster::Monster()
{
}


Monster::~Monster()
{
}
void Monster::respawn(int x, int y)
{
	x_cor = x;
	y_cor = y;
	monhp = rand() % 10 + 5;
}

void Monster::setHP()
{
	monhp = rand() % 10 + 5;
}

int Monster::getHP()
{
	return monhp;
}

int Monster::getx()
{
	return x_cor;
}

int Monster::gety()
{
	return y_cor;
}

void Monster::reduceHP()
{
	monhp--;
}


