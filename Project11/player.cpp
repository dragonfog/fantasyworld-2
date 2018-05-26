#include "player.h"



Player::Player()
{
}

Player::~Player()
{
}

void Player::summon()
{
	this->setHP();
}

void Player::summon(const int& x, const int& y)
{
	this->setPos(x, y);
	this->setHP();
	this->setFlag();
}

int Player::getRandAtk()
{
	p_atk = rand() % START_ATK + ATK_RANGE;
	return p_atk;
}

void Player::setPos(const int& x, const int& y)
{
	p_posx = x;
	p_posy = y;
}

void Player::moveUp()
{
	p_posx -= 1;
}

void Player::moveDown()
{
	p_posx += 1;
}

void Player::moveLeft()
{
	p_posy -= 1;
}

void Player::moveRight()
{
	p_posy += 1;
}

int Player::getPosX()
{
	return p_posx;
}

int Player::getPosY()
{
	return p_posy;
}

void Player::setHP()
{
	p_hp = rand() % START_HP + HP_RANGE;
}

int Player::getHP()
{
	return p_hp;
}

void Player::reduceHP(const int& atk)
{
	p_hp -= atk;
}

bool Player::getFlag()
{
	return is_death;
}

void Player::setFlag()
{
	is_death = !is_death;
}