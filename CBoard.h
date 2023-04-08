#pragma once
#include "Vector2.h"

class CBoard
{
private:
	int board[8] = {
		0x21212121,
		0x12121212,
		0x21212121,
		0x10101010,
		0x01010101,
		0x16161616,
		0x61616161,
		0x16161616
	};
	// Each int is the state of a row
	// The state of a tile consists of 4 bits
	// 3      2           1            0
	// - pieceColor isPiecePresent tileColor

public:
	CBoard();

	int& operator[](int i);
	
	int state(int x, int y);
	int state(Vector2 coor);
};