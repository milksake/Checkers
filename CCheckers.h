#pragma once
#include "CScene.h"
#include "CBoard.h"

class CCheckers : public CScene
{
	CBoard board;
	Vector2 sep;
	Vector2 selectedSquare;
	std::vector<Vector2> highlitedSquares;

	void drawBoard();
	void drawPiece(const Vector2& pos, bool color);
	void selectSquare(const Vector2& pos);
	void deSelectSquare();

public:
	CCheckers(CGame* const _game);

	// Inherited via CScene
	virtual void begin() override;
	virtual void end() override;
	virtual void update() override;
};