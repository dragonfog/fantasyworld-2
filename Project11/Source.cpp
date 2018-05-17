#include "stage.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	int r, c, p;
	srand(time(NULL));
	cout << "input row"; cin >> r;
	cout << "input collumn"; cin >> c;
	cout << "input percent monster u want to spawn in map "; cin >> p;
	Stage* World = new Stage(r, c, p);
	World->initStage();
	World->spawner();
	World->drawmap();
	World->nexTurn();
}