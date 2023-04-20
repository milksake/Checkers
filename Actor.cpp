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
