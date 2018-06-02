#include "stage.hpp"

inline std::ostream& blue(std::ostream &s)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE
		| FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	return s;
}

inline std::ostream& red(std::ostream &s)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout,
		FOREGROUND_RED | FOREGROUND_INTENSITY);
	return s;
}

inline std::ostream& green(std::ostream &s)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout,
		FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	return s;
}

inline std::ostream& yellow(std::ostream &s)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout,
		FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	return s;
}

inline std::ostream& white(std::ostream &s)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout,
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	return s;
}

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
}

void Stage::stageinf()
{
	mapdata.resize(row, std::vector<int>(col));
	monsterdata.resize(row, std::vector<int>(col));

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			mapdata[i][j] = INIT;
		}
	}
}

void Stage::ClearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
	)) return;
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;
SetConsoleCursorPosition(hStdOut, homeCoords);
}

void Stage::displayStat()
{
	int monstervalue = monsterdata[hero->getPosX()][hero->getPosY()];

	if (hero->getFlag())
	{
		std::cout <<  "Hero is death." << std::endl;
		std::cout <<  "GAME OVER"  << std::endl;
	}
	else
		std::cout <<  "Hero HP: " << hero->getHP()  << std::endl;

	if (mapdata[hero->getPosX()][hero->getPosY()] == T_BOTH)
		std::cout <<  "Monster HP: " << monsters[monstervalue]->getHP()  << std::endl;
}

void Stage::drawMap()
{
	this->ClearScreen();
	this->getTurn();
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			if (mapdata[i][j] == INIT)
				std::cout << EMPTY << EMPTY << " ";
			else if (mapdata[i][j] == T_MONSTER)
				std::cout << EMPTY  << MONSTER  << " ";
			else if (mapdata[i][j] == T_HERO)
				std::cout <<  HERO << EMPTY  << " ";
			else if (mapdata[i][j] == T_BOTH)
				std::cout << HERO << MONSTER  << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	this->displayStat();
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

int Stage::randPosX()
{
	return rand() % row;
}

int Stage::randPosY()
{
	return rand() % col;
}

void Stage::setNumber(const int& number)
{
	m_number = number;
}

void Stage::setMapData(const int& x, const int& y, const int& type)
{
	mapdata[x][y] = type;
}

void Stage::setMonsterData(const int& x, const int& y, const int& value)
{
	monsterdata[x][y] = value;
}

void Stage::spawner()
{
	for (int i = 0; i < m_number; i++)
	{
		this->singleSpawner(i);
	}
	this->playerSpawner();
	this->drawMap();
}

void Stage::singleSpawner(const int& value)
{
	while (true)
	{
		int m_row = this->randPosX();
		int m_col = this->randPosY();

		if (mapdata[m_row][m_col] == INIT)
		{
			monsters.push_back(std::make_shared<Monster>());
			monsters[value]->respawn(m_row, m_col, value);
			this->setMonsterData(m_row, m_col, value);
			this->setMapData(m_row, m_col, monsters[value]->getType());
			break;
		}
	}
}

void Stage::playerSpawner()
{
	while (hero->getFlag())
	{
		int p_row = this->randPosX();
		int p_col = this->randPosY();
		if (mapdata[p_row][p_col] == INIT)
		{
			hero->summon(p_row, p_col);
			this->setMapData(hero->getPosX(), hero->getPosY(), hero->getType());
			hero->setFlag();
		}
	}
}

void Stage::getTurn()
{
	std::cout << std::endl;
	std::cout << "====================================================================================================" << std::endl;
	std::cout << std::endl;
	std::cout << "Turn: " << turn << std::endl;
	std::cout << std::endl;
	turn++;
}

void Stage::checkPrev()
{
	if (mapdata[hero->getPosX()][hero->getPosY()] == T_BOTH)
		this->setMapData(hero->getPosX(), hero->getPosY(), T_MONSTER);
	else
		this->setMapData(hero->getPosX(), hero->getPosY(), INIT);
}

void Stage::checkCurr()
{
	if (mapdata[hero->getPosX()][hero->getPosY()] == INIT)
		this->setMapData(hero->getPosX(), hero->getPosY(), hero->getType());
	else
		this->setMapData(hero->getPosX(), hero->getPosY(), T_BOTH);
}

void Stage::playerMoveUp()
{
	if (hero->getPosX() != ABSOLUTE_ZERO)
	{
		this->checkPrev();
		hero->moveUp();
		this->checkCurr();
		this->drawMap();
	}
}
void Stage::playerMoveLeft()
{
	if (hero->getPosY() != ABSOLUTE_ZERO)
	{
		this->checkPrev();
		hero->moveLeft();
		this->checkCurr();
		this->drawMap();
	}
}
void Stage::playerMoveDown()
{
	if (hero->getPosX() + 1 != row)
	{
		this->checkPrev();
		hero->moveDown();
		this->checkCurr();
		this->drawMap();
	}
}
void Stage::playerMoveRight()
{
	if (hero->getPosY() + 1 != col)
	{
		this->checkPrev();
		hero->moveRight();
		this->checkCurr();
		this->drawMap();
	}
}

void Stage::checkAfterAtk(const int& value)
{
	if (monsters[value]->getHP() <= ABSOLUTE_ZERO && (!hero->getFlag()))
	{
		this->setMapData(hero->getPosX(), hero->getPosY(), hero->getType());
		this->setMonsterData(hero->getPosX(), hero->getPosY(), NULL);
	}
	else if (hero->getFlag() && monsters[value]->getHP() > ABSOLUTE_ZERO)
	{
		this->setMapData(hero->getPosX(), hero->getPosY(), T_MONSTER);
	}
	else if ((!hero->getFlag()) && monsters[value]->getHP() > ABSOLUTE_ZERO)
	{
		this->setMapData(hero->getPosX(), hero->getPosY(), T_BOTH);
	}
	else
	{
		this->setMapData(hero->getPosX(), hero->getPosY(), INIT);
	}
}

void Stage::atkPhase()
{
	int monstervalue = monsterdata[hero->getPosX()][hero->getPosY()];
	int m_atk = monsters[monstervalue]->getRandAtk();
	int p_atk = hero->getRandAtk();

	hero->attacked(m_atk);
	monsters[monstervalue]->attacked(p_atk);

	this->checkAfterAtk(monstervalue);
	this->drawMap();
}

void Stage::playerController()
{
	char _input;
	while (!hero->getFlag())
	{
		_input = _getch();
		if (_input == 'w' || _input == 'W')
		{
			this->playerMoveUp();
		}
		else if (_input == 'a' || _input == 'A')
		{

			this->playerMoveLeft();
		}
		else if (_input == 's' || _input == 'S')
		{

			this->playerMoveDown();
		}
		else if (_input == 'd' || _input == 'D')
		{
			this->playerMoveRight();
		}
		else if (_input == 'q' || _input == 'Q')
		{
			if (mapdata[hero->getPosX()][hero->getPosY()] == T_BOTH)
				this->atkPhase();
			else
				std::cout << "No monster here.";
		}
	}
}

















/*---------------------- Old Next Turn -----------------------------*/

void Stage::nextTurn()
{
	for (int i = 0; i < m_number; i++)
	{
		monsters[i]->reduceHP();
		this->setMapData(monsters[i]->getx(), monsters[i]->gety(), monsters[i]->getHP());
		if (monsters[i]->getHP() == ABSOLUTE_ZERO)
		{
			this->singleSpawner(i);
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
			this->nextTurn();
			this->drawMap();
		}
		if (turn > MAX_TURN)
			con = !con;
	}
}

/*---------------------- END Old Next Turn -----------------------------*/