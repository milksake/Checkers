#include "CScene.h"
#include "CGame.h"

CScene::CScene(CGame* const _game):
	game(_game)
{
}

bool CScene::hasEnded() const
{
	return ended;
}

CMenu::CMenu(CGame* const _game):
	CScene(_game)
{
}

void CMenu::begin()
{
}

void CMenu::end()
{
}

void CMenu::update()
{
	// INPUT
	for (auto& i : game->inputBuffer)
	{
		if (i.key = GLFW_KEY_A && i.action == GLFW_PRESS)
		{
			a += Vector2(10, 10);
		}
	}
	b = game->getMouseLocation(); // pixels
	c = b + Vector2(0, 50);

	// DRAW
	game->beginDrawing();

	game->drawRects({ a, c, b, d });

	game->endDrawing();
}
