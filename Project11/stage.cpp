#include "stage.h"



Stage::Stage(){}
Stage::Stage(int x, int y, int percent)
{
	this->setNumber(x, y, percent);
	this->setRow(x);
	this->setcol(y);
}
Stage::Stage(int percent)
{
	this->setNumber(percent);
}

Stage::~Stage()
{
	for (int i = 0; i < row; i++)
	{
		delete[] stageinf[i];
	}
		delete[] stageinf;
		delete[] monsters;}
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
	for(int i=0;i<row;++i)
	{
		for(int j=0;j<row;++j)
		{
			if(stageinf[i][j]<10 & stageinf[i][j]!=0)
				cout << "-" << stageinf[i][j] << " ";
			else if (stageinf[i][j] == 0)
				cout << "--" << " ";
			else
				cout <<stageinf[i][j] << " ";

		}
		cout << endl;
	}
}

void Stage::setRow(int x)
{
	row = x;
}

void Stage::setcol(int y)
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
	return rand() & col;
}

void Stage::setNumber(int x, int y, int percent)
{
	x_num = (x*y)*(percent / 100);
}
void Stage::setNumber(int percent)
{
	x_num = (row * col) * (percent / 100.0);
}


void Stage::setspawnData(int x, int y, int hp)
{
	stageinf[x][y] = hp;
}

void Stage::spawner()
{
	this->getTurn();
	for(int i=0;i<x_num;i++)
	{
		this->single(i);
	}
}

void Stage::getTurn()
{

	cout << endl;
	cout << "=====================================================================" << endl;
	cout << endl;
	cout << "Turn: " << turn << endl;
	turn++;
}

void Stage::single(int value)
{
	while (true)
	{
		int row = this->randPositionX();
		int col = this->randPositionY();

		if (stageinf[row][col] == 0)
		{
			monsters[value].respawn(row, col);
			this->setspawnData(row, col, monsters[value].getHP());
			break;
		}
	}
}






void Stage::nexTurn()
{
	
	
	
	clock_t startt, endt;

	float difft;

	startt = clock();

	while (true)
	{
		endt = clock();
		difft = ((float)endt - (float)startt) / CLOCKS_PER_SEC;
		if (difft > 3.0)
		{

			startt = clock();
			this->getTurn();
			for (int i = 0; i < x_num; i++)
			{
				monsters[i].reduceHP();
				this->setspawnData(monsters[i].getx(), monsters[i].gety(), monsters[i].getHP());
				if (monsters[i].getHP() == 0)
				{
					this->single(i);
				}
			}
			this->drawmap();
		}
	}
}


