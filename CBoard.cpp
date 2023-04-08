#include "CBoard.h"

CBoard::CBoard()
{
}

int& CBoard::operator[](int i)
{
	return board[i];
}

int CBoard::state(int x, int y)
{
	int s = board[y] >> (x * 4);
	return s & 0xF;
}

int CBoard::state(Vector2 coor)
{
	return state(coor.x, coor.y);
}
