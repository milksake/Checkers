#include "CBoard.h"

void CBoard::changeState(int x, int y, int value)
{
	int& row = board[y];
	int mask = ~(0xF << (4 * x));
	row = (row & mask) | (value << (4 * x));
}

void CBoard::changeState(const Vector2& pos, int value)
{
	changeState(pos.x, pos.y, value);
}

CBoard::CBoard()
{
}

int& CBoard::operator[](int i)
{
	return board[i];
}

int CBoard::state(int x, int y) const
{
	int s = board[y] >> (x * 4);
	return s & 0xF;
}

int CBoard::state(const Vector2& coor) const
{
	return state(coor.x, coor.y);
}

std::vector<Vector2> CBoard::possibleMoves(const Vector2& square, bool color) const
{
	Vector2 coor[2] = {
		square + Vector2(-1, color ? -1 : 1),
		square + Vector2( 1, color ? -1 : 1),
	};

	std::vector<Vector2> posMoves;
	for (int i = 0; i < 2; i++)
	{
		if (!coor[i].checkRange(Vector2(0, 0), Vector2(7, 7)))
			continue;
		int s = state(coor[i]);
		// Move
		if (!(s & 0x2))
			posMoves.push_back(coor[i]);
		else // Capture Pieces
		{
			Vector2 newCoor = coor[i] * 2 - square;
			if ((bool)(s & 0x4) == !color && !(state(newCoor) & 0x2) && newCoor.checkRange(Vector2(0, 0), Vector2(7, 7)))
			{
				posMoves.push_back(newCoor);
			}
		}
	}

	return posMoves;
}

std::vector<Vector2> CBoard::possibleMoves(int x, int y, bool color) const
{
	return possibleMoves(Vector2(x, y), color);
}

void CBoard::movePiece(const Vector2& from, const Vector2& to)
{
	changeState(to, state(from));
	changeState(from, state(from) & (~0x2));

	Vector2 newV = to - from;
	if (newV.abs() == Vector2(2, 2))
	{
		newV = from + (newV / 2);
		changeState(newV, state(newV) & (~0x2));
	}
}
