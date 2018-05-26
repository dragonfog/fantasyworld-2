#include "stage.h"


Stage::Stage()
{
}

Stage::Stage(const int& x, const int& y, const int& number)
{
	this->setNumber(number);
	this->setRow(x);
	this->setCol(y);
}

Stage::Stage(const int& number)
{
	this->setNumber(number);
}

Stage::~Stage()
{
	for (int i = 0; i < row; i++)
	{
		delete[] stageinf[i];
	}
	delete[] stageinf;
	delete[] monsters;
}

void Stage::initStage()
{
	stageinf = new int*[row];
	for (int i = 0; i < row; i++)
		stageinf[i] = new int[col];
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
		{
			stageinf[i][j] = 0;
		}
	}
}

void Stage::drawmap()
{
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			if (i == hero->getPosX() && j == hero->getPosY())
			{
				if (stageinf[i][j] < 10 && stageinf[i][j] != INIT_HP)
					cout <<  "-" << stageinf[i][j]  << " ";
				else
					cout  << stageinf[i][j]  << " ";
			}
			else if (stageinf[i][j] < 10 && stageinf[i][j] != INIT_HP)
				cout <<  "-" << stageinf[i][j] <<  " ";
			else if (stageinf[i][j] == INIT_HP)
				cout << "--" << " ";
			else
				cout << stageinf[i][j] << " ";
		}
		cout << endl;
	}
}

void Stage::setRow(const int& x)
{
	row = x;
}

void Stage::setCol(const int& y)
{
	col = y;
}

int Stage::getRow()
{
	return row;
}

int Stage::getCol()
{
	return col;
}

int Stage::randPositionX()
{
	return rand() % row;
}

int Stage::randPositionY()
{
	return rand() % col;
}

void Stage::setNumber(const int& number)
{
	x_num = number;
}

void Stage::setspawnData(const int& x, const int& y, const int& hp)
{
	stageinf[x][y] = hp;
}

void Stage::setPlayerData(const int& x, const int& y, const int& hp)
{
	stageinf[x][y] = hp;
}

void Stage::spawner()
{
	this->getTurn();
	for (int i = 0; i < x_num; i++)
	{
		this->single(i);
	}
	this->playerSpawner();
	this->drawmap();
}

void Stage::single(const int& value)
{
	while (true)
	{
		int m_row = this->randPositionX();
		int m_col = this->randPositionY();

		if (stageinf[m_row][m_col] == INIT_HP)
		{
			
			monsters[value].respawn(m_row, m_col);
			this->setspawnData(m_row, m_col, monsters[value].getHP());
			break;
		}
	}
}

void Stage::playerSpawner()
{
	while (hero->getFlag())
	{
		int p_row = this->randPositionX();
		int p_col = this->randPositionY();
		if (stageinf[p_row][p_col] == INIT_HP)
		{
			hero->summon(p_row, p_col);
			this->setPlayerData(hero->getPosX(), hero->getPosY(), hero->getHP());
		}
	}
}

void Stage::getTurn()
{
	cout << endl;
	cout << "====================================================================================================" << endl;
	cout << endl;
	cout << "Turn: " << turn << endl;
	turn++;
}

void Stage::nexTurn()
{
	

	for (int i = 0; i < x_num; i++)
	{
		monsters[i].reduceHP();
		this->setspawnData(monsters[i].getx(), monsters[i].gety(), monsters[i].getHP());
		if (monsters[i].getHP() == INIT_HP)
		{
			this->single(i);
		}
	}
}

void Stage::autoNextTurn()
{
	clock_t startt, endt;
	float difft;
	startt = clock();
	bool con = true;
	while (con)
	{
		endt = clock();
		difft = ((float)endt - (float)startt) / CLOCKS_PER_SEC;
		if (difft > DIFF)
		{
			startt = clock();
			this->getTurn();
			this->nexTurn();
			this->drawmap();
		}
		if (turn > MAX_TURN)
			con = !con;
	}
}