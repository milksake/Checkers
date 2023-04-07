#include <iostream>
#include "CGame.h"

int main()
{
	CGame game;
	game.init(1000, 500);
	game.run();
	return 0;
}