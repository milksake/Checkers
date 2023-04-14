#pragma once
#include "Vector2.h"
#include <vector>

class CBoard
{
private:
	int board[8] = {
		0x21212121,
		0x12121212,
		0x21210121,
		0x10121010,
		0x01010101,
		0x16161616,
		0x61616161,
		0x16161616
	};
	// Each int is the state of a row
	// The state of a tile consists of 4 bits
	// 3      2           1            0
	// - pieceColor isPiecePresent tileColor

	void changeState(int x, int y, int value);
	void changeState(const Vector2& pos, int value);

public:
	CBoard();

	int& operator[](int i);
	
	int state(int x, int y) const;
	int state(const Vector2& coor) const;

	std::vector<Vector2> possibleMoves(const Vector2& square, bool color) const;
	std::vector<Vector2> possibleMoves(int x, int y, bool color) const;

	void movePiece(const Vector2& from, const Vector2& to);

	std::vector<Vector2> getPieces();
	std::vector<Vector2> getPieces(bool color);

	int countPieces();
	int countPieces(bool color);
};