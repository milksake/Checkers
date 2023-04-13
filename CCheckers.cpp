#include "CCheckers.h"
#include "CGame.h"

void CCheckers::drawBoard()
{
	std::vector<Vector2> rects;
	Vector2 mouseRectPos(-1, -1);
	auto mousePos = game->getMouseLocation();

	// Row
	for (int y = 0; y < 8; y++)
	{
		// Column
		for (int x = 0, mask = 0xF; x < 8; x++, mask = mask << 4)
		{
			int state = board.state(x, y);
			auto lt = Vector2(sep.x * (x + 1), sep.y * (y + 1));
			if (state & 0x1) // if white tile
			{				
				rects.push_back(lt);
				rects.push_back(lt + Vector2(sep.x, 0));
				rects.push_back(lt + sep);
				rects.push_back(lt + Vector2(0, sep.y));
			}
			if (state & 0x2) // if piece present
				drawPiece(Vector2(x, y), state & 0x4);
			if (mousePos.checkRange(lt, lt + sep))
			{
				mouseRectPos = lt;
			}
		}
	}
	game->drawRects(rects);

	if (mouseRectPos.x != -1 && mouseRectPos.y != -1)
		game->drawRects({
			mouseRectPos,
			mouseRectPos + Vector2(sep.x, 0),
			mouseRectPos + sep,
			mouseRectPos + Vector2(0, sep.y),
		}, Color::AlphaGrey);

	for (auto& square : highlitedSquares)
	{
		game->drawRects({
			square,
			square + Vector2(sep.x, 0),
			square + sep,
			square + Vector2(0, sep.y),
		}, Color::Green);
	}

	if (selectedSquare != Vector2(-1, -1))
	{
		Color color = (highlitedSquares.empty()) ? Color::AlphaRed : Color::AlphaGreen;
		auto lt = Vector2(sep.x * (selectedSquare.x + 1), sep.y * (selectedSquare.y + 1));
		game->drawRects({
			lt,
			lt + Vector2(sep.x, 0),
			lt + sep,
			lt + Vector2(0, sep.y),
		}, color);
	}
}

void CCheckers::selectSquare(const Vector2& pos)
{
	selectedSquare = pos;
	auto squares = board.possibleMoves(selectedSquare, board.state(selectedSquare) & 0x4);

	for (auto& square : squares)
		highlitedSquares.push_back(Vector2(sep.x * (square.x + 1), sep.y * (square.y + 1)));
}

void CCheckers::deSelectSquare()
{
	selectedSquare = Vector2(-1, -1);
	highlitedSquares.clear();
}

void CCheckers::drawPiece(const Vector2& pos, bool color)
{
	auto center = Vector2(sep.x * (pos.x + 1), sep.y * (pos.y + 1)) + (sep / 2.0f);
	auto size = sep * (3.0f / 4.0f);
	if (color)
		game->drawCircle(center, size);
	else
		game->drawHollowCircle(center, size);
	/*
	Color mainC = Color::Black;
	Color secondaryC = Color::White;
	auto size = sep * (3.0f / 4.0f);
	if (color)
		std::swap(mainC, secondaryC);
	game->drawCircle(center, size, mainC);
	game->drawHollowCircle(center, size, secondaryC);
	*/
}

CCheckers::CCheckers(CGame* const _game):
	CScene(_game), board(),
	sep(_game->getWidth() / 10.0f, _game->getHeight() / 10.0f),
	selectedSquare(-1, -1)
{
}

void CCheckers::begin()
{
}

void CCheckers::end()
{
}

void CCheckers::update()
{
	for (auto& input : game->inputBuffer)
	{
		if (input.action == GLFW_PRESS && input.key == GLFW_MOUSE_BUTTON_LEFT)
		{
			for (int y = 0; y < 8; y++)
				for (int x = 0; x < 8; x++)
				{
					auto lt = Vector2(sep.x * (x + 1), sep.y * (y + 1));
					if (input.pos.checkRange(lt, lt + sep))
					{
						if (selectedSquare != Vector2(-1, -1))
						{
							if (std::find(highlitedSquares.begin(), highlitedSquares.end(), lt) != highlitedSquares.end())
							{
								board.movePiece(selectedSquare, Vector2(x, y));
								deSelectSquare();
							}
						}
						else if (board.state(Vector2(x, y)) & 0x6)
							selectSquare(Vector2(x, y));
					}
				}
		}
		if (input.action == GLFW_PRESS && input.key == GLFW_MOUSE_BUTTON_RIGHT)
			deSelectSquare();
	}

	game->beginDrawing();

	drawBoard();

	game->endDrawing();
}
