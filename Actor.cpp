#include "Actor.h"
#include "CGame.h"
#include "CCheckers.h"
#include <iostream>

Actor::Actor(bool color):
	color(color) {}

Player::Player(bool color):
	Actor(color) {}

void Player::update()
{
	for (auto& input : scene->game->inputBuffer)
	{
		if (input.action == GLFW_PRESS && input.key == GLFW_MOUSE_BUTTON_LEFT)
		{
			for (int y = 0; y < 8; y++)
				for (int x = 0; x < 8; x++)
				{
					auto lt = Vector2(scene->sep.x * (x + 1), scene->sep.y * (y + 1));
					if (input.pos.checkRange(lt, lt + scene->sep))
					{
						if (scene->selectedSquare != Vector2(-1, -1))
						{
							if (std::find(scene->highlitedSquares.begin(), scene->highlitedSquares.end(), lt) != scene->highlitedSquares.end())
							{
								scene->board.movePiece(scene->selectedSquare, Vector2(x, y));
								scene->deSelectSquare();
								scene->turn = !scene->turn;
							}
						}
						else
						{
							int state = scene->board.state(Vector2(x, y));
							if (state & 0x2 && (bool)(state & 0x4) == color)
								scene->selectSquare(Vector2(x, y));
						}
					}
				}
		}
		if (input.action == GLFW_PRESS && input.key == GLFW_MOUSE_BUTTON_RIGHT)
			scene->deSelectSquare();
	}
}

void Actor::setScene(CCheckers* _scene)
{
	scene = _scene;
}

AI::AI(bool color):
	Actor(color) {}

void AI::update()
{
	if (scene->selectedSquare == Vector2(-1, -1) || scene->highlitedSquares.empty())
	{
		Vector2 n(rand() % 8, rand() % 8);
		int state = scene->board.state(n);
		while (state & 0x1 || !(state & 0x2) || (bool)(state & 0x4) != color)
		{
			n = Vector2(((int)n.x + 1) % 8, ((int)n.y + ((int)n.x + 1) / 8) % 8);
			state = scene->board.state(n);
		}
		scene->selectSquare(n);
		std::cout << "Selected: (" << n.x << ", " << n.y << ")\n";
	}
	else
	{
		std::cout << "HighlitedNodes:\n";
		for (auto v: scene->highlitedSquares)
		{
			v = Vector2(v.x / scene->sep.x - 1, v.y / scene->sep.y - 1);
			std::cout << "\t- (" << v.x << ", " << v.y << ")\n";
		}

		Vector2 n = scene->highlitedSquares[rand() % scene->highlitedSquares.size()];
		n = Vector2(n.x / scene->sep.x - 1, n.y / scene->sep.y - 1);

		scene->board.movePiece(scene->selectedSquare, n);
		scene->deSelectSquare();
		scene->turn = !scene->turn;

		std::cout << "Moved: (" << n.x << ", " << n.y << ")\n";
	}
}
