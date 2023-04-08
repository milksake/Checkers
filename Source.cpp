#include <iostream>
#include "CGame.h"

int main()
{
	CGame game;
	if (!game.init(1000, 700))
		return -1;
	game.run();
	return 0;
}